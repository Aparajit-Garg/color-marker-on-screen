#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>


int main() {
    std::string image_path = "../blue_marker.jpeg";
    cv::Mat image, imgHSV;

    image = cv::imread(image_path);

    int h_min = 0, v_min = 0, s_min = 0;
    int h_max = 179, v_max = 255, s_max = 255;
    
    // converting BGR image to HSV format.
    cv::cvtColor(image, imgHSV, cv::COLOR_BGR2HSV);
    
    // creating trackbar. Passing the values as reference to update them in memory with trackbar
    cv::Mat mask;
    cv::namedWindow("Trackbar", (640, 200));
    cv::createTrackbar("Hue min", "Trackbar", &h_min, 179);
    cv::createTrackbar("Saturation min", "Trackbar", &s_min, 255);
    cv::createTrackbar("Value min", "Trackbar", &v_min, 255);
    cv::createTrackbar("Hue max", "Trackbar", &h_max, 179);
    cv::createTrackbar("Saturation max", "Trackbar", &s_max, 255);
    cv::createTrackbar("Value max", "Trackbar", &v_max, 255);

    while (true)
    {
        // updating the mask with the change in trackbar values
        cv::Scalar lower(h_min, s_min, v_min);
        cv::Scalar upper(h_max, s_max, v_max);
        cv::inRange(imgHSV, lower, upper, mask);

        cv::imshow("imgHSV", imgHSV);
        cv::imshow("mask", mask);
        
        int c = cv::waitKey(1);

        // quit the program if q is pressed
        if (c == 113)
            break;
    }

    // print out the final values of trackbar before the program ended.
    std::cout << "H: " << h_min << " " << h_max << std::endl;
    std::cout << "S: " << s_min << " " << s_max << std::endl;
    std::cout << "V: " << v_min << " " << v_max << std::endl;
    
    return 0;

}