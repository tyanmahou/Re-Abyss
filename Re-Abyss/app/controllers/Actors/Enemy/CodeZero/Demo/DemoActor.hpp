#pragma once
#include <abyss/controllers/Actors/base/IActor.hpp>
#include <Siv3D/Vector2D.hpp>
#include <memory>

namespace abyss::Actor::CodeZero
{
    namespace Body
    {
        class BodyVM;
    }
    namespace Head
    {
        class HeadVM;
    }
    namespace Hand
    {
        class HandVM;
    }
}
namespace abyss::Actor::CodeZero::Demo
{
    /// <summary>
    /// デモ用
    /// </summary>
    class DemoActor : public IActor
    {
    private:
        s3d::Vec2 m_pos;
        s3d::Vec2 m_targetPos;
        std::unique_ptr<Body::BodyVM> m_bodyVM;
        std::unique_ptr<Head::HeadVM> m_headVM;
        std::unique_ptr<Hand::HandVM> m_leftHandVM;
        std::unique_ptr<Hand::HandVM> m_rightHandVM;
    public:
        DemoActor(const s3d::Vec2& pos);

        bool moveToTarget(double dt);
        void setPos(const s3d::Vec2& pos)
        {
            m_pos = pos;
        }
        const s3d::Vec2& getPos()const
        {
            return m_pos;
        }
        const s3d::Vec2& getTargetPos()const
        {
            return m_targetPos;
        }
    };

}