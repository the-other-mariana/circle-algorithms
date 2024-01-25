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

void algo2(Mat* img, int radius, int cx, int cy) {
	for (int x = -radius; x < radius; x++) {
    		int height = (int)isqrt(radius * radius - x * x);
    		for (int y = -height; y < height; y++)
        		img->at<uchar>(x + cx, y + cy) = 255;
	}
}

void algo3(Mat* img, int radius, int cx, int cy) {

	int x = radius;
    	int y = 0;
    	int xChange = 1 - (radius << 1);
    	int yChange = 0;
    	int radiusError = 0;

	while (x >= y) {
		for (int i = cx - x; i <= cx + x; i++)
		{
		    img->at<uchar>(i, cy + y) = 255;
		    img->at<uchar>(i, cy - y) = 255;
		}
		for (int i = cx - y; i <= cx + y; i++)
		{
		    img->at<uchar>(i, cy + x);
		    img->at<uchar>(i, cy - x);
		}

		y++;
		radiusError += yChange;
		yChange += 2;
		if (((radiusError << 1) + xChange) > 0)
		{
		    x--;
		    radiusError += xChange;
		    xChange += 2;
		}
	}

} 
int main() {
	Mat matrix1(500, 500, CV_8U, cv::Scalar(0));
	algo3(&matrix1, 5, 100, 100);
	imwrite("algo1.png", matrix1);
	
	Mat matrix2(500, 500, CV_8U, cv::Scalar(0));
	algo3(&matrix2, 5, 100, 100);
	imwrite("algo2.png", matrix2);


	Mat matrix3(500, 500, CV_8U, cv::Scalar(0));
	algo3(&matrix3, 5, 100, 100);
	imwrite("algo3.png", matrix3);
}
