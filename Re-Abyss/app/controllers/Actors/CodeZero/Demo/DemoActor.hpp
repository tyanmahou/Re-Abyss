#pragma once
#include <abyss/controllers/Actors/base/IActor.hpp>
#include <Siv3D/Vector2D.hpp>
#include <memory>

namespace abyss::CodeZero
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
namespace abyss::CodeZero::Demo
{
    /// <summary>
    /// デモ用
    /// </summary>
    class DemoActor : public IActor
    {
    private:
        s3d::Vec2 m_pos;
        std::unique_ptr<Body::BodyVM> m_bodyVM;
        std::unique_ptr<Head::HeadVM> m_headVM;
        std::unique_ptr<Hand::HandVM> m_leftHandVM;
        std::unique_ptr<Hand::HandVM> m_rightHandVM;
    public:
        DemoActor(const s3d::Vec2& pos);

        void draw() const override;

        CShape getCollider() const
        {
            return s3d::none;
        }

        void setPos(const s3d::Vec2& pos)
        {
            m_pos = pos;
        }
        const s3d::Vec2& getPos()const
        {
            return m_pos;
        }
    };

}