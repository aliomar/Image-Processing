mex apply_point_tfrm.cpp
img = imread('183087.jpg');
out = apply_point_tfrm(img);
imshow(img); title('183087.jpg');
imshow(out); title('Point transformed image');