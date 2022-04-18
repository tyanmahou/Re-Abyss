#pragma once
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/components/Actor/base/IPreDraw.hpp>
#include <abyss/components/Actor/base/IDraw.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/HideCtrl.hpp>
#include <abyss/utils/Ref/Ref.hpp>
#include <Siv3D/Vector2D.hpp>

namespace abyss::Actor::Gimmick::CodeZeroBack
{
    class Main :
        public IComponent,
        public IPreDraw,
        public IDraw
    {
    public:
        Main(ActorObj* pActor, const s3d::Vec2& pos);
    public:
        void onStart() override;

        void onPreDraw() override;
        void onDraw() const override;
    private:
        ActorObj* m_pActor;
        s3d::Vec2 m_pos;

        bool m_isFind = false;
        Ref<Enemy::CodeZero::HideCtrl> m_hideCtrl;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::Gimmick::CodeZeroBack::Main>
    {
        using Base = MultiComponents<
            Actor::IPreDraw,
            Actor::IDraw
        >;
    };
}
