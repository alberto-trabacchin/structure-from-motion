#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <opencv4/opencv2/opencv.hpp>
#include <boost/circular_buffer.hpp>


class Camera{

    private:
        cv::VideoCapture cap;
        std::string vid_src;

    public:
        boost::circular_buffer<cv::Mat> frame_buffer;
        boost::circular_buffer<std::vector<cv::KeyPoint>> keypoints_buffer;
        boost::circular_buffer<cv::Mat> descriptors_buffer;
        cv::Ptr<cv::ORB> detector;
        cv::Mat mask;

        Camera(const std::string vid_src) {
            this->vid_src = vid_src;
            this->cap = cv::VideoCapture(vid_src);
            if (!this->cap.isOpened()) {
                throw std::runtime_error("Error opening video source.");
            }
            this->frame_buffer = boost::circular_buffer<cv::Mat>(2);
            this->keypoints_buffer = boost::circular_buffer<std::vector<cv::KeyPoint>>(2);
            this->descriptors_buffer = boost::circular_buffer<cv::Mat>(2);
            this->detector = cv::ORB::create();
        }

        std::vector<cv::KeyPoint> compute_keypoints(cv::Mat img) {
            cv::cvtColor(img, img, cv::COLOR_BGR2GRAY);
            this->mask = cv::Mat::ones(img.size(), CV_8UC1);
            std::vector<cv::KeyPoint> keypoints;
            cv::Mat descriptors;
            detector->detectAndCompute(img, mask, keypoints, descriptors);
            this->keypoints_buffer.push_back(keypoints);
            this->descriptors_buffer.push_back(descriptors);
        }
};