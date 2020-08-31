#include "BackGround.hpp"
#include <abyss/models/Cycle/Title/BackGround/BackGroundModel.hpp>
#include <abyss/views/Cycle/Title/BackGround/BackGroundVM.hpp>
#include <abyss/views/Cycle/Title/BackGround/AtlantisVM.hpp>

#include <Siv3D.hpp>

namespace abyss::Cycle::Title::BackGround
{
    BackGround::BackGround() :
        m_model(std::make_unique<BackGroundModel>()),
        m_bgView(std::make_unique<BackGroundVM>()),
        m_atlantisView(std::make_unique<AtlantisVM>())
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
        m_bgView
            ->setPos(m_model->getPos())
            .draw();
        m_atlantisView
            ->setPos(m_model->getAtlantisPos())
            .draw();
    }
}