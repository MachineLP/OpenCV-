import cv2 as cv
import numpy as np

src = cv.imread("./test.png")
cv.namedWindow("input", cv.WINDOW_AUTOSIZE)
cv.imshow("input", src)

# 高斯模糊去噪声
gray = cv.cvtColor(src, cv.COLOR_BGR2GRAY)
dst = cv.GaussianBlur(gray, (9, 9), 2, 2)
binary = cv.adaptiveThreshold(dst, 255, cv.ADAPTIVE_THRESH_GAUSSIAN_C,
                              cv.THRESH_BINARY_INV, 45, 15)

# 开操作
se = cv.getStructuringElement(cv.MORPH_RECT, (5, 5), (-1, -1))
binary = cv.morphologyEx(binary, cv.MORPH_OPEN, se)

cv.imshow("binary", binary)

cv.waitKey(0)
cv.destroyAllWindows()
