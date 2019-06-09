#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <math.h>
using namespace cv;
using namespace std;
int main(int argc, char** argv)
{
	Mat src = imread("./test.jpg");
	imshow("input", src);

	// ��ֵͼ��
	Mat gray, binary, result;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	threshold(gray, binary, 0, 255, THRESH_BINARY_INV | THRESH_OTSU);
	imshow("binary", binary);

	// ����ṹԪ��
	Mat se = getStructuringElement(MORPH_RECT, Size(3, 3), Point(-1, -1));
	morphologyEx(binary, binary, MORPH_OPEN, se);

	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(binary, contours, hierarchy, RETR_LIST,  CHAIN_APPROX_SIMPLE);
	int height = src.rows;
	for (size_t t = 0; t < contours.size(); t++) {
		Rect rect = boundingRect(contours[t]);
		double area = contourArea(contours[t]);
		if (rect.height > (height / 2)) {
			continue;
		}
		if (area < 150)
			continue;
		rectangle(src, rect, Scalar(0, 0, 255), 1, 8, 0);
		drawContours(src, contours, t, Scalar(0, 255, 0), 2, 8);
	}
	// ��ʾ
	imshow("result", src);
	waitKey(0);
	return 0;
}