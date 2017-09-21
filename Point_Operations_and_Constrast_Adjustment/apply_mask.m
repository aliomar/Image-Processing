mex apply_mask.cpp
img = imread('bridge.png');
img1 = imread('fish.png');
img2 = imread('mask.png');
out = apply_mask(img, img1, img2);
imshow(img); title('masked.jpg');
imshow(out); title('Masked Image');