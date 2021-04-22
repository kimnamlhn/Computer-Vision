#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
using namespace std;
using namespace cv;

Mat detectHarrist(Mat img);
Mat detectBlob(Mat img);
Mat detectDOG(Mat img);
double matchBySIFT(Mat img1, Mat img2, int detector);
