#include <opencv2/opencv.hpp>
#include<iostream>

using namespace cv;
using namespace std;
void process_frame(Mat &image, int opts);
int main(int argc, char** argv) {
	VideoCapture capture(0);

	if (!capture.isOpened()) {
		printf("could not open camera...\n");
		return -1;
	}
	namedWindow("input", WINDOW_AUTOSIZE);

	int fps = capture.get(CAP_PROP_FPS);
	int width = capture.get(CAP_PROP_FRAME_WIDTH);
	int height = capture.get(CAP_PROP_FRAME_HEIGHT);
	int num_of_frames = capture.get(CAP_PROP_FRAME_COUNT);

	printf("frame width: %d, frame height: %d, FPS : %d \n", width, height, fps);

	Mat frame;
	int index = 0;
	while (true) {
		bool ret = capture.read(frame);
		if (!ret) break;
		imshow("input", frame);
		char c = waitKey(50);
		process_frame(frame, index);
		imshow("result", frame);
		if (c == 27) {
			break;
		}
	}
	waitKey(0);
	return 0;
}

void process_frame(Mat &image, int opts) {
	Mat hsv, mask;
	cvtColor(image, hsv, COLOR_BGR2HSV);
	// ����ṹԪ��
	Mat se = getStructuringElement(MORPH_RECT, Size(15, 15), Point(-1, -1));
	inRange(hsv, Scalar(0, 43, 46), Scalar(10, 255, 255), mask);
	morphologyEx(mask, mask, MORPH_OPEN, se);

	// Ѱ���������
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(mask, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	int index = -1;
	int max = 0;
	for (size_t t = 0; t < contours.size(); t++) {
		double area = contourArea(contours[t]);
		if (area > max) {
			max = area;
			index = t;
		}
	}
	// Ѱ����С��Ӿ���
	if (index >= 0) {
		RotatedRect rect = minAreaRect(contours[index]);
		ellipse(image, rect, Scalar(0, 255, 0), 2, 8);
		circle(image, rect.center, 2, Scalar(255, 0, 0), 2, 8, 0);
	}
}
