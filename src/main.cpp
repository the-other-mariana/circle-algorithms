#include <opencv2/opencv.hpp>
#include <iostream>
#include <random>
#include <chrono>
#include <cmath>

#define ALGORITHMS 6


using namespace std;
using namespace cv;

int isqrt(int x) {
    int r = x;
    while (r * r > x) {
        r = (r + x / r) / 2;
    }
    return r;
}

void algo1(Mat* img, int radius, int cx, int cy, uint8_t color) {
	for(int y=-radius; y<=radius; y++)
    		for(int x=-radius; x<=radius; x++)
        		if(x*x+y*y <= radius*radius)
            			img->at<uchar>(cx+x, cy+y) = color;
}

void algo2(Mat* img, int radius, int cx, int cy, uint8_t color) {
	for (int x = -radius; x < radius; x++) {
    		int height = (int)isqrt(radius * radius - x * x);
    		for (int y = -height; y < height; y++)
        		img->at<uchar>(x + cx, y + cy) = color;
	}
}

void algo3(Mat* img, int radius, int cx, int cy, uint8_t color) {

	int x = radius;
    	int y = 0;
    	int xChange = 1 - (radius << 1);
    	int yChange = 0;
    	int radiusError = 0;

	while (x >= y) {
		for (int i = cx - x; i <= cx + x; i++)
		{
		    img->at<uchar>(i, cy + y) = color;
		    img->at<uchar>(i, cy - y) = color;
		}
		for (int i = cx - y; i <= cx + y; i++)
		{
		    img->at<uchar>(i, cy + x) = color;
		    img->at<uchar>(i, cy - x) = color;
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

void algo4(Mat* img, int radius, int cx, int cy, uint8_t color) {
	for (int x = -radius; x < radius ; x++) {
		int hh = (int)isqrt(radius * radius - x * x);
		int rx = cx + x;
		int ph = cy + hh;
		for (int y = cy-hh; y < ph; y++)
        		img->at<uchar>(rx, y) = color;
	}
}

void algo5(Mat* img, int radius, int cx, int cy, uint8_t color) {
	int r2 = radius * radius;
	int area = r2 << 2;
	int rr = radius << 1;

	for (int i = 0; i < area; i++) {
    		int tx = (i % rr) - radius;
    		int ty = (i / rr) - radius;

    		if (tx * tx + ty * ty <= r2)
        		img->at<uchar>(cx + tx, cy + ty) = color;
	}
}

void algo6(Mat* img, int radius, int cx, int cy, uint8_t color) {
	for (int r = 1; r < radius; r += 1) {
		for (double a = 0.0; a < 360.0; a += 5.0) {
			int x = cx + r * cos(a * 3.1416 / 180.0);
			int y = cy + r * sin(a * 3.1416 / 180.0);
			img->at<uchar>(x, y) = color;
		}
	}
}
 
int main(int argc, char* argv[]) {

	if (argc != 2) {
        	std::cerr << "Usage: " << argv[0] << " <integer_argument>" << std::endl;
        	return 1;  // Exit with an error code
    	}	

	void (*functionArray[])(Mat*, int, int, int, uint8_t) = {algo1, algo2, algo3, algo4, algo5, algo6};
	random_device rd;
    	mt19937 gen(rd());
	int maxX = 400;
	int maxY = 400;

	int CIRCLES = stoi(argv[1]);
	cout << "algorithm_id, time(ms), calls" << endl;
	int radius = 20;
	for (uint8_t i = 0; i < ALGORITHMS; i++) {
		cv::Mat* matrix = new cv::Mat(maxX, maxY, CV_8U, cv::Scalar(0));
		auto iteration_start = std::chrono::high_resolution_clock::now();
		for (int r = 0; r < CIRCLES; r++) {
			int x = uniform_int_distribution<int>(radius + 1, maxX - radius - 1)(gen);
        		int y = uniform_int_distribution<int>(radius + 1, maxY - radius - 1)(gen);

			uint8_t color = uniform_int_distribution<int>(20, 255)(gen);
			functionArray[i](matrix, radius, x, y, color);
		}
		auto iteration_end = std::chrono::high_resolution_clock::now();
        	auto iteration_duration = std::chrono::duration_cast<std::chrono::microseconds>(iteration_end - iteration_start);
		cout << (i+1) << ", " << iteration_duration.count() << ", " << CIRCLES << endl;
		imwrite("images/algotest_" + to_string(i+1) + "_" + to_string(CIRCLES) + ".png", *matrix);
		delete matrix;
	}
}
