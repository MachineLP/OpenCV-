#include <opencv2/opencv.hpp>
#include<iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {

	VideoCapture capture(0);

	if (!capture.isOpened()) {
		printf("could not open camera...\n");
		return -1;
	}
	namedWindow("input", WINDOW_AUTOSIZE);
	namedWindow("mask", WINDOW_AUTOSIZE);

	int fps = capture.get(CAP_PROP_FPS);
	int width = capture.get(CAP_PROP_FRAME_WIDTH);
	int height = capture.get(CAP_PROP_FRAME_HEIGHT);
	int num_of_frames = capture.get(CAP_PROP_FRAME_COUNT);
	printf("frame width: %d, frame height: %d, FPS : %d \n", width, height, fps);
	Ptr<BackgroundSubtractor> pMOG2 = createBackgroundSubtractorMOG2(500, 1000, false);
	Mat frame, mask, back_img;
	while (true) {
		bool ret = capture.read(frame);
		if (!ret) break;
		pMOG2->apply(frame, mask);
		pMOG2->getBackgroundImage(back_img);
		imshow("input", frame);
		imshow("mask", mask);
		imshow("back ground image", back_img);
		char c = waitKey(5);
		if (c == 27) {
			break;
		}
	}

	waitKey(0);
	return 0;
}