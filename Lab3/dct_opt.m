image = imread('lab3_starter/lena_gray.bmp');
block = double(image(1:8,1:8));
dct_res = zeros(8,8);
dctint8 = round(dctmtx(8) * 2^14.5);
for i = 1:8
    % dct_res(i,:) = dct(block(i,:));
    dct_res(i,:) = dctint8 * block(i,:)';
    dct_res(i,:) = bitshift(int32(dct_res(i,:)) + bitshift(1, 12), -13);
end
for i = 1:8
    % dct_res(:,i) = dct(dct_res(:,i));
    dct_res(:,i) = dctint8 * dct_res(:,i);
    dct_res(:,i) = bitshift(int32(dct_res(:,i)) + bitshift(1, 12), -13);
end
dct_expected = dct2(block);
idct_res = zeros(8,8);
for i = 1:8
    % idct_res(i,:) = idct(dct_expected(i,:));
    idct_res(i,:) = dctint8' * dct_res(i,:)';
    idct_res(i,:) = bitshift(int32(idct_res(i,:)), -16);
end
for i = 1:8
    % idct_res(:,i) = idct(idct_res(:,i));
    idct_res(:,i) = dctint8' * idct_res(:,i);
    idct_res(:,i) = bitshift(int32(idct_res(:,i)), -16);
end
% isequal(uint8(idct_res), uint8(block))
