#pragma once


class Window {
public:
    Window(string name)
        : name(std::move(name)) {
        cv::namedWindow(name);
    }
    i32 update_and_wait(const Frame& f, i32 timeout) {
        cv::imshow(name, f);
        return cv::waitKey(timeout);
    }

private:
    string name;
};