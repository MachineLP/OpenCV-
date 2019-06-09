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

	// ת��Ϊ�Ҷ�ͼ��
	int T = 127;
	Mat gray, binary;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	for (int i = 0; i < 5; i++) {
		threshold(gray, binary, T, 255, i);
		imshow(format("binary_%d" , i), binary);
		imwrite(format("./binary_%d.png", i), binary);
	}
	waitKey(0);
	return 0;
}