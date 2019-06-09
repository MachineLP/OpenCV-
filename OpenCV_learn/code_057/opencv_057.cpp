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

	// ��ֵ��
	Mat dst, gray, binary;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	threshold(gray, binary, 0, 255, THRESH_BINARY | THRESH_OTSU);

	// �������������
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(binary, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point());
	int h = src.rows;
	int w = src.cols;
	Mat image = Mat::zeros(src.size(), CV_32FC3);
	for (int row = 0; row < h; row++) {
		for (int col = 0; col < w; col++) {
			double dist = pointPolygonTest(contours[0], Point(col, row), true);
			if (dist == 0) {
				image.at<Vec3f>(row, col) = Vec3f(255, 255, 255);
			}
			if (dist > 0) {
				image.at<Vec3f>(row, col) = Vec3f(255-dist, 0, 0);
			}
			if (dist < 0) {
				image.at<Vec3f>(row, col) = Vec3f(0, 0, 255+dist);
			}
			
		}
	}
	convertScaleAbs(image, image);
	image.convertTo(image, CV_8UC3);
	imshow("points", image);

	waitKey(0);
	return 0;
}