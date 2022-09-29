#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp>


using namespace cv;
using namespace std;

int main(int argc, char** argv){
    //leer el archivo de la imagen
    Mat image= imread("D:/Desktop/Proyecto 1/prueba.jpg");

    if (image.empty()){
        cout <<"no se encontro la imagen"<< endl<
        cin.get();
        return -1;
    }

    Mat image_blurred_with_5x5_kernel;
    GaussianBlur(image, image_blurred_with_5x5_kernel, Size(5, 5), 0);

    String window_name= "Gaussian";
    String window_name_blurred_with_5x5_kernel = "Lotus Blurred with 5 x 5 Gaussian Kernel";


    namedWindow(window_name);
    namedWindow(window_name_blurred_with_5x5_kernel);

    imshow(window_name, image);

    imshow(window_name_blurred_with_5x5_kernel, image_blurred_with_5x5_kernel);

    waitKey(0); // Wait for any keystroke in the window

    destroyAllWindows(); //destroy all opened windows

    return 0;

}