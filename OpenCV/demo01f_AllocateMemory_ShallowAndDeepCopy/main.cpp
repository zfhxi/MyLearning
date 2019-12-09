//
// Created by julian on 12/9/19.
//

#include<iostream>
#include<opencv2/core.hpp>
#include<opencv2/highgui.hpp>


//创建图像并返回
cv::Mat function(){
    cv::Mat img(500,500,CV_8U,50);
    return img;
}

int main(){

    std::string winName="Image";
    std::string imgFilePath="../yan.png";
    //创建一个图像，大小240x320,矩阵元素类型CV_8U(1字节，灰度图),像素值100
    cv::Mat image1(240,320,CV_8U,100);
    cv::imshow(winName,image1);
    cv::waitKey(0);

    //重新分配一个新图像(原来分配的内容将被释放)
    //内存一旦无Mat对象引用，那么会被释放。实现原理：计数引用和浅拷贝
    image1.create(200,200,CV_8U);
    image1=200;
    cv::imshow(winName,image1);
    cv::waitKey(0);

    //创建一个红色图像 BGR通道
    cv::Mat image2(240,320,CV_8UC3,cv::Scalar(0,0,255));
    /*//等价写法
    cv::Mat image2(240,320,CV_8UC3);
    image2=cv::Scalar(0,0,255);*/
    cv::imshow(winName,image2);
    cv::waitKey(0);

    //读入一幅图像
    cv::Mat image3=cv::imread(imgFilePath);
    //浅拷贝，所有图像指向同一个数据块
    cv::Mat image4(image3);
    image1=image3;

    //深拷贝，这些图像都是源图像的副本
    image3.copyTo(image2);
    cv::Mat image5=image3.clone();

    //转换图像进行测试
    cv::flip(image3,image3,1);

    //检查哪些图像在处理过程中收到影响
    cv::imshow("Image 3",image3);
    cv::imshow("Image 1",image1);
    cv::imshow("Image 2",image2);
    cv::imshow("Image 4",image4);
    cv::imshow("Image 5",image5);
    cv::waitKey(0);

    //从函数中获取一个灰度图像
    cv::Mat grayScaleImg=function();
    cv::imshow("Image",grayScaleImg);
    cv::waitKey(0);

    //作为灰度图像读入
    //如果两幅图像的通道数相同而类型不一样，拷贝时需要进行类型转换。
    image1=cv::imread(imgFilePath,CV_LOAD_IMAGE_GRAYSCALE);
    image1.convertTo(image2,CV_32F,1/255.0,0.0);
    cv::imshow("Image",image2);
    cv::waitKey(0);

    return 0;
}
