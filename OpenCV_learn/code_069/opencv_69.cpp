#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <math.h>
using namespace cv;
using namespace std;
int main(int argc, char** argv)
{
	Mat basic, exter, inter;
	Mat src = imread("./test.png");
	imshow("input", src);

	// ����ṹԪ��
	Mat se = getStructuringElement(MORPH_RECT, Size(3, 3), Point(-1, -1));
	
	// �����ݶ�
	morphologyEx(src, basic, MORPH_GRADIENT, se);
	imshow("basic gradient", basic);

	// ���ݶ�
	morphologyEx(src, exter, MORPH_DILATE, se);
	subtract(exter, src, exter);
	imshow("external gradient", exter);

	// ���ݶ�
	morphologyEx(src, inter, MORPH_ERODE, se);
	subtract(src, inter, inter);
	imshow("internal gradient", exter);

	waitKey(0);
	return 0;
}