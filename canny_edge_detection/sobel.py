import numpy as np
import cv2

img = cv2.imread('lena.jpg')
sobelx = cv2.Sobel(img, cv2.CV_64F, 1, 0, ksize = 3)


cv2.imwrite('test.jpg', sobelx)
print(sobelx[0,1:10])