#include "Main.hpp"
#include <abyss/commons/InputManager/InputManager.hpp>
#include <abyss/commons/ResourceManager/ResourceManager.hpp>
#include <abyss/controllers/Cycle/Title/Logo/Logo.hpp>
#include <abyss/controllers/Cycle/Title/BackGround/BackGround.hpp>

#include <Siv3D.hpp>

namespace abyss::Cycle::Title
{
    Main::Main(IMainObserver* observer) :
        m_observer(observer),
        m_logo(std::make_unique<Logo::Logo>()),
        m_bg(std::make_unique<BackGround::BackGround>()),
        m_bgm(ResourceManager::Main()->loadAudio(U"bgm/cycle/title/title.aas"))
    {
        m_bgm.play();
    }

    Main::~Main()
    {}

    void Main::update()
    {
        m_logo->update();
        if (!m_logo->isEnd()) {
            return;
        }
        m_bg->update();
    }

    void Main::draw() const
    {
        if (m_logo->isEnd()) {
            m_bg->draw();

            {
                static double angle = 0;
                angle += Scene::DeltaTime() * 0.5f;
                s3d::ScopedRenderStates2D blend(s3d::BlendState::Additive);

                Circle(480, 130, 100).drawArc(angle, Math::ToRadians(70.0),                          7, 7, Color(100,170,255, 50));
                Circle(480, 130, 100).drawArc(angle + Math::ToRadians(90.0), Math::ToRadians(70.0),  7, 7, Color(100, 170, 255, 50));
                Circle(480, 130, 100).drawArc(angle + Math::ToRadians(180.0), Math::ToRadians(70.0), 7, 7, Color(100, 170, 255, 50));
                Circle(480, 130, 100).drawArc(angle + Math::ToRadians(270.0), Math::ToRadians(70.0), 7, 7, Color(100, 170, 255, 50));

                Circle(480, 130, 150).drawArc(-angle*0.7, Math::ToRadians(70.0),                          7, 7, Color(100, 170, 255, 50));
                Circle(480, 130, 150).drawArc(-angle*0.7 + Math::ToRadians(90.0), Math::ToRadians(70.0),  7, 7, Color(100, 170, 255, 50));
                Circle(480, 130, 150).drawArc(-angle*0.7 + Math::ToRadians(180.0), Math::ToRadians(70.0), 7, 7, Color(100, 170, 255, 50));
                Circle(480, 130, 150).drawArc(-angle*0.7 + Math::ToRadians(270.0), Math::ToRadians(70.0), 7, 7, Color(100, 170, 255, 50));

                //Circle(480, 130, 250).drawArc(angle, Math::ToRadians(70.0),                          7, 7, Color(100, 170, 255, 50));
                //Circle(480, 130, 250).drawArc(angle + Math::ToRadians(90.0), Math::ToRadians(70.0),  7, 7, Color(100, 170, 255, 50));
                //Circle(480, 130, 250).drawArc(angle + Math::ToRadians(180.0), Math::ToRadians(70.0), 7, 7, Color(100, 170, 255, 50));
                //Circle(480, 130, 250).drawArc(angle + Math::ToRadians(270.0), Math::ToRadians(70.0), 7, 7, Color(100, 170, 255, 50));

            }
        }
        m_logo->draw();

    }
}
