#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <vector>


std::vector<std::vector<int>> colors {
    // h_min, h_max, s_min, s_max, v_min, v_max
    {53, 179, 99, 255, 58, 255}, // blue marker
    {68, 102, 72, 126, 156, 255}, // green marker
    {124, 143, 48, 170, 117, 255} // purple marker
};

std::vector<cv::Scalar> detectedColor {
    {255, 0, 0}, // blue
    {0, 255, 0}, // green
    {255, 0, 255} // purple
};

std::vector<std::vector<int>> newPoints;

cv::Point getContours(cv::Mat mask, cv::Mat image){
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;

    cv::findContours(mask, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    std::vector<std::vector<cv::Point>> conPoly(contours.size());
    std::vector<cv::Rect> boundRect(contours.size());
    cv::Point myPoint(0, 0);

    for (int i = 0; i < contours.size(); i++) {
        int area = cv::contourArea(contours[i]);

        if (area > 1000){
            float peri = cv::arcLength(contours[i], true);
            cv::approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);
            boundRect[i] = cv::boundingRect(conPoly[i]);
            myPoint.x = boundRect[i].x + boundRect[i].width/2;
            myPoint.y = boundRect[i].y;

            cv::drawContours(image, conPoly, i, cv::Scalar(255, 0, 255));
        }
    }
    return myPoint;
}

void findColor(cv::Mat image){
    cv::Mat imgHSV;
    cv::cvtColor(image, imgHSV, cv::COLOR_BGR2HSV);

    for (int i = 0; i < colors.size(); i++){
        cv::Mat mask;
        int h_min = colors[i][0];
        int h_max = colors[i][1];
        int s_min = colors[i][2];
        int s_max = colors[i][3];
        int v_min = colors[i][4];
        int v_max = colors[i][5];
        cv::Scalar lower(h_min, s_min, v_min);
        cv::Scalar upper(h_max, s_max, v_max);
        cv::inRange(imgHSV, lower, upper, mask);

        cv::Point myPoint = getContours(mask, image);
        if (myPoint.x != 0 && myPoint.y != 0) {
            newPoints.push_back({myPoint.x, myPoint.y, i});
        }
        // cv::imshow( std::to_string(i), mask);
    }
}

void drawOnScreen(cv::Mat image) {
    for (int i = 0; i < newPoints.size(); i++) {
        // std::cout << detectedColor[newPoints[i][2]];
        cv::circle(image, cv::Point(newPoints[i][0], newPoints[i][1]), 10, detectedColor[newPoints[i][2]], cv::FILLED);
    }
}

int main() {
    // std::string image_path = "../blue_marker.jpeg";
    cv::VideoCapture cap(0);
    cv::Mat image;

    while (true){
        cap.read(image);
        
        findColor(image);
        drawOnScreen(image);

        cv::imshow("image", image);
        int c = cv::waitKey(1);
        if (c == 113)
            break;
    }

    return 0;

}