#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <math.h>
using namespace cv;
using namespace std;
int main(int argc, char** argv)
{
	Mat src = imread("./test.png");
	imshow("input", src);

	// ��ֵͼ��
	Mat gray, binary;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	threshold(gray, binary, 0, 255, THRESH_BINARY | THRESH_OTSU);
	imshow("binary", binary);

	// ����ṹԪ��
	Mat se = getStructuringElement(MORPH_RECT, Size(3, 3), Point(-1, -1));
	morphologyEx(binary, binary, MORPH_CLOSE, se);

	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(binary, contours, hierarchy, RETR_LIST, CHAIN_APPROX_SIMPLE);
	int height = src.rows;
	int width = src.cols;
	int index = -1;
	int max = 0;
	for (size_t t = 0; t < contours.size(); t++) {
		Rect rect = boundingRect(contours[t]);
		if (rect.height >= height || rect.width >= width) {
			continue;
		}
		double area = contourArea(contours[t]);
		if (area > max) {
			max = area;
			index = t;
		}
	}
	Mat result = Mat::zeros(src.size(), src.type());
	Mat pts;
	drawContours(src, contours, index, Scalar(0, 0, 255), 1, 8);
	approxPolyDP(contours[index], pts, 4, true);
	for (int i = 0; i < pts.rows; i++) {
		Vec2i pt = pts.at<Vec2i>(i, 0);
		circle(src, Point(pt[0], pt[1]), 2, Scalar(0, 255, 0), 2, 8, 0);
		circle(result, Point(pt[0], pt[1]), 2, Scalar(0, 255, 0), 2, 8, 0);
	}
	imshow("result", src);
	waitKey(0);
	return 0;
}