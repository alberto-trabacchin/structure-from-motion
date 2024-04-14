#include <string>
#include <iostream>

#include "camera.hpp"


int main(int argc, char** argv) {
    std::string vid_path = argv[1];
    Camera cam(vid_path);
    cv::Mat frame;
    while (true) {
        frame = cam.read();
        cv::imshow("Frame", frame);
        if (cv::waitKey(1) == 27)
            break;
    }
    return 0;
}