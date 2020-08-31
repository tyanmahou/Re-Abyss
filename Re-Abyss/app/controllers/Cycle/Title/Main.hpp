#pragma once
#include <Siv3D/Audio.hpp>
namespace abyss::Cycle::Title
{
    namespace Logo
    {
        class Logo;
    }

    class IMainObserver
    {
    public:
        virtual ~IMainObserver() = default;
    };
    class Main
    {
        IMainObserver* m_observer;
        std::unique_ptr<Logo::Logo> m_logo;

        s3d::Audio m_bgm;
    public:
        Main(IMainObserver* observer);
        ~Main();

        void update();

        void draw()const;
    };
}