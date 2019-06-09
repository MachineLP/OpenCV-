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
	threshold(gray, binary, 0, 255, THRESH_BINARY | THRESH_OTSU);
	imshow("binary", binary);

	// ����ṹԪ�� 5x5��С����
	Mat se1 = getStructuringElement(MORPH_RECT, Size(25, 5), Point(-1, -1));
	Mat se2 = getStructuringElement(MORPH_RECT, Size(5, 25), Point(-1, -1));
	morphologyEx(binary, result, MORPH_CLOSE, se1);
	morphologyEx(result, result, MORPH_CLOSE, se2);

	// ��ʾ
	imshow("open demo", result);
	waitKey(0);
	return 0;
}