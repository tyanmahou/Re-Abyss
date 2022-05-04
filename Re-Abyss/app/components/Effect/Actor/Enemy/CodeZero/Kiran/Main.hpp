#pragma once
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/components/Effect/base/IUpdate.hpp>
#include <abyss/components/Effect/base/IDrawParts.hpp>
#include <Siv3D/Vector2D.hpp>

namespace abyss::Effect::Actor
{
    class KiranVM;
}
namespace abyss::Effect::Actor::Enemy::CodeZero::Kiran
{
    class Main :
        public IComponent,
        public IUpdate,
        public IDrawParts
    {
    public:
        Main(EffectObj* pObj, const s3d::Vec2& pos);
        ~Main();

    public:
        void onUpdate() override;
        bool onDraw(double time) override;

    private:
        EffectObj* m_pObj;
        std::unique_ptr<Actor::KiranVM> m_view;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Effect::Actor::Enemy::CodeZero::Kiran::Main>
    {
        using Base = MultiComponents<
            Effect::IUpdate,
            Effect::IDrawParts
        >;
    };
}