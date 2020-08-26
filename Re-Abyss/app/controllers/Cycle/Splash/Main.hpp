#pragma once

namespace abyss::Cycle::Splash
{
    namespace Logo
    {
        class Logo;
    }

    class IMainObserver
    {
    public:
        virtual ~IMainObserver() = default;

        virtual void chageOpDemoScene() = 0;
    };
    class Main
    {
        IMainObserver* m_observer;

        std::unique_ptr<Logo::Logo> m_logo;
    public:
        Main(IMainObserver* observer);
        ~Main();

        void update();

        void draw()const;
    };
}