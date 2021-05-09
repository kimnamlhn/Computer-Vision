#include "function.h"

//srcImage: ảnh nguồn
//kernel[]: giá trị của ma trận kernel
//size: kích thước ma trận kernel
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

double matchBySIFT(Mat img1, Mat img2, int detector)
{
	return 0.0;
}

int detectHarris(Mat& src)
{
	//kiểm tra điều kiện ảnh tồn tại hay không
	if (src.empty())
		return -1;

	//kiểm tra ảnh đầu vào có phải ảnh xám hay không.
	//nếu không phải thì chuyển thành ảnh xám.
	Mat dst = src.clone();
	if (src.type() != CV_8UC1)
		RGB2Gray(dst, src);

	// lấy hàng, cột
	int width = dst.cols;
	int height = dst.rows;
	
	//tập điểm các vị trí của corner
	vector<Point> points;

	//Làm trơn ảnh bằng gaussian 
	Mat tmp;
	GaussianBlur(src, tmp, Size(0, 0), 1);

	// Kernel đạo hàm Sobel
	int Wx[3][3] = { { 1, 0, -1 },
						{ 2, 0, -2 },
						{ 1, 0, -1 } };

	int Wy[3][3] = { { -1, -2, -1 },
						{ 0, 0, 0 },
						{ 1, 2, 1 } };

	// tạo biến tính toán độ tương quan giữa các đạo hàm 
	//A = Ix^2
	//B = Ix * Iy
	//C = Iy ^ 2
	Mat Ixx(height, width, CV_32FC1);
	Mat Iyy(height, width, CV_32FC1);
	Mat Ixy(height, width, CV_32FC1);
	Mat newdst(dst.clone());
	for (int y = 0; y < height; ++y) {

		float* prow2 = Ixx.ptr<float>(y);
		float* prow3 = Iyy.ptr<float>(y);
		float* prow4 = Ixy.ptr<float>(y);

		uchar* pdata = newdst.ptr<uchar>(y);
		for (int x = 0; x < width; ++x) {
			double ix = Derivative(dst.data, Wx, width, height, y, x, width, 1, 0);
			double iy = Derivative(dst.data, Wy, width, height, y, x, width, 1, 0);

			pdata[x] = (uchar)(sqrt(ix * ix + iy * iy));
			prow2[x] = ix * ix;
			prow3[x] = iy * iy;
			prow4[x] = ix * iy;

		}
	}

	// áp bộ lọc gaussian lên các ma trận Ixx, Iyy, Ixy;
	Mat IIxx, IIyy, IIxy;
	GaussianBlur(Ixx, IIxx, Size(0, 0), 1);
	GaussianBlur(Iyy, IIyy, Size(0, 0), 1);
	GaussianBlur(Ixy, IIxy, Size(0, 0), 1);


	//Tính ma trận r là tập hợp điểm f cho mỗi điểm ảnh
	Mat rr(height, width, CV_32FC1);
	for (int y = 0; y < height; ++y) {
		float* prow1 = IIxx.ptr<float>(y);
		float* prow2 = IIyy.ptr<float>(y);
		float* prow3 = IIxy.ptr<float>(y);
		float* prow4 = rr.ptr<float>(y);
		for (int x = 0; x < width; ++x) {
			prow4[x] = (prow1[x] * prow2[x] - prow3[x] * prow3[x]) - 0.04 * (prow1[x] + prow2[x]);
		}
	}

	//corner response
	float* rrdata = (float*)rr.data;

	for (int y = 0; y < height; ++y) {
		float* prow = rr.ptr<float>(y);
		for (int x = 0; x < width; ++x) {
			float R = prow[x];

			if (R > 0) {
				bool check = true;
				for (int i = -1; i <= 1; ++i) {
					for (int j = -1; j <= 1; ++j) {
						if (y + i >= height || y + i < 0 || x + j >= width && x + j < 0)
							continue;
						if (R < rrdata[(y + i) * width + (x + j)]) {
							check = false;
							break;
						}
					}

					if (!check)
						break;
				}

				if (check)
					points.push_back(Point(x, y));

			}
		}
	}


	// Các conner trên ảnh src
	int widthstep = src.step[0];
	int nchanel = src.step[1];
	uchar* data = src.data;
	for (int i = 0; i < points.size(); ++i) {

		// đánh dấu bằng hàm circle
		circle(src, points[i], 3, Scalar(0, 0, 255), -1);

	}

	namedWindow("Des Image", WINDOW_AUTOSIZE);
	cv::imshow("Des Image", src);
	cv::waitKey(0);
	return 1;

}

double Derivative(uchar* pdata, int kernel[3][3], int width, int height, int y, int x, int widthstep, int nchanel, int ii)
{
	double res = 0.0;
	for (int i = -1; i <= 1; ++i) {
		for (int j = -1; j <= 1; ++j) {
			if (y + i >= height || y + i < 0 || x + j >= width || x + j < 0)
				continue;
			else {
				res += pdata[(y + i) * widthstep + (x + j) * nchanel + ii] * kernel[1 - i][1 - j];
			}
		}
	}

	return (double)(res * (1.0 / 4) * (1.0 / 255));
}

int detectBlob(Mat& src, Mat& dst)
{
	//kiểm tra điều kiện ảnh tồn tại hay không
	if (src.empty())
		return -1;

	//kiểm tra ảnh đầu vào có phải ảnh xám hay không.
	//nếu không phải thì chuyển thành ảnh xám.
	if (src.type() != CV_8UC1)
		RGB2Gray(dst, src);

	// lấy hàng, cột
	int width = dst.cols;
	int height = dst.rows;




	return 1;
}

int detectDOG(Mat& src, Mat& dst)
{
	//kiểm tra điều kiện ảnh tồn tại hay không
	if (src.empty())
		return -1;

	//kiểm tra ảnh đầu vào có phải ảnh xám hay không.
	//nếu không phải thì chuyển thành ảnh xám.
	if (src.type() != CV_8UC1)
		RGB2Gray(dst, src);

	// lấy hàng, cột
	int width = dst.cols;
	int height = dst.rows;
}




