#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <string>
#include <vector>
#include <opencv4/opencv2/opencv.hpp>
#include <boost/circular_buffer.hpp>


class Camera{

    private:
        cv::VideoCapture cap;
        std::string vid_src;
        boost::circular_buffer<cv::Mat> frame_buffer;
        boost::circular_buffer<std::vector<cv::KeyPoint>> keypoints_buffer;
        boost::circular_buffer<cv::Mat> descriptors_buffer;
        cv::Ptr<cv::ORB> detector;
        cv::Ptr<cv::BFMatcher> matcher;
        cv::Mat mask;
        std::vector<cv::DMatch> matches;

    public:
        Camera(const std::string vid_src);
        cv::Mat read(void);
        void compute_keypoints(void);
        void match_keypoints(void);
};

#endif