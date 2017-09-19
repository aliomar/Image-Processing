#include "mex.h"
#include <iostream>
#include <string>
#include <cmath>

using namespace std;
void invertUint8(int width, int height, const unsigned char *input, unsigned char *output, int c, int b)
{ 
    for (int y = 0; y < height; y++)
        for (int x = 0; x < width; x++)
        {
            int ind = x*height + y;
            output[ind] = input[ind]*c + b;
            if (output[ind] >= 255){
                output[ind] = 255;
            }
        }
}


void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{

    
    if (nlhs != 1)
        mexErrMsgTxt("Apply point transform can only accept one input argument");
    
    if (nrhs != 1)
        mexErrMsgTxt("Apply point transform requires one output argument");
    
    const mxArray *img = prhs[0];
    if (!mxIsDouble(img) && !mxIsUint8(img))
        mexErrMsgTxt("Apply point transform can only accept images of type 'double' or 'uint8'");
    
    mwSize ndims = mxGetNumberOfDimensions(img);
    const mwSize *dims = mxGetDimensions(img);

    int height   = dims[0];
    int width    = dims[1];
 
    mxClassID input_type = mxGetClassID(img);
 
    mxArray *output = mxCreateNumericArray(ndims, dims, input_type, mxREAL);
    plhs[0] = output;

    
    if (mxIsUint8(img))
    {
        unsigned char *img_ptr = (unsigned char *)mxGetData(img);
        unsigned char *out_ptr = (unsigned char *)mxGetData(output);
        
        mxArray   *new_number, *str, *new_number2, *str2;
        double c, b;

        str = mxCreateString("Enter scaling factor (C):  ");
        mexCallMATLAB(1,&new_number,1,&str,"input");
        c = mxGetScalar(new_number);
        
        str2 = mxCreateString("Enter scaling factor (B):  ");
        mexCallMATLAB(1,&new_number2,1,&str2,"input");
        b = mxGetScalar(new_number2);

        

        
        //if (c > 255)
        //    c = fmod(c,255);
        
        invertUint8(width, height, img_ptr, out_ptr, c, b);

    
   }

}