#ifndef IMAGEPROCESSING_HPP
#define IMAGEPROCESSING_HPP

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <vector>
#include <cmath>

using namespace cv;
using namespace std;

class ImageProcessing{
public:
    Mat image;
    uchar **array;

    bool read(const char* file){
        
        image = imread(file);

        if(image.empty()){

            return false;

        }
        
        return true;

    }

    bool matToArray(const char* file){

        
        if(file == NULL){

            cout << "Imagen no encontrada\n";

        }
        image = imread(file);
        array = new uchar*[image.rows];
        for(int i=0; i<image.rows; i++)
            array[i] = new uchar[image.cols*image.channels()];
        for (int i=0; i<image.rows; i++)
            array[i] = image.ptr<uchar>(i);

        return true;
        

    }

    bool arrayToMat(){

        image = Mat(image.rows, image.cols, CV_16S, array);
        //image.data = array[0];
        imshow("Imagen", image);
        waitKey(0);
        return true;
    }

    int gaussianBlur(){

        Mat img_out;
        GaussianBlur(image, img_out, Size(9,9), 10, 0);
        imshow("Salida", img_out);
        waitKey(0);
        return 0;
    }


    int brightControl(int bright){

        Mat img_out;
        image.convertTo(img_out, -1, 1, bright);
        imshow("Salida", img_out);
        waitKey(0);
        return 0;

    }


    int gray_scale(){
    
        Mat img_out;
        cvtColor(image, img_out,COLOR_BGR2GRAY);
        imshow("Salida", img_out);
        waitKey(0);

        return 0;

    }

    int gammaCorrection(int gamma){

        float x = 0.5;

        cvtColor(image, image, COLOR_BGR2RGB);
    
        Mat new_image = Mat(image.size(), image.type());
        int alpha = gamma;
        int beta = 0;

        for (int j = 0; j<image.rows; j++){
            for(int i = 0; i< image.cols; i++){
                for (int c = 0; c <image.channels(); c++){
                    new_image.at<Vec3b>(j, i)[c] = saturate_cast<uchar>(alpha*image.at<Vec3b>(j, i)[c] + beta);
              
                }
            }
        }

        image = new_image;
        imshow("Salida", image);
        waitKey(0);
        return 0;
    }

    int prueba(){
        
        for(int j = 0; j<image.cols; j++)
            for(int i = 0; i<image.rows; i++)
                array[i][j] = (array[i][j]+5);

        
        return 1;                
    }
};
#endif

    

    
    



