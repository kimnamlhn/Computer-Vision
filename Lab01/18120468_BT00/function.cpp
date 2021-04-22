#include "function.h"

// hàm thay đổi độ tương phản
int changeContract(Mat& srcImage, Mat& desImage, float contrastValue)
{
	//kiểm tra ảnh nguồn
	if (srcImage.data == NULL)
		return 1;

	//hàng, cột
	int width = srcImage.cols, height = srcImage.rows;

	//clone ảnh đích từ ảnh nguồn
	desImage.create(srcImage.rows, srcImage.cols, srcImage.type());

	//số kênh màu 
	int nChannels = srcImage.channels();

	//bảng tra, dùng saturate_cast để hạn chế từ 0-255
	uchar lookup[256];
	for (int i = 0; i < 256; i++)
		lookup[i] = saturate_cast<uchar>(i * contrastValue);

	//truy xuất từng pixel điểm ảnh
	for (int y = 0; y < height; y++) 
	{
		// con trỏ chỉ dữ liệu trên từng hàng của ảnh nguồn và ảnh đích
		uchar* pSrcRow = srcImage.ptr<uchar>(y);
		uchar* pDstRow = desImage.ptr<uchar>(y);
		for (int j = 0; j < width; j++, pSrcRow += nChannels, pDstRow += nChannels) 
		{
			//k là số kênh màu chạy (ảnh xám 1 hoặc ảnh màu 3)
			for (int k = 0; k < nChannels; k++)
				pDstRow[k] = lookup[(int)pSrcRow[k]];
		}
	}
	

	return 0;
}

//hàm thay đổi độ sáng
int changeBrighness(Mat& srcImage, Mat& desImage, short brighnessValue)
{
	//kiểm tra ảnh nguồn
	if (srcImage.data == NULL)
		return 1;

	//hàng, cột
	int width = srcImage.cols, height = srcImage.rows;

	//clone ảnh đích từ ảnh nguồn
	desImage.create(srcImage.rows, srcImage.cols, srcImage.type());

	//số kênh màu 
	int nChannels = srcImage.channels();

	//bảng tra, dùng saturate_cast để hạn chế từ 0-255
	uchar lookup[256];
	for (int i = 0; i < 256; i++)
		lookup[i] = saturate_cast<uchar>(i + brighnessValue);

	//truy xuất từng pixel điểm ảnh
	for (int y = 0; y < height; y++)
	{
		// con trỏ chỉ dữ liệu trên từng hàng của ảnh nguồn và ảnh đích
		uchar* pSrcRow = srcImage.ptr<uchar>(y);
		uchar* pDstRow = desImage.ptr<uchar>(y);
		for (int j = 0; j < width; j++, pSrcRow += nChannels, pDstRow += nChannels)
		{
			//k là số kênh màu chạy (ảnh xám 1 hoặc ảnh màu 3)
			for (int k = 0; k < nChannels; k++)
				pDstRow[k] = lookup[(int)pSrcRow[k]];
		}
	}
		return 0;
}

// hàm chuyển ảnh màu sang ảnh xám
int RGB2Gray(Mat& srcImage, Mat& desImage)
{
	//kiểm tra ảnh nguồn
	if (srcImage.data == NULL)
		return 1;

	//hàng, cột
	int width = srcImage.cols, height = srcImage.rows;

	//tạo ảnh output là ảnh xám
	desImage = cv::Mat(height, width, CV_8UC1);

	//số kênh màu của ảnh nguồn và đích
	int srcnChannels = srcImage.channels();
	int dstnChannels = desImage.channels();

	for (int y = 0; y < height; y++)
	{
		// con trỏ chỉ dữ liệu trên từng hàng của ảnh nguồn và ảnh đích
		uchar* pSrcRow = srcImage.ptr<uchar>(y);
		uchar* pDstRow = desImage.ptr<uchar>(y);

		//tính giá trị gray trên ảnh nguồn rồi gán vào ảnh đích
		for (int x = 0; x < width; x++, pSrcRow += srcnChannels, pDstRow += dstnChannels)
		{
			uchar B = pSrcRow[0];
			uchar G = pSrcRow[1];
			uchar R = pSrcRow[2];
			float gray_value = (float)(R + G + B) / 3;
			pDstRow[0] = (uchar)gray_value;
		}
	}

	return 0;
}

//hàm chuyển ảnh xám sang ảnh màu RGB
int Gray2RGB(Mat& srcImage, Mat& desImage)
{
	// kiểm tra ảnh nguồn
	if (srcImage.data == NULL)
		return 1;

	// hàng, cột
	int height = srcImage.rows;
	int width = srcImage.cols;

	//tạo ảnh ouput là ảnh màu
	desImage = cv::Mat(height, width, CV_8UC3);


	// truy xuất từng pixel điểm ảnh
	// lấy giá trị gray gán cho 3 kênh màu của ảnh đích mới tạo
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			int grayValue = srcImage.at<Vec3b>(i, j)[0];
			desImage.at<Vec3b>(i, j)[0] = grayValue;
			desImage.at<Vec3b>(i, j)[1] = grayValue;
			desImage.at<Vec3b>(i, j)[2] = grayValue;

		}

	}
	return 0;
}

