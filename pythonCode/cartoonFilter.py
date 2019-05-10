import cv2
import sys
import numpy as np

#read image
image = cv2.imread("../assets/anish.jpg")

#check if image exists
if image is None:
    print("can not find image")
    exit()

#convert to gray scale
grayImage = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

#apply gaussian blur
grayImage = cv2.GaussianBlur(grayImage, (3, 3), 0)

#detect edges
edgeImage = cv2.Laplacian(grayImage, -1, ksize=5)
edgeImage = 255 - edgeImage

#threshold image
ret, edgeImage = cv2.threshold(edgeImage, 150, 255, cv2.THRESH_BINARY)

#blur images heavily using edgePreservingFilter
edgePreservingImage = cv2.edgePreservingFilter(image, flags=2, sigma_s=50, sigma_r=0.4)

#create output matrix
output =np.zeros(grayImage.shape)

#combine cartoon image and edges image
output = cv2.bitwise_and(edgePreservingImage, edgePreservingImage, mask=edgeImage)

#create windows to display images
cv2.namedWindow("image", cv2.WINDOW_AUTOSIZE)
cv2.namedWindow("cartoon", cv2.WINDOW_AUTOSIZE)

#display images
cv2.imshow("image", image)
cv2.imshow("cartoon", output)

#press esc to exit program
cv2.waitKey(0)

#close all the opened windows
cv2.destroyAllWindows()