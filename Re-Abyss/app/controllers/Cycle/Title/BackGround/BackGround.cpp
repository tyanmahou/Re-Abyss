#include "BackGround.hpp"
#include <abyss/models/Cycle/Title/BackGround/BackGroundModel.hpp>
#include <abyss/views/Cycle/Title/BackGround/BackGroundVM.hpp>

#include <Siv3D.hpp>

namespace abyss::Cycle::Title::BackGround
{
    BackGround::BackGround() :
        m_model(std::make_unique<BackGroundModel>()),
        m_view(std::make_unique<BackGroundVM>())
    {}

    BackGround::~BackGround()
    {}
    
    void BackGround::update()
    {
        if (!m_model->isStarted()) {
            m_model->start();
        }
    }
    bool BackGround::isEnd() const
    {
        return m_model->isEnd();
    }

    void BackGround::draw() const
    {
        m_view
            ->setPos(m_model->getPos())
            .draw();
    }
}