//
// Created by julian on 12/9/19.
//

#include<opencv2/core.hpp>
#include<opencv2/highgui.hpp>
#include<iostream>
#include <opencv2/imgproc.hpp>

//鼠标点击事件
void clickOnImage(int event,int x,int y,int flags,void* callBackRef);

int main(){
    cv::Mat image;
    std::string winName="Original Image";//后面的三个winname名称需一致
    image=cv::imread("../yan.png");
    cv::namedWindow(winName);
    //鼠标点击响应事件绑定
    cv::setMouseCallback(winName,clickOnImage,reinterpret_cast<void*>(&image));
    //绘图
    cv::circle(image,
               cv::Point(256,289),//中心
               65,//半径
               0,//颜色
               3);//厚度
    //文本
    cv::putText(image,
                "This is a chair!",//文本
                cv::Point(256,289),//位置
                cv::FONT_HERSHEY_PLAIN,//字体类型
                2.0,//字体大小
                255,//字体颜色
                2//文本厚度
    );
    cv::imshow(winName,image);

    cv::waitKey(0);
    return 0;
}

//鼠标点击事件
void clickOnImage(int event,int x,int y,int flags,void* callBackRef){
    cv::Mat *im=reinterpret_cast<cv::Mat*>(callBackRef);
    switch (event){
        //显示像素
        case cv::EVENT_LBUTTONDOWN://鼠标左键按下
            std::cout<<"at ("<<x<<","<<y<<" ) value is: "
                     << static_cast<int>(im->at<uchar>(cv::Point(x,y)))<<std::endl;//打印(x,y)出的像素值
            break;
    }
}
