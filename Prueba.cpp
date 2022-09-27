#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "ImageProcessing.hpp"
#include "errno.h"
#include <iostream>
#include <stdio.h>


using namespace std;
using namespace cv;

int main()
{
    Image img;
    img.read("Images/in.bmp");
    img.horizontalScale(2.0);
    img.write("Images/out.bmp");
    img.clear();
    //string path = "Images/K-on.jpg";
    //Mat img = imread(path);
    //imshow("Image", img);
    //waitKey(0);
    return 0; 
    
}   
