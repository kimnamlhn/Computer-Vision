#include "function.h"

//int main(int argc, char** argv)
//{
//	Mat image;
//	image = imread("girl_gray.png", CV_8UC1);
//	if (!image.data)
//	{
//		cout << "Khong the mo anh" << std::endl;
//		return -1;
//	}
//	Mat dst(image.rows, image.cols, CV_8UC1);
//	detectBySobel(image, dst);
//
//	return 0;
//}

int main(int argc, char* argv[])
{
#pragma region ONLY_FOR_DEBUG
	argc = 3;
	char* temp[4];
	temp[0] = _strdup("18120468_18120389_BT02.exe");
	temp[1] = _strdup("girl_gray.png");
	temp[2] = _strdup("--laplace");

	argv = temp;
#pragma endregion

	char* command, * inputPath;

	try
	{
		inputPath = argv[1];
		command = argv[2];

		// đọc ảnh
		Mat srcImage = imread(inputPath, CV_8UC1);
		Mat desImage(srcImage.rows, srcImage.cols, CV_8UC1);

		if (strcmp(command, "--sobel") == 0)
		{
			detectBySobel(srcImage, desImage);
		}
		else if (strcmp(command, "--prewitt") == 0)
		{
			detectByPrewitt(srcImage, desImage);
		}
		else if (strcmp(command, "--laplace") == 0)
		{
			detectByLaplace(srcImage, desImage);
		}
		else if (strcmp(command, "--cany") == 0)
		{
			detectByCany(srcImage, desImage);

		}
	}
	catch (const char* msg)
	{
		cout << msg << endl;
		system("pause");
	}

#pragma region ONLY_FOR_DEBUG
	free(temp[0]);
	free(temp[1]);
	free(temp[2]);
	free(temp[3]);
#pragma endregion

	system("pause");
	return 0;
}


