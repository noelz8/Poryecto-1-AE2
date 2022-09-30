#ifndef IMAGEPROCESSING_HPP
#define IMAGEPROCESSING_HPP

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <vector>

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

        //vector<uchar> array(image.rows*image.cols*image.channels());
        //array = image.data;

        
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
        return 1;
    }


    int brightControl(int bright){

        Mat img_out;
        image.convertTo(img_out, -1, 1, bright);
        imshow("Salida", img_out);
        waitKey(0);
        return 1;

    }


    int gray_scale(){
    
        Mat img_out;
        //Mat image = imread(path);
        cvtColor(image, img_out,COLOR_BGR2GRAY);
        imshow("Entrada", image);
        imshow("Salida", img_out);
        //cout << image.rows << " " << image.cols << "\n";

        waitKey(0);

        return 1;

    }

    int prueba(){
        
        for(int j = 0; j<image.cols; j++)
            for(int i = 0; i<image.rows; i++)
                array[i][j] = (array[i][j]+5);

        
        return 1;                
    }
};
#endif

    

    
    



