#pragma once

namespace abyss::Cycle::Splash
{
    class IMainObserver
    {
    public:
        virtual ~IMainObserver() = default;

        virtual void chageTitleScene() = 0;
    };
    class Main
    {
        IMainObserver* m_observer;
    public:
        Main(IMainObserver* observer);

        void update();

        void draw()const;
    };
}