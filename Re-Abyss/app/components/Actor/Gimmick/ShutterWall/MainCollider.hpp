#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/components/Actor/Common/Col/Collider/ICollider.hpp>
#include <abyss/components/Actor/Gimmick/ShutterWall/ShutterCtrl.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Actor::Gimmick::ShutterWall
{
    class MainCollider final : public Col::ICollider
    {
    public:
        MainCollider(ActorObj* pActor);
    private:
        void onStart() override;
        CShape getCollider() const override;
    private:
        ActorObj* m_pActor = nullptr;
        Ref<ShutterCtrl> m_shutter;
    };
}
