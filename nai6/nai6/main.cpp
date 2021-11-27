#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace cv;

// \\wsl$

int main(int argc, char** argv) {

    bool capturing = true;
    VideoCapture cap(0);
    Mat frame;
    if (!cap.isOpened()) {
        std::cerr << "error opening frames source" << std::endl;
        return -1;
    }

    std::cout << "Video size: " << cap.get(cv::CAP_PROP_FRAME_WIDTH)
              << "x" << cap.get(cv::CAP_PROP_FRAME_HEIGHT) << std::endl;

    do {
        Mat frame;
        Mat mirror;
        if (cap.read(frame)) {
            imshow("Not-yet smart window", frame);
            flip(frame, mirror, 1);
            imshow("odbicie lustrzane", mirror);
        }
        else {
            //stream finished
            capturing = false;
        }
        //czekaj na klawisz, sprawdz czy to jest 'esc'
        //113 - q 27 - esc
        if ((waitKey(1000.0 / 60.0) & 0x0ff) == 113) {
            capturing = false;
        }
    } while (capturing);

    return 0;
}