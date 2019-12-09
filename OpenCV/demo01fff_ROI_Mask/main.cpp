//
// Created by julian on 12/9/19.
//

#include<iostream>
#include<opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <cv.hpp>

int main(){
    std::string imgFilePath="../yan.png";
    std::string tagimgPath="../gexiaolun.png";
    cv::Mat image=cv::imread(imgFilePath);
    cv::Mat tagImg=cv::imread(tagimgPath);

    /*
     * 感兴趣区域ROI
     *
     */
    ///*//左上角区域定义感兴趣区域
    cv::Mat imageROI(image,
                     cv::Rect( 0, 0,//ROI坐标
                               tagImg.cols,tagImg.rows)//ROI大小
    );//*/

    /*//等价于
    cv::Mat imageROI=image(cv::Rect(0,0,tagImg.cols,tagImg.rows));//*/

    //右下角区域定义感兴趣区域
    /*cv::Mat imageROI=image(cv::Range(image.rows-tagImg.rows,image.rows),
                            cv::Range(image.cols-tagImg.cols,image.cols));*/

    /*//定义行组成的ROI
    cv::Mat imageRowROI=image.rowRange(0,tagImg.rows);
    //定义列组成的ROI
    cv::Mat imageColROI=image.colRange(0,tagImg.cols);*/
    //将相对较小的标志图像深拷贝到相对较大的目标图像上
    tagImg.copyTo(imageROI);
    cv::namedWindow("Image");
    cv::imshow("Image Window",image);
    cv::waitKey(0);
    cv::destroyAllWindows();

    /*
     * 使用掩码
     * 掩码中
     */
    //左上角定义感兴趣区域
    cv::Mat imageROI2=image(cv::Rect(0,image.rows-tagImg.rows-200,tagImg.cols,tagImg.rows));
    //将灰度图标志作为掩码
    cv::Mat maskTag=tagImg.clone();//深拷贝一份
    cv::cvtColor(maskTag,maskTag,CV_BGR2GRAY);//转为灰度图
    float meanVal=cv::mean(maskTag).val[0];//求灰度图平均值
    cv::threshold(maskTag,maskTag,meanVal,1,CV_THRESH_BINARY);//二值化为0和1

    //插入标志，只深拷贝不为0的位置
    tagImg.copyTo(imageROI2,maskTag);
    cv::imshow("Image Mask",image);
    cv::waitKey(0);

    return 0;
}
