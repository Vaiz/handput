#include "pch.h"
#include "camera.h"
#include "window.h"

int main() {
    try {
        Window window("Test");
        auto cam = Camera::open_default();
        Frame frame;

        while (true) {
            cam.read_frame(frame);
            cv::flip(frame, frame, 1);
            const i32 key = window.update_and_wait(frame, 10);
            if (key > 0 && key != 255) {
                break;
            }
        }
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return -1;
    }
}
