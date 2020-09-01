#pragma once
#include <Siv3D/Audio.hpp>
namespace abyss::Cycle::Title
{
    namespace Logo
    {
        class Logo;
    }
    namespace BackGround
    {
        class BackGround;
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
        std::unique_ptr<BackGround::BackGround> m_bg;

        s3d::Audio m_bgm;
    public:
        Main(IMainObserver* observer);
        ~Main();

        void update();

        void draw()const;

        void finally();
    };
}