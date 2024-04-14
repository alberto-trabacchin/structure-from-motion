
int main(int argc, char** argv) {
    std::string vid_path = argv[1];
    cv::VideoCapture cap(vid_path);
    cv::FlannBasedMatcher matcher;
    boost::circular_buffer<cv::Mat> frame_buffer(2);
    boost::circular_buffer<std::vector<cv::KeyPoint>> keypoints_buffer(2);
    boost::circular_buffer<std::vector<cv::

    if (!cap.isOpened()) {
        std::cerr << "Error opening camera." << std::endl;
        return -1;
    }
    while (true) {
        cv::Mat frame;
        cap >> frame;
        frame_buffer.push_back(frame);
        keypoints_buffer.push_back(get_keypoints(frame));

        cv::imshow("Camera", frame);
        if (cv::waitKey(1) == 27)
            break;
    }
    cap.release();
    cv::destroyAllWindows();
    return 0;
}