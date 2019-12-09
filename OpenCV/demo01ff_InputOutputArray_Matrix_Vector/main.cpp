//
// Created by julian on 12/9/19.
//

#include<iostream>
#include<vector>
#include<opencv2/core/matx.hpp>
#include <opencv2/core.hpp>

//通过InputArray和OutputArray传值实现的仿射变换函数
void myAffineTransform(cv::InputArray _src, cv::OutputArray _dst, cv::InputArray _m);

int main(){
    //InputArray
    //专用于传值而作为形参的代理类。兼容Mat, Mat_<T>, Matx<T, m, n>, std::vector<T>, std::vector<std::vector<T> >,
    //std::vector<Mat>, std::vector<Mat_<T> >, UMat, std::vector<UMat> or double.
    //下面演示InputArray的用法
    std::vector<cv::Point2f> vec;
    std::vector<cv::Point2f> vec1;
    std::vector<cv::Point2f> vec2;
    //points of a circle
    for( int i = 0; i < 30; i++ )
        vec.push_back(cv::Point2f((float)(100 + 30*cos(i*CV_PI*2/5)),
                                  (float)(100 - 30*sin(i*CV_PI*2/5))));
    //将这些点按照Matx23f进行仿射变换
    //其中transform的原形为 void cv::transform(InputArray src, OutputArray dst, InputArray m);
    cv::transform(vec, vec1, cv::Matx23f(0.707, -0.707, 10, 0.707, 0.707, 20));
    //下面演示通过InputArray和OutputArray传值实现的仿射变换函数
    myAffineTransform(vec, vec2, cv::Matx23f(0.707, -0.707, 10, 0.707, 0.707, 20));


    //3x3双精度型矩阵
    cv::Matx33d matrix(3.0,2.0,1.0,
                       2.0,1.0,3.0,
                       1.0,2.0,3.0
    );
    //3x1矩阵（列向量）
    cv::Matx31d vector(5.0,1.0,3.0);
    //相乘的结果
    cv::Matx31d result=matrix*vector;
    //1x3矩阵（行向量）
    cv::Matx13d vector2(5.0,1.0,3.0);
    //相乘的结果
    cv::Matx13d result2=vector2*matrix;
    return 0;
}

//下面演示通过InputArray和OutputArray传值实现的仿射变换函数
void myAffineTransform(cv::InputArray _src, cv::OutputArray _dst, cv::InputArray _m)
{
    // get Mat headers for input arrays. This is O(1) operation,
    // unless _src and/or _m are matrix expressions.
    cv::Mat src = _src.getMat(), m = _m.getMat();
    CV_Assert( src.type() == CV_32FC2 && m.type() == CV_32F && m.size() == cv::Size(3, 2) );
    // [re]create the output array so that it has the proper size and type.
    // In case of Mat it calls Mat::create, in case of STL vector it calls vector::resize.
    _dst.create(src.size(), src.type());
    cv::Mat dst = _dst.getMat();
    for( int i = 0; i < src.rows; i++ )
        for( int j = 0; j < src.cols; j++ )
        {
            cv::Point2f pt = src.at<cv::Point2f>(i, j);
            dst.at<cv::Point2f>(i, j) = cv::Point2f(m.at<float>(0, 0)*pt.x +
                                            m.at<float>(0, 1)*pt.y +
                                            m.at<float>(0, 2),
                                            m.at<float>(1, 0)*pt.x +
                                            m.at<float>(1, 1)*pt.y +
                                            m.at<float>(1, 2));
        }
}
