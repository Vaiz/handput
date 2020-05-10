#pragma once

struct IFilter {
    virtual void apply(Frame& frame) = 0;
};


class EmptyFilter final : public IFilter {
    void apply(Frame& frame) override {}
};


class BackgroundSubtractorMOG2 final : public IFilter {
    void apply(Frame& frame) override {
        pFilter->apply(frame, frame);
    }

private:
    cv::Ptr<cv::BackgroundSubtractorMOG2> pFilter = cv::createBackgroundSubtractorMOG2(500, 16, false);
};


class BackgroundSubtractorKNN final : public IFilter {
    void apply(Frame& frame) override {
        pFilter->apply(frame, frame);
    }

private:
    cv::Ptr<cv::BackgroundSubtractorKNN> pFilter = cv::createBackgroundSubtractorKNN(500, 16, false);
};


class FilterRoulette final : public IFilter {
    using FilterVec = std::vector<std::unique_ptr<IFilter>>;

public:
    FilterRoulette() {
        filters.push_back(std::make_unique<EmptyFilter>());
        filters.push_back(std::make_unique<BackgroundSubtractorMOG2>());
        filters.push_back(std::make_unique<BackgroundSubtractorKNN>());
        curIter = filters.begin();
    }
    void apply(Frame& frame) override {
        (**curIter).apply(frame);
    }
    void next() {
        ++curIter;
        if (curIter == filters.end())
            curIter = filters.begin();
    }

private:
    FilterVec filters;
    FilterVec::iterator curIter;
};
