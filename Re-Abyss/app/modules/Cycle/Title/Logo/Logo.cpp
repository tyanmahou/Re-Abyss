#include "Logo.hpp"
#include <abyss/models/Cycle/Title/Logo/LogoModel.hpp>
#include <abyss/views/Cycle/Title/Logo/LogoVM.hpp>

#include <Siv3D.hpp>

namespace abyss::Cycle::Title::Logo
{
    Logo::Logo() :
        m_model(std::make_unique<LogoModel>()),
        m_view(std::make_unique<LogoVM>())
    {}

    Logo::~Logo()
    {}

    bool Logo::isEnd() const
    {
        return m_model->isEnd();
    }

    void Logo::update()
    {
        m_model->update();
    }
    void Logo::draw() const
    {
        auto [view1, view2] = m_model->getViewParams();

        if (view1) {
            m_view
                ->setPos(view1->pos)
                .setAlpha(view1->alpha)
                .draw();
        }
        if (view2) {
            m_view
                ->setPos(view2->pos)
                .setAlpha(view2->alpha)
                .draw();
        }
    }
}

