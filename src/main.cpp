#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;
int isqrt(int x) {
    int r = x;
    while (r * r > x) {
        r = (r + x / r) / 2;
    }
    return r;
}

void algo1(Mat* img, int radius, int cx, int cy) {
for(int y=-radius; y<=radius; y++)
    for(int x=-radius; x<=radius; x++)
        if(x*x+y*y <= radius*radius)
            img->at<uchar>(cx+x, cy+y) = 255;
}

int main() {
	Mat matrix(500, 500, CV_8U, cv::Scalar(0));
	algo1(&matrix, 5, 100, 100);
	imwrite("algo1.png", matrix);
}
