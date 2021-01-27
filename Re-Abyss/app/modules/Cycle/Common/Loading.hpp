#pragma once
#include <memory>

namespace abyss::Cycle
{
    class LoadingView;

    class ILoadingTask
    {
    public:
        virtual ~ILoadingTask() = default;
        virtual double progress() const = 0;
        virtual bool isDone() const = 0;
    };
    class Loading
    {
    public:
        Loading();
        ~Loading();

        void start(std::function<void(double& progress)> func);
        bool isDone() const;

        void draw() const;
    private:
        std::unique_ptr<ILoadingTask> m_task;
        std::unique_ptr<LoadingView> m_view;
    };
}