#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
using namespace cv;
int main()
{
    Mat img = imread("tmp.jpg", IMREAD_COLOR);
    if (img.empty())
    {
        std::cout << "Could not read the image: " << std::endl;
        return 1;
    }
    imshow("Display window", img);
    waitKey(0); // Wait for a keystroke in the window

    return 0;
}