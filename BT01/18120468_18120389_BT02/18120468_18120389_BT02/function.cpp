#include "function.h"


Mat DoConvolution(Mat& srcImage, float kernel[], int size)
{
	// kiểm tra điều kiện ảnh đầu vào
	if (srcImage.data == NULL)
		exit;

	// Dòng và cột 
	int rows = srcImage.rows;
	int cols = srcImage.cols;

	// số kênh màu
	int nChannels = srcImage.channels();
	
	// Tạo ảnh đích là ảnh xám
	Mat desImage(rows, cols, CV_8UC1);

	// Lấy step ảnh 
	int image_Step = srcImage.step[0];

	// Tao ma tran offset
	vector<int> offset;
	for (int i = -size / 2; i <= size / 2; i++)
	{
		for (int j = -size / 2; j <= size / 2; j++)
		{
			offset.push_back(image_Step * i + j);
		}
	}

	//truy xuất từng pixel điểm ảnh
	for (int y = 0; y < rows; y++)
	{
		// con trỏ chỉ dữ liệu trên từng hàng của ảnh nguồn và ảnh đích
		uchar* pSrcRow = srcImage.ptr<uchar>(y);
		uchar* pDstRow = desImage.ptr<uchar>(y);
		for (int j = 0; j < cols; j++, pSrcRow += nChannels, pDstRow += nChannels)
		{
			// Biến tính
			float value = 0;

			// Tính đạo hàm
			for (int x = -size / 2; x <= size / 2; x++)
			{
				for (int y = -size / 2; y <= size / 2; y++)
				{
					// gán với vị trị trong mảng kernel
					int index = (x + size / 2) * size + (y + size / 2); 
					value += pSrcRow[offset[index]] * kernel[index];
				}
			}

			// Giá trị từ 0-255
			// nếu nhỏ hơn 0 thì gán bằng 0
			// nếu lớn hơn 255 thì gán 255
			if (value < 0)
			{
				value = 0;
			}
			pDstRow[0] = (int)value;
		}
		}
	



	return desImage;
}

int detectBySobel(Mat srcImage, Mat desImage)
{
	// kiểm tra điều kiện ảnh đầu vào
	if (srcImage.data == NULL)
		exit;

	// Dòng và cột 
	int rows = srcImage.rows;
	int cols = srcImage.cols;

	// số kênh màu
	int nChannels = srcImage.channels();

	// Mặt nạ sobel theo phương x và y
	float kernelX[] = { -1, 0, 1, -2, 0, 2, -1, 0, 1 };
	float kernelY[] = { -1, -2, -1, 0, 0, 0, 1, 2, 1 };

	// đạo hàm theo 2 hướng
	Mat imageX = DoConvolution(srcImage, kernelX, 3);
	Mat imageY = DoConvolution(srcImage, kernelY, 3);

	// Địa chỉ ảnh imageX, imageY đã tính chập
	uchar* pDesImage = desImage.data;
	uchar* pImageX = imageX.data;
	uchar* pImageY = imageY.data;

	// Gán vào ảnh đích
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++, pDesImage++, pImageX++, pImageY++)
		{
			pDesImage[0] = (uchar)(sqrt(pImageX[0] * pImageX[0] + pImageY[0] * pImageY[0]) / 4);
		}
	}

	imshow("Source Image", srcImage);
	imshow("Destination", desImage);
	waitKey(0);
	return 1;
}
int detectByPrewitt(Mat srcImage, Mat desImage)
{
	// kiểm tra điều kiện ảnh đầu vào
	if (srcImage.data == NULL)
		exit;

	// Dòng và cột 
	int rows = srcImage.rows;
	int cols = srcImage.cols;

	// số kênh màu
	int nChannels = srcImage.channels();

	// Mặt nạ prewitt theo phương x và y
	float kernelX[] = { 1, 0, -1, 1, 0, -1, 1, 0, -1 };
	float kernelY[] = { -1, -1, -1, 0, 0, 0, 1, 1, 1 };


	// đạo hàm theo 2 hướng
	Mat imageX = DoConvolution(srcImage, kernelX, 3);
	Mat imageY = DoConvolution(srcImage, kernelY, 3);


	// Địa chỉ ảnh imageX, imageY đã tính chập
	uchar* pDst = desImage.data;
	uchar* pImageX = imageX.data;
	uchar* pImageY = imageY.data;

	// Gán vào ảnh đích
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++, pDst++, pImageX++, pImageY++)
		{
			pDst[0] = (uchar)(sqrt(pImageX[0] * pImageX[0] + pImageY[0] * pImageY[0]) / 3);
		}
	}

	imshow("Source Image", srcImage);
	imshow("Destination", desImage);
	waitKey(0);
	return 1;
}

int detectByLaplace(Mat srcImage, Mat desImage)
{
	// kiểm tra điều kiện ảnh đầu vào
	if (srcImage.data == NULL)
		exit;

	// Dòng và cột 
	int rows = srcImage.rows;
	int cols = srcImage.cols;

	// số kênh màu
	int nChannels = srcImage.channels();

	// Tạo kernel
	vector<float> kernel;
	int size = 3 / 2;

	kernel = { -1,-1,-1,-1,8,-1,-1,-1,-1 };

	// step của ảnh
	int step = srcImage.step[0];

	// offset
	vector<int> offset;
	for (int i = -size; i <= size; i++)
	{
		for (int j = -size; j <= size; j++)
		{
			offset.push_back(i * step + j);
		}
	}

	uchar* pSrc = srcImage.data;
	uchar* pDst = desImage.data;

	// truy xuất từng pixel điểm ảnh
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++, pSrc++, pDst++)
		{
			// khai báo biến tính
			float value = 0;
			for (int x = -size; x <= size; x++)
			{
				for (int y = -size; y <= size; y++)
				{
					int index = (x + size) * 3 + (y + size);
					value += pSrc[offset[index]] * kernel[index];
				}
			}

			// Giá trị từ 0-255
			// nếu nhỏ hơn 0 thì gán bằng 0
			// nếu lớn hơn 255 thì gán 255
			if (value > 0)
				pDst[0] = 255;
			else
				pDst[0] = 0;
			
		}
	}
	imshow("Source Image", srcImage);
	imshow("Destination Image", desImage);
	waitKey(0);
	return 1;
}

int detectByCany(Mat sourceImage, Mat destinationImage)
{
	return 0;
}
