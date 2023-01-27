#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/modules/Actor/base/ILastUpdate.hpp>
#include <abyss/components/Actor/Common/DamageCtrl.hpp>
#include <abyss/components/Actor/Common/IStateCallback.hpp>
#include <abyss/utils/Ref/Ref.hpp>
#include <abyss/utils/TimeLite/Timer.hpp>
#include <Siv3D/Vector2D.hpp>

namespace abyss::Actor::Enemy::KingDux
{
    class EyeCtrl final:
        public IComponent,
        public ILastUpdate,
        public IStateCallback
    {
    public:
        enum class Mode
        {
            Default,
            Dance,
            Angry,
        };
    public:
        EyeCtrl(ActorObj* pActor);

        void onStart() override;

        void onLastUpdate() override;

        const s3d::Vec2& getEyePosL() const
        {
            return m_eyePosL;
        }
        const s3d::Vec2& getEyePosR() const
        {
            return m_eyePosR;
        }

        void onStateStart() override;

        void setDanceMode();
        void setAngryMode();
    private:
        void updateDefault();
        void updateDance();
        void updateAngry();
    private:
        ActorObj* m_pActor = nullptr;
        Ref<Body> m_body;
        Ref<HP> m_hp;
        Ref<DamageCtrl> m_damage;

        s3d::Vec2 m_eyePosL{0, 0};
        s3d::Vec2 m_eyePosR{0, 0};

        Mode m_mode = Mode::Default;
        TimeLite::Timer m_timer{2.0};
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::Enemy::KingDux::EyeCtrl>
    {
        using Base = MultiComponents<
            Actor::ILastUpdate,
            Actor::IStateCallback
        >;
    };
}