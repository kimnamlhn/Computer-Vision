#include "opencv2\core.hpp"
#include "opencv2\highgui\highgui.hpp"
#include <iostream>
using namespace std;
using namespace cv;


int detectBySobel(Mat src,Mat dst);
int detectByPrewitt(Mat src, Mat dst);
int detectByLaplace(Mat src, Mat dst);
int detectByCany(Mat sourceImage, Mat destinationImage);