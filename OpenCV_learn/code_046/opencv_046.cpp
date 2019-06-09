#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

RNG rng(12345);
void connected_component_demo(Mat &image);
int main(int argc, char** argv) {
	Mat src = imread("./test.png");
	if (src.empty()) {
		printf("could not load image...\n");
	}
	imshow("input", src);
	connected_component_demo(src);

	waitKey(0);
	return 0;
}

void connected_component_demo(Mat &image) {
	// extract labels
	Mat gray, binary;
	GaussianBlur(image, image, Size(3, 3), 0);
	cvtColor(image, gray, COLOR_BGR2GRAY);
	threshold(gray, binary, 0, 255, THRESH_BINARY | THRESH_OTSU);
	Mat labels = Mat::zeros(image.size(), CV_32S);
	int num_labels = connectedComponents(binary, labels, 8, CV_32S);
	printf("total labels : %d\n", (num_labels - 1));
	vector<Vec3b> colors(num_labels);

	// background color
	colors[0] = Vec3b(0, 0, 0);

	// object color
	for (int i = 1; i < num_labels; i++) {
		colors[i] = Vec3b(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
	}

	// render result
	Mat dst = Mat::zeros(image.size(), image.type());
	int w = image.cols;
	int h = image.rows;
	for (int row = 0; row < h; row++) {
		for (int col = 0; col < w; col++) {
			int label = labels.at<int>(row, col);
			if (label == 0) continue;
			dst.at<Vec3b>(row, col) = colors[label];
		}
	}
	imshow("ccla-demo", dst);
	imwrite("./ccla_dst.png", dst);
}
