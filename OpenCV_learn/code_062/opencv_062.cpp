#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <math.h>
using namespace cv;
using namespace std;
int main(int argc, char** argv)
{
	Mat dresult, eresult;
	Mat src = imread("./test.jpg");
	imshow("input", src);
	// ����ṹԪ�� 3x3��С����
	Mat se = getStructuringElement(MORPH_RECT, Size(3, 3), Point(-1, -1));
	// ����
	dilate(src, dresult, se, Point(-1, -1), 1, 0);
	// ��ʴ
	erode(src, eresult, se, Point(-1, -1), 1, 0);
	
	// ��ʾ
	imshow("dilate", dresult);
	imshow("erode", eresult);
	waitKey(0);
	return 0;
}