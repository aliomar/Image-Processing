#include "mex.h"
#include <iostream>
#include <string>
#include <cmath>

using namespace std;
void invertUint8(int width, int height, const unsigned char *input, const unsigned char *input1, const unsigned char *input2, unsigned char *output)
{ 
    for (int y = 0; y < height; y++)
        for (int x = 0; x < width; x++)
        {
            int ind = x*height + y;
            if (input2[ind] == 0)
                output[ind] = input1[ind];
            
            else
                output[ind] = input[ind];
        }
}


void mexFunction(int nrhs, mxArray *plhs[], int nlhs, const mxArray *prhs[])
{
    
    if (nlhs != 3)
        mexErrMsgTxt("Apply mask requires three input arguments");
    
    if (nrhs != 1)
        mexErrMsgTxt("Apply mask requires one output argument");
    
    const mxArray *img = prhs[0];
    const mxArray *img1 = prhs[1];
    const mxArray *img2 = prhs[2];
    if (!mxIsDouble(img) && !mxIsUint8(img))
        mexErrMsgTxt("Apply mask can only accept images of type 'double' or 'uint8'");
    
     if (!mxIsDouble(img1) && !mxIsUint8(img1))
        mexErrMsgTxt("Apply mask can only accept images of type 'double' or 'uint8'");
    
     if (!mxIsDouble(img2) && !mxIsUint8(img2))
        mexErrMsgTxt("Apply mask can only accept images of type 'double' or 'uint8'");
    
    mwSize ndims = mxGetNumberOfDimensions(img);
    const mwSize *dims = mxGetDimensions(img);

    int height   = dims[0];
    int width    = dims[1];
 
    mxClassID input_type = mxGetClassID(img);
 
    mxArray *output = mxCreateNumericArray(ndims, dims, input_type, mxREAL);
    plhs[0] = output;

    
    if (mxIsUint8(img) && mxIsUint8(img1) && mxIsUint8(img2))
    {
        unsigned char *img_ptr = (unsigned char *)mxGetData(img);
        unsigned char *img1_ptr = (unsigned char *)mxGetData(img1);
        unsigned char *img2_ptr = (unsigned char *)mxGetData(img2);
        unsigned char *out_ptr = (unsigned char *)mxGetData(output);
        
        mxArray   *new_number, *str, *new_number2, *str2;

        invertUint8(width, height, img_ptr, img1_ptr, img2_ptr, out_ptr);

    
   }

}