#include "function.h"

int DoConvolution(Mat& sourceImage, Mat& destinationImage, vector<float> kernel, int size)
{
	int rows = sourceImage.rows;
	int cols = sourceImage.cols;

	Mat sourceClone = sourceImage.clone(); // tao ban sao
	vector <int> dx;
	vector <int> dy;
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++) {
			dx.push_back(i - (size / 2));
			dy.push_back(j - (size / 2));
		}

	destinationImage = Mat(rows - size + 1, cols - size + 1, CV_32FC1, Scalar(0.0));


	for (int i = 0; i < destinationImage.rows; i++) {
		float* dataRow = destinationImage.ptr<float>(i);
		for (int j = 0; j < destinationImage.cols; j++) {
			int i_source = i + (size / 2), j_source = j + (size / 2);
			float convolution = 0.0;
			for (int k = 0; k < size * size; k++) {
				float dataImage = 1.0 * sourceClone.ptr<uchar>(i_source - dx[k])[j_source - dy[k]];
				float dataKernel = 1.0 * kernel[(dx[k] + (size / 2)) * size + dy[k] + (size / 2)];
				convolution += dataImage * dataKernel;
			}
			dataRow[j] = convolution;
		}
	}

	return 0;
}

int detectBySobel(Mat& sourceImage, Mat& destinationImage, int size)
{
	int rows = sourceImage.rows;
	int cols = sourceImage.cols;
	int channels = sourceImage.channels();

	//if (channels != 1) 
	//	return 1;
	float eps = 1e-6;

	float threshold = 25;

	Mat sourceClone = sourceImage.clone(); // tao ban sao
	destinationImage = Mat(rows - size + 1, cols - size + 1, CV_32FC1, Scalar(0));

	vector <float> Wx = { -1 , 0, 1, -2, 0, 2, -1, 0, 1 };
	vector <float> Wy = { -1, -2, -1, 0, 0, 0, 1, 2, 1 };

	//for (int i = 0; i < Wx.size(); i++) {
	//	Wx[i] *= 1.0 / 4;
	//	Wy[i] *= 1.0 / 4;
	//}
	Mat Gx;
	Mat Gy;

	DoConvolution(sourceClone, Gx, Wx, 3);
	DoConvolution(sourceClone, Gy, Wy, 3);


	for (int i = 0; i < destinationImage.rows; i++)
		for (int j = 0; j < destinationImage.cols; j++) {
			float fx = Gx.ptr<float>(i)[j];
			float fy = Gy.ptr<float>(i)[j];
			float e = sqrt(fx * fx + fy * fy);
			if (e - threshold >= eps) {
				destinationImage.ptr<float>(i)[j] = 1;
			}
		}
	return 0;
}

int detectByPrewitt(Mat sourceImage, Mat destinationImage, int size)
{
	int rows = sourceImage.rows;
	int cols = sourceImage.cols;
	int channels = sourceImage.channels();

	//if (channels != 1)
	//	return 1;
	float eps = 1e-6;

	float threshold = 50;
	vector <float> Wx = { 1.0, 0, -1.0, 1.0, 0, -1.0, 1.0, 0, -1.0 };
	vector <float> Wy = { -1.0, -1.0, -1.0, 0, 0, 0, 1.0, 1.0, 1.0 };

	Mat fx;
	Mat fy;


	for (int i = 0; i < Wx.size(); i++) {
		Wx[i] *= 1.0 / 3;
		Wy[i] *= 1.0 / 3;
	}
	
	DoConvolution(sourceImage, fx, Wx, 3);
	DoConvolution(sourceImage, fy, Wy, 3);


	destinationImage = Mat(rows - size + 1, cols - size + 1, CV_32FC1, Scalar(0));
	for (int i = 0; i < destinationImage.rows; i++) {
		float* DestRow = destinationImage.ptr<float>(i);
		float* fxRow = fx.ptr<float>(i);
		float* fyRow = fy.ptr<float>(i);
		for (int j = 0; j < destinationImage.cols; j++) {
			float e = sqrt(fxRow[j] * fxRow[j] + fyRow[j] * fyRow[j]);
			if (e - threshold >= eps) {
				DestRow[j] = 1;
			}
		}
	}
	fx.release();
	fy.release();

	return 0;
}


int detectByLaplace(Mat sourceImage, Mat destinationImage)
{
	return 0;
}

