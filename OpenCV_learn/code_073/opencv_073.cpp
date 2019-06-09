#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <math.h>
using namespace cv;
using namespace std;
void sort_box(vector<Rect> &boxes);
Mat get_template(Mat &binary, vector<Rect> rects);
void detect_defects(Mat &binary, vector<Rect> rects, Mat &tpl, vector<Rect> &defects);
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
	vector<Rect> rects;
	findContours(binary.clone(), contours, hierarchy, RETR_LIST, CHAIN_APPROX_SIMPLE);
	int height = src.rows;
	for (size_t t = 0; t < contours.size(); t++) {
		Rect rect = boundingRect(contours[t]);
		double area = contourArea(contours[t]);
		if (rect.height >(height / 2)) {
			continue;
		}
		if (area < 150)
			continue;
		rects.push_back(rect);
	}
	sort_box(rects);
	Mat tpl = get_template(binary, rects);
	for (size_t t = 0; t < contours.size(); t++) {
		Rect rect = boundingRect(contours[t]);
		double area = contourArea(contours[t]);
		if (rect.height >(height / 2)) {
			continue;
		}
		if (area < 150)
			continue;
		drawContours(binary, contours, t, Scalar(0), 2, 8);
	}
	vector<Rect> defects;
	for (int i = 0; i < rects.size(); i++) {
		putText(src, format("num: %d", (i+1)), Point(rects[i].x-40, rects[i].y+15), FONT_HERSHEY_PLAIN, 1.0, Scalar(255, 0, 0), 1);
	}
	detect_defects(binary, rects, tpl, defects);
	for (int i = 0; i < defects.size(); i++) {
		rectangle(src, defects[i], Scalar(0, 0, 255), 1, 8, 0);
		putText(src, "bad", Point(defects[i].x, defects[i].y), FONT_HERSHEY_PLAIN, 1.0, Scalar(0, 255, 0), 2);
	}
	// ��ʾ
	imshow("result", src);
	waitKey(0);
	return 0;
}


void sort_box(vector<Rect> &boxes) {
	int size = boxes.size();
	for (int i = 0; i < size - 1; i++) {
		for (int j = i; j < size; j++) {
			int x = boxes[j].x;
			int y = boxes[j].y;
			int w = boxes[j].width;
			int h = boxes[j].height;
			if (y < boxes[i].y) {
				Rect temp = boxes[i];
				boxes[i] = boxes[j];
				boxes[j] = temp;
			}
		}
	}
}
Mat get_template(Mat &binary, vector<Rect> rects) {
	return binary(rects[0]);
}
void detect_defects(Mat &binary, vector<Rect> rects, Mat &tpl, vector<Rect> &defects) {
	int height = tpl.rows;
	int width = tpl.cols;
	int index = 1;
	int size = rects.size();
	for (int i = 0; i < size; i++) {
		Mat roi = binary(rects[i]);
		resize(roi, roi, tpl.size());
		Mat mask;
		subtract(tpl, roi, mask);
		Mat se = getStructuringElement(MORPH_RECT, Size(5, 5), Point(-1, -1));
		morphologyEx(mask, mask, MORPH_OPEN, se);
		threshold(mask, mask, 0, 255, THRESH_BINARY);
		int count = 0;
		for (int row = 0; row < height; row++) {
			for (int col = 0; col < width; col++) {
				int pv = mask.at<uchar>(row, col);
				if (pv == 255) {
					count++;
				}
			}
		}
		if (count > 0) {
			defects.push_back(rects[i]);
		}
	}
}