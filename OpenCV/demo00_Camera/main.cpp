#include<opencv2/opencv.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
using namespace std;
// 视频来源于摄像头
VideoCapture capture(0);
Mat edges;

int main(int argc, const char * argv[]) {
    while (true) {
        Mat frame;
        // 每一帧
        capture >> frame;
        // 转为灰度图
        cvtColor(frame, edges, COLOR_BGR2GRAY);
        blur(edges, edges, Size(7, 7));
        Canny(edges, edges, 0, 30, 3);
        // 边缘检测并显示边缘
        imshow("Read Video", edges);
        // 等待用户输入
        if(waitKey(30) >= 0) break;
    }
    return 0;
}
