//#include "Main.hpp"
//#include <abyss/commons/InputManager/InputManager.hpp>
//#include <abyss/commons/Resource/Assets/Assets.hpp>
//#include <abyss/modules/Cycle/Title/Logo/Logo.hpp>
//#include <abyss/modules/Cycle/Title/BackGround/BackGround.hpp>
//#include <abyss/modules/Cycle/Title/Cursor/Cursor.hpp>
//
//#include <Siv3D.hpp>
//
//namespace abyss::Cycle::Title
//{
//    Main::Main(IMainObserver* observer) :
//        m_observer(observer),
//        m_logo(std::make_unique<Logo::Logo>()),
//        m_bg(std::make_unique<BackGround::BackGround>()),
//        m_cursor(std::make_unique<Cursor::Cursor>()),
//        m_bgm(Resource::Assets::Main()->loadAudio(U"bgm/cycle/title/title.aas"))
//    {
//        m_bgm.play(0.2s);
//
//        (*m_cursor)[Cursor::Cursor::Mode::GameStart] = [this] {
//            m_observer->onGameStart();
//        };
//        (*m_cursor)[Cursor::Cursor::Mode::Exit] = [this] {
//            m_observer->onExit();
//        };
//    }
//
//    Main::~Main()
//    {}
//
//    void Main::update()
//    {
//        m_logo->update();
//        if (!m_logo->isEnd()) {
//            return;
//        }
//        m_bg->update();
//        m_cursor->update();
//    }
//
//    void Main::draw() const
//    {
//        if (m_logo->isEnd()) {
//            m_bg->draw();
//            m_cursor->draw();
//        }
//        m_logo->draw();
//    }
//
//    void Main::finally()
//    {
//        m_bgm.stop(0.2s);
//    }
//}
