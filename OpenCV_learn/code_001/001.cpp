#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int artc, char** argv) {
	// Mat src = imread("D:/vcprojects/images/test.png");
	Mat src = imread("./test.png", IMREAD_GRAYSCALE);

	if (src.empty()) {
		printf("could not load image...\n");
		return -1;
	}
	namedWindow("input", CV_WINDOW_AUTOSIZE);
	imshow("input", src);

	waitKey(0);
	return 0;
}



