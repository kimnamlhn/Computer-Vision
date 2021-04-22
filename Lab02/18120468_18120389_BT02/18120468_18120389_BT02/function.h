#include "opencv2\core.hpp"
#include "opencv2\highgui\highgui.hpp"
#include <iostream>
using namespace std;
using namespace cv;

// hàm tính chập
Mat DoConvolution(Mat& image, float kernel[], int size);
//phát hiện biên cạnh bằng sobel
int detectBySobel(Mat src, Mat dst);
//phát hiện biên cạnh bằng prewitt
int detectByPrewitt(Mat src, Mat dst);
//phát hiện biên cạnh bằng laplace
int detectByLaplace(Mat sourceImage, Mat destinationImage);
//phát hiện biên cạnh bằng cany
int detectByCany(Mat sourceImage, Mat destinationImage);