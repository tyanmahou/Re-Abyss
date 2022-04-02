#pragma once
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/components/Effect/base/IDraw.hpp>
#include <Siv3D/Vector2D.hpp>

namespace abyss::Effect::Actor
{
    class EnemyDeadVM;
}
namespace abyss::Effect::Actor::EnemyDead
{
    class Main :
        public IComponent,
        public IDraw
    {
    public:
        Main(EffectObj* pObj, const s3d::Vec2& pos);
        ~Main();

    public:
        bool onDraw(double time) override;

    private:
        EffectObj* m_pObj;
        std::unique_ptr<Actor::EnemyDeadVM> m_view;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Effect::Actor::EnemyDead::Main>
    {
        using Base = MultiComponents<
            Effect::IDraw
        >;
    };
}