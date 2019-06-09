#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <math.h>
using namespace cv;
using namespace std;
void open_demo();
void close_demo();
int main(int argc, char** argv)
{
	close_demo();
	waitKey(0);
	return 0;
}

void open_demo() {
	Mat dresult, eresult;
	Mat src = imread("./test.png");
	imshow("input", src);

	// ��ֵͼ��
	Mat gray, binary;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	threshold(gray, binary, 0, 255, THRESH_BINARY_INV | THRESH_OTSU);
	imshow("binary", binary);

	// ����ṹԪ��
	Mat se = getStructuringElement(MORPH_RECT, Size(20, 1), Point(-1, -1));
	morphologyEx(binary, binary, MORPH_OPEN, se);

	vector<vector<Point>> contours;
	vector<Vec4i> hierarhy;
	findContours(binary, contours, hierarhy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(-1, -1));
	for (size_t t = 0; t < contours.size(); t++) {
		Rect roi = boundingRect(contours[t]);
		roi.y = roi.y - 10;
		roi.height = 12;
		rectangle(src, roi, Scalar(0, 0, 255), 1, 8, 0);
	}
	// ��ʾ
	imshow("open demo", src);
}

void close_demo() {
	Mat src = imread("./test.png");
	namedWindow("input", WINDOW_AUTOSIZE);
	imshow("input", src);

	// ͼ���ֵ��
	Mat gray, binary;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	threshold(gray, binary, 0, 255, THRESH_BINARY | THRESH_OTSU);

	// �ղ���
	// Mat se = getStructuringElement(MORPH_ELLIPSE, Size(15, 15), Point(-1, -1));
	Mat se = getStructuringElement(MORPH_RECT, Size(25, 25), Point(-1, -1));
	morphologyEx(binary, binary, MORPH_CLOSE, se);
	imwrite("D:/close.png", binary);
	imshow("close", binary);
}