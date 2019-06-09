#include <opencv2/opencv.hpp>
#include <math.h>
using namespace cv;
using namespace std;
int main(int argc, char** argv)
{
	Mat hsv, mask, result;
	Mat src = imread("./test.png");
	if (src.empty()) {
		printf("could not load image...\n");
		return -1;
	}
	cvtColor(src, hsv, COLOR_BGR2HSV);

	// mask
	inRange(hsv, Scalar(100, 43, 46), Scalar(124, 255, 255), mask);
	Mat se = getStructuringElement(MORPH_RECT, Size(5, 5), Point(-1, -1));
	dilate(mask, mask, se);
	imshow("mask", mask);

	// �޸�
	inpaint(src, mask, result, 3, INPAINT_TELEA);
	imshow("result", result);
	waitKey(0);
	return 0;
}