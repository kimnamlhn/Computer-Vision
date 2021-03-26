#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
using namespace cv;

int main()
{
	Mat image = imread("girl.jpg", CV_LOAD_IMAGE_COLOR);
	namedWindow("Show Image");
	imshow("Show Image", image);
	waitKey(0);
	return 0;
}
