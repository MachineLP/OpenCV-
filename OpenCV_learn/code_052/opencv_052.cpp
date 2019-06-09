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

	// ȥ�������ֵ��
	Mat dst, gray, binary;
	Canny(src, binary, 80, 160, 3, false);
	imshow("binary", binary);
	imwrite("./binary.png", binary);

	Mat k = getStructuringElement(MORPH_RECT, Size(3, 3), Point(-1, -1));
	dilate(binary, binary, k);

	// �������������
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(binary, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point());
	for (size_t t = 0; t < contours.size(); t++) {
		// ��С�������
		RotatedRect rrt = minAreaRect(contours[t]);
		float w = rrt.size.width;
		float h = rrt.size.height;
		Point2f pts[4];
		rrt.points(pts);

		// ������ݱ�
		float ratio = min(w, h) / max(w, h);
		Point2f cpt = rrt.center;
		circle(src, cpt, 2, Scalar(255, 0, 0), 2, 8, 0);
		if (ratio > 0.9) {
			circle(src, cpt, 2, Scalar(255, 0, 0), 2, 8, 0);
			// ������ת����������λ��
			for (int i = 0; i < 4; i++) {
				line(src, pts[i % 4], pts[(i + 1) % 4], Scalar(0, 0, 255), 2, 8, 0);
			}
		} 
		if (ratio < 0.5) {
			circle(src, cpt, 2, Scalar(255, 0, 0), 2, 8, 0);
			// ������ת����������λ��
			for (int i = 0; i < 4; i++) {
				line(src, pts[i % 4], pts[(i + 1) % 4], Scalar(0, 255, 0), 2, 8, 0);
			}
		}
	}
	imshow("contours", src);

	waitKey(0);
	return 0;
}