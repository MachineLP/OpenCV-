#include <opencv2/opencv.hpp>
#include<iostream>

using namespace cv;
using namespace std;
void process_frame(Mat &image, int opts);
Ptr<BackgroundSubtractor> pMOG2 = createBackgroundSubtractorMOG2(500, 100, false);
int main(int argc, char** argv) {
	VideoCapture capture(0);

	if (!capture.isOpened()) {
		printf("could not open camera...\n");
		return -1;
	}
	namedWindow("input", WINDOW_AUTOSIZE);
	namedWindow("result", WINDOW_AUTOSIZE);

	int fps = capture.get(CAP_PROP_FPS);
	int width = capture.get(CAP_PROP_FRAME_WIDTH);
	int height = capture.get(CAP_PROP_FRAME_HEIGHT);
	int num_of_frames = capture.get(CAP_PROP_FRAME_COUNT);
	printf("frame width: %d, frame height: %d, FPS : %d \n", width, height, fps);
	
	Mat frame;
	while (true) {
		bool ret = capture.read(frame);
		imshow("input", frame);
		if (!ret) break;
		
		process_frame(frame, 0);
		imshow("result", frame);
		char c = waitKey(5);
		if (c == 27) {
			break;
		}
	}

	waitKey(0);
	return 0;
}


void process_frame(Mat &image, int opts) {
	Mat mask;
	pMOG2->apply(image, mask);
	// ����ṹԪ��
	Mat se = getStructuringElement(MORPH_RECT, Size(1, 5), Point(-1, -1));
	morphologyEx(mask, mask, MORPH_OPEN, se);

	// Ѱ���������
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(mask, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	for (size_t t = 0; t < contours.size(); t++) {
		double area = contourArea(contours[t]);
		if (area <100) {
			continue;
		}
		RotatedRect rect = minAreaRect(contours[t]);
		ellipse(image, rect, Scalar(0, 255, 0), 2, 8);
		circle(image, rect.center, 2, Scalar(255, 0, 0), 2, 8, 0);
	}
}
