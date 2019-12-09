//
// Created by julian on 12/9/19.
//

#include<opencv2/core.hpp>
#include<opencv2/highgui.hpp>
#include<iostream>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;

int main(){
    //显示图片
    Mat image;//创建一个空图像
    cout<<"This image is "<<image.rows<<" x "
        <<image.cols<<endl;
    image=imread("../yan.png");//读取输入的图像
    if(image.empty()){
        cout<<"This is an empty image!"<<endl;
    }else{
        cout<<"This image is "<<image.rows<<" x "
            <<image.cols<<endl;
        namedWindow("demo01");//定义窗口
        imshow("demo01_image",image);//显示图像
    }
    waitKey(0);

    //水平翻转图片
    Mat result;
    flip(image,result,1);//正-水平，0-垂直，负-水平和垂直
    namedWindow("Output Image");
    imshow("Output Image",result);
    waitKey(0);

    //保存图片
    //imwrite("flip_output.bmp",result);

    //转为灰度图像
    Mat grayScaleImg;
    grayScaleImg=imread("../yan.png",IMREAD_GRAYSCALE);
    namedWindow("gray scale image");
    imshow("GrayScaleImg",grayScaleImg);
    waitKey(0);

    //再转为三通道彩色图
    Mat colourImg;
    cvtColor(grayScaleImg,colourImg,CV_GRAY2BGR);
    namedWindow("colour image");
    imshow("ColourImg",colourImg);
    waitKey(0);
    cout<<"This image transferred from gray scale image has "
        <<colourImg.channels()<<" channerl(s)"<<endl;

    return 0;
}
