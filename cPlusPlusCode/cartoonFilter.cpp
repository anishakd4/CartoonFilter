#include<opencv2/imgproc.hpp>
#include<opencv2/photo.hpp>
#include<opencv2/highgui.hpp>
#include<iostream>

using namespace cv;
using namespace std;

int main(){

    //Read input image
    Mat image = imread("../assets/anish.jpg");

    //check if image exists
    if (image.empty()){
        cout<<"can not find image"<<endl;
        return 0;
    }

    //Convert to gray scale
    Mat grayImage;
    cvtColor(image, grayImage, COLOR_BGR2GRAY);

    //apply gaussian blur
    GaussianBlur(grayImage, grayImage, Size(3, 3), 0);

    //find edges
    Mat edgeImage;
    Laplacian(grayImage, edgeImage, -1, 5);
    convertScaleAbs(edgeImage, edgeImage);

    //invert the image
    edgeImage = 255 - edgeImage;

    //apply thresholding
    threshold(edgeImage, edgeImage, 150, 255, THRESH_BINARY);

    //blur images heavily using edgePreservingFilter
    Mat edgePreservingImage;
    edgePreservingFilter(image, edgePreservingImage, 2, 50, 0.4);

    // Create a output Matrix
    Mat output;
    output = Scalar::all(0);

    // Combine the cartoon and edges
    cv::bitwise_and(edgePreservingImage, edgePreservingImage, output, edgeImage);

    //create windows to display images
    namedWindow("image", WINDOW_AUTOSIZE);
    namedWindow("cartoon", WINDOW_AUTOSIZE);

    //display images
    imshow("image", image);
    imshow("cartoon", output);

    //press Esc to exit the program
    waitKey(0);

    //close all the opened windows
    destroyAllWindows();

    return 0;
}