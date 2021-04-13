﻿#include "function.h"

int main(int argc, char** argv)
{
	Mat image;
	image = imread("girl_gray.png", CV_8UC1);
	if (!image.data)
	{
		cout << "Khong the mo anh" << std::endl;
		return -1;
	}
	Mat dst(image.rows, image.cols, CV_8UC1);
	detectByLaplace(image, dst);



	return 0;
}

//int main(int argc, char* argv[])
//{
//#pragma region ONLY_FOR_DEBUG
//	argc = 3;
//	char* temp[4];
//	temp[0] = _strdup("18120468_18120389_BT02.exe");
//	temp[1] = _strdup("--sobel");
//	temp[2] = _strdup("girl.jpg");
//
//	argv = temp;
//#pragma endregion
//
//	int size = 3;
//
//	if (argc < 3) {
//		cout << "Error arguments";
//		return 0;
//	}
//
//	char* cmd = argv[1];
//	char* inputImg = argv[2];
//	Mat srcImg = imread(inputImg, IMREAD_COLOR);
//	//k tìm thấy ảnh
//	if (srcImg.empty()) {
//		cout << "image not found";
//		return 1;
//	}
//
//	Mat desImg;
//
//	if (strcmp(cmd, "--sobel") == 0) {
//		if (detectBySobel(srcImg, desImg, size) == 0) {
//			imshow("Source", srcImg);
//			imshow("Destination", desImg);
//		}
//		else cout << "Error";
//		waitKey(0);
//		return 0;
//	}
//	if (strcmp(cmd, "--prewitt") == 0) {
//		if (detectByPrewitt(srcImg, desImg) == 0) {
//			imshow("Source", srcImg);
//			imshow("Destination", desImg);
//		}
//		else cout << "Error";
//		waitKey(0);
//		return 0;
//	}
//	if (strcmp(cmd, "--laplace") == 0) {
//		if (detectByLaplace(srcImg, desImg) == 0) {
//			imshow("Source", srcImg);
//			imshow("Destination", desImg);
//		}
//		else cout << "Error";
//		waitKey(0);
//		return 0;
//	}
//
//#pragma region ONLY_FOR_DEBUG
//	free(temp[0]);
//	free(temp[1]);
//	free(temp[2]);
//	free(temp[3]);
//#pragma endregion
//
//	waitKey(0);
//	return 0;
//}

