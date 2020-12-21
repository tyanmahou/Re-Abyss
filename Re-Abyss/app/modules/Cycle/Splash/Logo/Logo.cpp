#include "Logo.hpp"
#include <abyss/models/Cycle/Splash/Logo/LogoModel.hpp>
#include <abyss/views/Cycle/Splash/Logo/LogoVM.hpp>

#include <Siv3D.hpp>

namespace abyss::Cycle::Splash::Logo
{
    Logo::Logo():
        m_model(std::make_unique<LogoModel>()),
        m_view(std::make_unique<LogoVM>())
    {}

    Logo::~Logo()
    {}

    bool Logo::isEnd() const
    {
        return m_model->isEnd();
    }

    void Logo::draw() const
    {
        m_view
            ->setPos(Scene::Center())
            .setTime(m_model->time0_1())
            .draw();
    }
}

