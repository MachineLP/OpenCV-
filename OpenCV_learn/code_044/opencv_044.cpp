#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, const char *argv[])
{
	Mat src = imread("./test.png");
	if (src.empty()) {
		printf("could not load image...\n");
		return -1;
	}
	namedWindow("input", WINDOW_AUTOSIZE);
	imshow("input", src);

	// �Զ���ֵѰ�����ֵ��
	Mat gray, binary;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	adaptiveThreshold(gray, binary, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 25, 10);

	imshow("binary", binary);
	imwrite("./test.png", binary);

	waitKey(0);
	return 0;
}