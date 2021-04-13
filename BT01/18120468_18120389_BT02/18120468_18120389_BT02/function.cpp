#include "function.h"

Mat DoConvolution(Mat& image, float kernel[], int size)
{
	// Lam cho anh trang den
	int half_size = size / 2; //Lay nua kich thuoc cua size

	// Lay dong va cot
	int row = image.rows;
	int col = image.cols;

	// Tao anh output
	Mat output(row, col, CV_8UC1);

	// Lay step cua anh output va anh image
	int image_Step = image.step[0];

	// Tao ma tran offset
	vector<int> offset;
	for (int i = -half_size; i <= half_size; i++)
	{
		for (int j = -half_size; j <= half_size; j++)
		{
			offset.push_back(image_Step * i + j);
		}
	}



	// Lay dia chi dong cua anh output va anh image
	uchar* pOutput = output.data;
	uchar* pImage = image.data;

	// Moi vong lap tang dia chi dong len output_Step va image_Step
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++, pImage++, pOutput++)
		{
			if (i < half_size || i >= row - half_size || j < half_size || j >= col - half_size)
			{
				pOutput[0] = 0;
				continue;
			}
			// Khoi tao bien tinh tong 
			float sum = 0;

			// Tinh dao ham
			for (int x = -half_size; x <= half_size; x++)
			{
				for (int y = -half_size; y <= half_size; y++)
				{
					int index = (x + half_size) * size + (y + half_size); // Vi tri trong mang kernel
					sum += pImage[offset[index]] * kernel[index];
				}
			}

			// Neu tong am thi ta gan bang 0
			if (sum < 0)
			{
				sum = 0;
			}
			pOutput[0] = (int)sum;
		}

	}
	return output;
}

int detectBySobel(Mat src, Mat dst)
{
	// Ma tran theo phuong x va phuong y
	float kernel_x[] = { -1, 0, 1, -2, 0, 2, -1, 0, 1 };
	float kernel_y[] = { -1, -2, -1, 0, 0, 0, 1, 2, 1 };

	// Dao ham theo 2 huong
	Mat image_x = DoConvolution(src, kernel_x, 3);
	Mat image_y = DoConvolution(src, kernel_y, 3);

	// Xuat anh dao ham
	imshow("Dao ham theo x", image_x);
	imshow("Dao ham theo y", image_y);

	// Tinh sqrt ( image_x^2 + image_y^2)
	// Lay dong va cot
	int row = src.rows;
	int col = src.cols;

	// Lay dia chi anh dst, image_x, image_y
	uchar* pDst = dst.data;
	uchar* pImage_x = image_x.data;
	uchar* pImage_y = image_y.data;

	// Gan vao anh dst
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++, pDst++, pImage_x++, pImage_y++)
		{
			pDst[0] = (uchar)(sqrt(pImage_x[0] * pImage_x[0] + pImage_y[0] * pImage_y[0]) / 4);
		}
	}
	imshow("Destination", dst);
	waitKey(0);
	return 1;
}
int detectByPrewitt(Mat src, Mat dst)
{
	// Ma tran theo phuong x va phuong y
	float kernel_x[] = { 1, 0, -1, 1, 0, -1, 1, 0, -1 };
	float kernel_y[] = { -1,-1,-1,0,0,0,1,1,1 };


	// Dao ham theo 2 huong
	Mat image_x = DoConvolution(src, kernel_x, 3);
	Mat image_y = DoConvolution(src, kernel_y, 3);

	// Xuat anh dao ham
	imshow("Dao ham theo x", image_x);
	imshow("Dao ham theo y", image_y);

	// Tinh sqrt ( image_x^2 + image_y^2)
	// Lay dong va cot
	int row = src.rows;
	int col = src.cols;

	// Lay dia chi anh dst, image_x, image_y
	uchar* pDst = dst.data;
	uchar* pImage_x = image_x.data;
	uchar* pImage_y = image_y.data;

	// Gan vao anh dst
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++, pDst++, pImage_x++, pImage_y++)
		{
			pDst[0] = (uchar)(sqrt(pImage_x[0] * pImage_x[0] + pImage_y[0] * pImage_y[0]) / 3);
		}
	}
	imshow("Destination", dst);
	waitKey(0);
	return 1;
}
int detectByLaplace(Mat sourceImage, Mat destinationImage)
{
	int rows = sourceImage.rows;
	int cols = sourceImage.cols;
	int channels = sourceImage.channels();

	if (channels != 1) return 1;
	float eps = 1e-6;

	vector<float> laplace = { 1, 1, 1, 1, -8, 1, 1, 1, 1 };
	Mat destinationImageCopied = Mat(rows, cols, CV_32FC1);

	// tinh chap
	//Convolution Laplace;
	//Laplace.SetKernel(laplace, 3, 3);
	// kiem tra dieu kien
	//if (Laplace.DoConvolution(sourceImage, destinationImageCopied) == 1) return 1;

	// tinh threshold
	float threshold = -1.0 * INT_MAX;
	destinationImage = Mat::zeros(rows, cols, CV_8UC1);
	for (int x = 0; x < destinationImageCopied.rows; x++) {
		for (int y = 0; y < destinationImageCopied.cols; y++) {
			float value = destinationImageCopied.at<float>(x, y);
			threshold = value > threshold ? value : threshold;
		}
	}
	threshold = threshold > 255 ? 255 : threshold;
	threshold = threshold * 25 / 100.0;

	//tinh zero crossing
	int dx[] = { -1, 1, 0, -1 };
	int dy[] = { -1, -1, 1, 0 };
	for (int x = 1; x < destinationImageCopied.rows - 1; x++) {
		for (int y = 1; y < destinationImageCopied.cols - 1; y++) {
			int count = 0;
			for (int k = 0; k < 4; k++) {
				float value1 = destinationImageCopied.at<float>(x + dx[k], y + dy[k]);
				float value2 = destinationImageCopied.at<float>(x - dx[k], y - dy[k]);
				int sign1 = value1 < 0 ? -1 : 1;
				int sign2 = value2 < 0 ? -1 : 1;
				if (sign1 != sign2 && abs(value1 - value2) - eps > threshold) {
					count++;
				}
			}
			// diem zero crossing
			if (count >= 2) destinationImage.at<uchar>(x, y) = 255;
		}
	}

	imshow("Laplace", destinationImage);
	waitKey(0);
	return 1;
}