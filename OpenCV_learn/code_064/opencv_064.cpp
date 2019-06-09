#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <math.h>
using namespace cv;
using namespace std;
int main(int argc, char** argv)
{
	Mat dresult, eresult;
	Mat src = imread("./test.png");

	// ��ֵͼ��
	Mat gray, binary, result;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	GaussianBlur(gray, gray, Size(9, 9), 0, 0);
	adaptiveThreshold(gray, binary, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY_INV, 45, 15);
	imshow("binary", binary);

	// ����ṹԪ�� 5x5��С����
	Mat se = getStructuringElement(MORPH_RECT, Size(5, 5), Point(-1, -1));
	morphologyEx(binary, result, MORPH_OPEN, se);

	// ��ʾ
	imshow("open demo", result);
	waitKey(0);
	return 0;
}