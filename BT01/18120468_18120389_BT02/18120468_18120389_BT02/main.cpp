#include "function.h"

int main(int argc, char* argv[])
{

	char* command, * inputPath;
	int isSuccess;
	try
	{
		inputPath = argv[1];
		command = argv[2];

		// đọc ảnh
		Mat srcImage = imread(inputPath, CV_8UC1);
		Mat desImage(srcImage.rows, srcImage.cols, CV_8UC1);

		if (strcmp(command, "--sobel") == 0)
		{
			isSuccess = detectBySobel(srcImage, desImage);
		}
		else if (strcmp(command, "--prewitt") == 0)
		{
			isSuccess = detectByPrewitt(srcImage, desImage);
		}
		else if (strcmp(command, "--laplace") == 0)
		{
			isSuccess = detectByLaplace(srcImage, desImage);
		}
		else if (strcmp(command, "--cany") == 0)
		{
			isSuccess = detectByCany(srcImage, desImage);

		}

		//in kết quả ra
		if (strcmp(command, "--sobel") == 0 || strcmp(command, "--prewitt") == 0 || strcmp(command, "--laplace") == 0 || strcmp(command, "--cany") == 0)
		{
			if (isSuccess == 0)
			{
				imshow("Source Image", srcImage);
				imshow("Destination Image", desImage);
				waitKey(0);
			}
			else
			{
				throw "Error";
			}
		}
	}
	catch (const char* msg)
	{
		cout << msg << endl;
		system("pause");
	}


	system("pause");
	return 0;
}


