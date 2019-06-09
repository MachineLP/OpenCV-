#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, const char *argv[])
{
	Mat src = imread("./test.jpg");
	if (src.empty()) {
		printf("could not load image...\n");
		return -1;
	}
	namedWindow("input", WINDOW_AUTOSIZE);
	imshow("input", src);

	// ��ֵ��
	Mat dst, gray, binary;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	threshold(gray, binary, 0, 255, THRESH_BINARY | THRESH_OTSU);

	// ɾ�����ſ�
	Mat k = getStructuringElement(MORPH_RECT, Size(3, 3), Point(-1, -1)); 
	morphologyEx(binary, binary, MORPH_OPEN, k);
	imshow("binary", binary);

	// �������������
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(binary, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point());
	for (size_t t = 0; t < contours.size(); t++) { 
		vector<Point> hull;
		convexHull(contours[t], hull);
		bool isHull = isContourConvex(contours[t]);
		printf("test convex of the contours %s", isHull?"Y":"N");
		int len = hull.size();
		for (int i = 0; i < hull.size(); i++) {
			circle(src, hull[i], 4, Scalar(255, 0, 0), 2, 8, 0);
			line(src, hull[i%len],hull[(i+1)%len], Scalar(0, 0, 255), 2, 8, 0);
		}
	}
	imshow("contours", src); 

	waitKey(0);
	return 0;
}