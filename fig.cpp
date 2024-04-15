#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    Mat image = imread("task1.png");

    if (image.empty()) {
        cout << "Error" << endl;
        return -1;
    }

    auto figure = [](const vector<Point>& contour) -> string {
        double epsilon = 0.04 * arcLength(contour, true);
        vector<Point> approx;
        approxPolyDP(contour, approx, epsilon, true);

        if (approx.size() == 3) {
            return "Triangle";
        }
        else if (approx.size() == 4) {
            Rect rect = boundingRect(contour);
            double aspectRatio = static_cast<double>(rect.width) / rect.height;
            if (aspectRatio >= 0.95 && aspectRatio <= 1.05) {
                return "Square";
            }
            else {
                return "Rectangle";
            }
        }
        else {
            return "Circle";
        }
        };

    Mat grayImage;
    cvtColor(image, grayImage, COLOR_BGR2GRAY);
    Mat gaussImage;
    GaussianBlur(grayImage, gaussImage, Size(0, 0), 1);
    Mat contourImage;
    Canny(gaussImage, contourImage, 0, 0);
    vector<vector<Point> > contours;
    findContours(contourImage, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    for (size_t i = 0; i < contours.size(); i++) {
        string shape = figure(contours[i]);
        Scalar color;
        if (shape == "Triangle") {
            color = Scalar(255, 0, 255);  
        }
        else if (shape == "Square" || shape == "Rectangle") {
            color = Scalar(25, 87, 36);  
        }
        else {
            color = Scalar(255, 255, 255);  
        }
        drawContours(image, contours, static_cast<int>(i), color, 2);
        Moments mu = moments(contours[i]);
        Point center(mu.m10 / mu.m00, mu.m01 / mu.m00);
        putText(image, shape, center, FONT_HERSHEY_SIMPLEX, 0.5, color, 2);
    }

    imshow("Done", image);
    imwrite("Done.jpg", image);
    waitKey(0);

    return 0;
}
