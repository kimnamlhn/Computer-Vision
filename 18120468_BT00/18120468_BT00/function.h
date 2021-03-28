#include "opencv2\core.hpp"
#include "opencv2\highgui\highgui.hpp"
#include <iostream>
using namespace std;
using namespace cv;

int changeContract(Mat& srcImage, Mat& desImage, float contrastValue);
int changeBrighness(Mat& srcImage, Mat& desImage, short brighnessValue);
int RGB2Gray(Mat& srcImage, Mat& desImage);
int Gray2RGB(Mat& srcImage, Mat& desImage);

