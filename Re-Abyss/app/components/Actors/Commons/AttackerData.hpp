#pragma once
#include <abyss/components/base/IComponent.hpp>
#include <abyss/utils/Ref/Ref.hpp>
#include <Siv3D/Vector2D.hpp>
namespace abyss::Actor
{
    class AttackerData final : public IComponent
    {
    public:
        AttackerData(IActor* pActor, s3d::int32 power) :
            m_pActor(pActor),
            m_power(power)
        {}

        void onStart() override;
        s3d::Vec2 getVelocity()const;
        s3d::int32 getPower()const { return m_power; }
    private:
        IActor* m_pActor;
        s3d::int32 m_power = 1;

        Ref<Body> m_body;
    };
}