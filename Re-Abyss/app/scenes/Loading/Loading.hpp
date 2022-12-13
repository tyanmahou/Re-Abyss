#pragma once
#include <memory>
#include <abyss/utils/Coro/Generator/Generator.hpp>
namespace abyss
{
    namespace UI
    {
        class LoadingView;
    }

    class ILoadingFiber
    {
    public:
        virtual ~ILoadingFiber() = default;
        virtual double progress() const = 0;
        virtual bool isDone() const = 0;
    };
    class Loading
    {
    public:
        Loading();
        ~Loading();

        void start(Coro::Generator<double> task);
        bool isDone() const;

        void draw() const;
    private:
        std::unique_ptr<ILoadingFiber> m_task;
        std::unique_ptr<UI::LoadingView> m_view;
    };
}