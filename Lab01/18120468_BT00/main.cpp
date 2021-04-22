#include "function.h"


int main(int argc, char* argv[])
{
	char* command, * inputPath;

	try
	{
		inputPath = argv[1];
		command = argv[2];

		// đọc ảnh
		Mat input = imread(inputPath, -1);
		Mat output;
		int isSuccess = 0; // 0 la dung, 1 la sai 

		// Command kiểm tra câu lệnh yêu cầu
		if (strcmp(command, "--rgb2gray") == 0)
		{
			isSuccess = RGB2Gray(input, output);
		}
		else if (strcmp(command, "--gray2rgb") == 0)
		{
			isSuccess = Gray2RGB(input, output);
		}
		else if (strcmp(command, "--bright") == 0)
		{
			uchar brighVaule = atoi(argv[3]);
			isSuccess = changeBrighness(input, output, brighVaule);
		}
		else if (strcmp(command, "--contrast") == 0)
		{
			uchar contrastValue = atoi(argv[3]);
			isSuccess = changeContract(input, output, contrastValue);
		}


		//in kết quả ra
		if (strcmp(command, "--rgb2gray") == 0 || strcmp(command, "--gray2rgb") == 0 || strcmp(command, "--bright") == 0 || strcmp(command, "--contrast") == 0)
		{
			if (isSuccess == 0)
			{
				imshow("Source Image", input);
				imshow("Destination Image", output);
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
