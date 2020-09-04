#include "DemoActor.hpp"

#include <abyss/commons/Constants.hpp>
#include <abyss/models/Actors/Commons/CustomDrawModel.hpp>
#include <abyss/views/Actors/Enemy/CodeZero/Body/BodyVM.hpp>
#include <abyss/views/Actors/Enemy/CodeZero/Hand/HandVM.hpp>
#include <abyss/views/Actors/Enemy/CodeZero/Head/HeadVM.hpp>
#include <abyss/views/util/MaskUtil/MaskUtil.hpp>
#include <abyss/params/Actors/Enemy/CodeZero/Param.hpp>
#include <abyss/types/Forward.hpp>

namespace abyss::Actor::CodeZero::Demo
{
    DemoActor::DemoActor(const s3d::Vec2& pos) :
        m_pos(pos + s3d::Vec2{ 0, 400 }),
        m_targetPos(pos),
        m_bodyVM(std::make_unique<Body::BodyVM>()),
        m_headVM(std::make_unique<Head::HeadVM>()),
        m_leftHandVM(std::make_unique<Hand::HandVM>(Forward::Left)),
        m_rightHandVM(std::make_unique<Hand::HandVM>(Forward::Right))
    {
        m_order = -99;

        {
            auto draw = [this] {
                const s3d::RectF maskArea(m_targetPos.x - Constants::GameScreenSize.x / 2.0f, m_targetPos.y + 140, Constants::GameScreenSize.x, 120);

                {
                    auto mask = MaskUtil::Instance().notEqual([maskArea] {
                        maskArea.draw(s3d::Palette::Black);
                    });

                    m_bodyVM->setPos(m_pos).draw();
                    double time = this->getDrawTimeSec();
                    m_headVM->setTime(time).setPos(m_pos + Param::Head::Offset).draw();
                    m_leftHandVM->setTime(time).setPos(m_pos + s3d::Vec2{ 110, 90 }).draw();
                    m_rightHandVM->setTime(time).setPos(m_pos + s3d::Vec2{ -110, 90 }).draw();
                }
            };
            this->attach<CustomDrawModel>()->setDrawer(draw);
        }

    }

    bool DemoActor::moveToTarget(double dt)
    {
        if (m_pos.y <= m_targetPos.y) {
            m_pos = m_targetPos;
            return false;
        }
        m_pos.y += -120 * dt;
        return true;
    }

}
