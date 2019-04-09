#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int artc, char** argv) {
	Mat src = imread("./test.png");
	if (src.empty()) {
		printf("could not load image...\n");
		return -1;
	}
	namedWindow("input", CV_WINDOW_AUTOSIZE);
	imshow("input", src);

	Mat kernel1 = Mat::ones(5, 5, CV_32F) / (float)(25);

	Mat kernel2 = (Mat_<char>(3, 3) << 0, -1, 0,
		-1, 5, -1,
		0, -1, 0);

	Mat kernel3 = (Mat_<int>(2, 2) << 1, 0, 0, -1);

	Mat dst1, dst2, dst3;
	filter2D(src, dst1, -1, kernel1);
	filter2D(src, dst2, -1, kernel2);
	filter2D(src, dst3, CV_32F, kernel3);
	convertScaleAbs(dst3, dst3);

	imshow("blur=5x5", dst1);
	imshow("shape=3x3", dst2);
	imshow("gradient=2x2", dst3);

	waitKey(0);
	return 0;
}
