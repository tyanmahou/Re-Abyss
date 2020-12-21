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
    namespace Cursor
    {
        class Cursor;
    }

    class IMainObserver
    {
    public:
        virtual ~IMainObserver() = default;

        virtual void onGameStart() = 0;
        virtual void onExit() = 0;
    };
    class Main
    {
        IMainObserver* m_observer;
        std::unique_ptr<Logo::Logo> m_logo;
        std::unique_ptr<BackGround::BackGround> m_bg;
        std::unique_ptr<Cursor::Cursor> m_cursor;

        s3d::Audio m_bgm;
    public:
        Main(IMainObserver* observer);
        ~Main();

        void update();

        void draw()const;

        void finally();
    };
}