#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/modules/Actor/base/ILastUpdate.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/HeadCtrl.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/PartsCtrl.hpp>

namespace abyss::Actor::Enemy::CodeZero
{
    /// <summary>
    /// 翼制御
    /// </summary>
    class WingCtrl: 
        public IComponent,
        public ILastUpdate
    {
    public:
        WingCtrl(ActorObj* pActor);

        const Vec2& localL() const
        {
            return m_localL;
        }
        const Vec2& localR() const
        {
            return m_localR;
        }
    public:
        void setup(Executer executer) override;
        void onStart() override;
        void onLastUpdate() override;
    private:
        ActorObj* m_pActor;
        Ref<HeadCtrl> m_head;
        Ref<PartsCtrl> m_parts;

        Vec2 m_localL{};
        Vec2 m_localTargetL{};
        Vec2 m_localR{};
        Vec2 m_localTargetR{};

        double m_elapsedTimeSec = 0;
    };
}
namespace abyss
{
    template<>
    struct ComponentTree<Actor::Enemy::CodeZero::WingCtrl>
    {
        using Base = MultiComponents<
            Actor::ILastUpdate
        >;
    };
}
