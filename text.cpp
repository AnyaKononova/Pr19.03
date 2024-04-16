#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main() {
    // Загрузка изображения
    Mat image = imread("C:/Users/Nuta/Documents/Open CV/Практика 2/2.png", IMREAD_GRAYSCALE);
    if (image.empty()) {
        cout << "Error" << endl;
        return -1;
    }

    Mat edges;
    Canny(image, edges, 50, 150);

    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(edges, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    Mat contourImage = Mat::zeros(image.size(), CV_8UC3);
    for (size_t i = 0; i < contours.size(); ++i) {
        drawContours(contourImage, contours, static_cast<int>(i), Scalar(255, 255, 255), 2);
    }
    imwrite("Done.png", contourImage);
    imshow("Original", image);
    imshow("Done", contourImage);
    waitKey(0);

    return 0;
}
