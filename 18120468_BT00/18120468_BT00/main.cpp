#include "function.h"


int main(int argc, char** argv)
{
	if (argc != 2)
	{
		cout << "Chuong trinh mo va hien thi anh" << endl;
		return -1;
	}
	Mat image; // (1)
	image = imread(argv[1], IMREAD_COLOR); // (2)
	if (!image.data)
	{
		cout << "Khong the mo anh" << std::endl;
		return -1;
	}
	namedWindow("Display window", WINDOW_AUTOSIZE); // (3)
	imshow("Display window", image); // (4)
	waitKey(0);
	return 0;
}
