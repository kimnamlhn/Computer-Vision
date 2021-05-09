#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
using namespace cv;


// hàm tính chập
Mat DoConvolution(Mat& image, float kernel[], int size);

//hàm tính đạo hàm
double Derivative(uchar* pdata, int kernel[3][3], int width, int height, int y, int x, int widthstep, int nchanel, int ii);

//hàm chuyển ảnh màu sang ảnh xám
int RGB2Gray(Mat& srcImage, Mat& desImage);

//hàm dò góc harris
int detectHarris(Mat& src);

//hàm dò góc blob
int detectBlob(Mat& src, Mat& dst);

//hàm dò góc dog
int detectDOG(Mat& src, Mat& dst);

// hàm đối sánh 2 ảnh sử dụng đặc trưng SIFT với thuật toán KNN
double matchBySIFT(Mat img1, Mat img2, int detector);
