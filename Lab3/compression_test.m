image = double(imread('lena.jpg'));
% image must be double rather than uint8
[H, W] = size(image);
if H == W
    dct_basis = dctmtx(512);
    image_dct = dct_basis * image * dct_basis';
    image_recover = dct_basis' * image_dct * dct_basis;
else
    image_dct = dct2(image);
    image_recover = idct2(image_dct);
end
imwrite(uint8(image_dct), 'lena_dct_test.jpg');
imwrite(uint8(rescale(image_recover,0,255)), 'lena_recover_test.jpg');
