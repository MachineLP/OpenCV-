import cv2 as cv

src = cv.imread("./test.png")
cv.namedWindow("input", cv.WINDOW_AUTOSIZE)
cv.imshow("input", src)
gray = cv.cvtColor(src, cv.COLOR_BGR2GRAY)
cv.imwrite('gray.png', gray)
cv.imshow("gray", gray)
cv.waitKey(0)
cv.destroyAllWindows()

