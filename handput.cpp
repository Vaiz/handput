#include "pch.h"
#include "camera.h"
#include "window.h"
#include "filter.h"



int main() {
    try {
        Window window("Test");
        auto cam = Camera::open_default();
        Frame frame;
        FilterRoulette backgroundFilters;

        bool bFinish = false;
        while (!bFinish) {
            cam.read_frame(frame);
            cv::flip(frame, frame, 1);

            backgroundFilters.apply(frame);

            const i32 key = window.update_and_wait(frame, 10);

            switch (key) {
            case 'q':
                bFinish = true;
                break;
            case 'f':
                backgroundFilters.next();
                break;
            }
        }
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return -1;
    }
}
