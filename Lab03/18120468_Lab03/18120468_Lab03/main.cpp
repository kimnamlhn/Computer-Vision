#include "function.h"



//int main()
//{
//    Mat img = imread("harris.jpg", IMREAD_GRAYSCALE);
//    if (img.empty())
//    {
//        std::cout << "Could not read the image: " << std::endl;
//        return 1;
//    }
//    imshow("src window", img);
//    detectHarris(img);
//
//
//
//    waitKey(0); 
//
//    return 0;
//}


int main(int argc, char* argv[])
{
	char* command, * inputPath;

	try
	{
		inputPath = argv[1];
		command = argv[2];

		// đọc ảnh
		Mat input = imread(inputPath, IMREAD_GRAYSCALE);
		Mat output;
		int isSuccess = 0; // 0 la dung, 1 la sai 

		//ảnh gốc
		namedWindow("Src Image", WINDOW_AUTOSIZE);
		cv::imshow("Src Image", input);

		// Command kiểm tra câu lệnh yêu cầu
		if (strcmp(command, "--harris") == 0)
		{
			isSuccess = detectHarris(input);
		}
		else if (strcmp(command, "--blob") == 0)
		{
			isSuccess = detectBlob(input, output);
		}
		else if (strcmp(command, "--dog") == 0)
		{
			isSuccess = detectDOG(input, output);
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