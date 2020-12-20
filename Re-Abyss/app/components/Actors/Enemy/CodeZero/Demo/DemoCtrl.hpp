#pragma once
#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/components/base/IComponent.hpp>

#include <Siv3D/Vector2D.hpp>

namespace abyss::Actor::Enemy::CodeZero::Demo
{
    class DemoCtrl :
        public IComponent
    {
    public:
        DemoCtrl(IActor* pActor);

        bool moveToTarget(double dt);
        DemoCtrl& setPos(const s3d::Vec2& pos)
        {
            m_pos = pos;
            return *this;
        }
        const s3d::Vec2& getPos()const
        {
            return m_pos;
        }
        DemoCtrl& setTargetPos(const s3d::Vec2& pos)
        {
            m_targetPos = pos;
            return *this;
        }
        const s3d::Vec2& getTargetPos()const
        {
            return m_targetPos;
        }

        void destroy() const;
    private:
        IActor* m_pActor;
        s3d::Vec2 m_pos;
        s3d::Vec2 m_targetPos;
    };
}