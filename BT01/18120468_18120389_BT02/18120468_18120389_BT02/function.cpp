#include "function.h"


// image: ảnh vào
// kernel: là ma trận karrnel tính chập 
// size: là kích thước bộ lọc
//Mat DoConvolution(Mat& image, float kernel[], int size)
//{
//	// Lam cho anh trang den
//	int half_size = size / 2; //Lay nua kich thuoc cua size
//
//	// Lay dong va cot
//	int row = image.rows;
//	int col = image.cols;
//
//	// Tao anh output
//	Mat output(row, col, CV_8UC1);
//
//	// Lay step cua anh output va anh image
//	int image_Step = image.step[0];
//
//	// Tao ma tran offset
//	vector<int> offset;
//	for (int i = -half_size; i <= half_size; i++)
//	{
//		for (int j = -half_size; j <= half_size; j++)
//		{
//			offset.push_back(image_Step * i + j);
//		}
//	}
//
//
//
//	// Lay dia chi dong cua anh output va anh image
//	uchar* pOutput = output.data;
//	uchar* pImage = image.data;
//
//	// Moi vong lap tang dia chi dong len output_Step va image_Step
//	for (int i = 0; i < row; i++)
//	{
//		for (int j = 0; j < col; j++, pImage++, pOutput++)
//		{
//			if (i < half_size || i >= row - half_size || j < half_size || j >= col - half_size)
//			{
//				pOutput[0] = 0;
//				continue;
//			}
//			// Khoi tao bien tinh tong 
//			float sum = 0;
//
//			// Tinh dao ham
//			for (int x = -half_size; x <= half_size; x++)
//			{
//				for (int y = -half_size; y <= half_size; y++)
//				{
//					int index = (x + half_size) * size + (y + half_size); // Vi tri trong mang kernel
//					sum += pImage[offset[index]] * kernel[index];
//				}
//			}
//
//			// Neu tong am thi ta gan bang 0
//			if (sum < 0)
//			{
//				sum = 0;
//			}
//			pOutput[0] = (int)sum;
//		}
//
//	}
//	return output;
//}


Mat DoConvolution(Mat& image, float kernel[], int size) 
{
	////kiểm tra ảnh nguồn
	//if (image.data == NULL)
	//	return image;
	////hàng, cột
	//int width = image.cols, height = image.rows;
	////số kênh màu 
	//int nChannels = image.channels();
	////tạo ảnh đích và bản sao source
	//Mat desImage(height, width, CV_8UC1);
	//Mat srcImage(height, width, CV_8UC1);

	////tạo ma trận offset
	//vector <int> dx;
	//vector <int> dy;
	//for (int i = 0; i < size; i++)
	//	for (int j = 0; j < size; j++) {
	//		dx.push_back(i - (size / 2));
	//		dy.push_back(j - (size / 2));
	//	}



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
int detectByLaplace(Mat src, Mat dst)
{
	// Tao kernel
	vector<float> kernel;
	int size = 3 / 2;

	kernel = { -1,-1,-1,-1,8,-1,-1,-1,-1 };
	// Lay step cua anh goc
	int step = src.step[0];

	// Tao offset
	vector<int> offset;
	for (int i = -size; i <= size; i++)
	{
		for (int j = -size; j <= size; j++)
		{
			offset.push_back(i * step + j);
		}
	}

	// Convolution
	int row = src.rows;
	int col = src.cols;

	uchar* pSrc = src.data;
	uchar* pDst = dst.data;

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++, pSrc++, pDst++)
		{
			if (i < size || j < size || i >= row - size || j >= col - size)
			{
				pDst[0] = 0;
			}
			else
			{
				float sum = 0;
				for (int x = -size; x <= size; x++)
				{
					for (int y = -size; y <= size; y++)
					{
						int index = (x + size) * 3 + (y + size);
						sum += pSrc[offset[index]] * kernel[index];
					}
				}
				if (sum > 0)
					pDst[0] = 255;
				else
					pDst[0] = 0;
			}
		}
	}
	imshow("Laplace", dst);
	waitKey(0);
	return 1;
}
