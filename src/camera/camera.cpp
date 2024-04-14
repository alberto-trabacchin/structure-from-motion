#include <stdexcept>
#include <iostream>

#include "camera.hpp"


Camera::Camera(const std::string vid_src) {
    this->vid_src = vid_src;
    this->cap = cv::VideoCapture(vid_src);
    if (!this->cap.isOpened()) {
        throw std::runtime_error("Error opening video source.");
    }
    this->frame_buffer = boost::circular_buffer<cv::Mat>(2);
    this->keypoints_buffer = boost::circular_buffer<std::vector<cv::KeyPoint>>(2);
    this->descriptors_buffer = boost::circular_buffer<cv::Mat>(2);
    this->detector = cv::ORB::create();
    this->matcher = cv::BFMatcher::create(cv::NORM_HAMMING, true);
    std::cout << "Camera object created." << std::endl;
}

cv::Mat Camera::read(void) {
    cv::Mat frame;
    (this->cap) >> frame;
    if (frame.empty()) {
        throw std::runtime_error("Error reading frame.");
    }
    this->frame_buffer.push_back(frame);
    this->compute_keypoints();
    if (this->frame_buffer.size() == 2)
        this->match_keypoints();
    return frame;
}

void Camera::compute_keypoints(void) {
    cv::Mat img = this->frame_buffer[0];
    cv::cvtColor(img, img, cv::COLOR_BGR2GRAY);
    this->mask = cv::Mat::ones(img.size(), CV_8UC1);
    std::vector<cv::KeyPoint> keypoints;
    cv::Mat descriptors;
    detector->detectAndCompute(img, mask, keypoints, descriptors);
    this->keypoints_buffer.push_back(keypoints);
    this->descriptors_buffer.push_back(descriptors);
}

void Camera::match_keypoints(void) {
    matcher->match(
        this->descriptors_buffer[0], 
        this->descriptors_buffer[1], 
        this->matches
    );
}