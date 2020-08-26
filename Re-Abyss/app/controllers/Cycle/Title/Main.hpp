#pragma once

namespace abyss::Cycle::Title
{
    class IMainObserver
    {
    public:
        virtual ~IMainObserver() = default;
    };
    class Main
    {
        IMainObserver* m_observer;
    public:
        Main(IMainObserver* observer);
        ~Main();

        void update();

        void draw()const;
    };
}