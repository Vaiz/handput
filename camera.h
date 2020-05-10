#pragma once

class Camera {
public:
    Camera(cv::VideoCapture cam)
        : cam(std::move(cam)) {
        if (!cam.isOpened())
            throw std::logic_error("Camera is not opened");
    }

    void read_frame(Frame& f) {
        if (!cam.read(f))
            throw std::logic_error("Failed to read frame");
        if (f.empty())
            throw std::logic_error("Failed to read frame. Frame is empty");
    }
    static Camera open_default() {
        return { cv::VideoCapture(0) };
    }

private:
    cv::VideoCapture cam;
};