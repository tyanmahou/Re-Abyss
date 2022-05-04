#pragma once
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/components/Effect/base/IDrawParts.hpp>
#include <abyss/components/Effect/Actor/Item/Recovery/LocationCtrl.hpp>
#include <abyss/utils/Ref/Ref.hpp>
#include <Siv3D/ColorF.hpp>

namespace abyss::Effect::Actor::Item::Recovery
{
    class Particles :
        public IComponent,
        public IDrawParts
    {
        struct Particle
        {
        public:
            Particle(bool isFrame, bool isColor0);

            bool update(const s3d::Vec2& pos, double t);
        private:
            s3d::Vec2 m_localPos;
            double m_size;
            double m_angle;
            bool m_isFrame;
            s3d::ColorF m_color;
        };
    public:
        Particles(EffectObj* pObj);
    public:
        void onStart() override;

        bool onDraw(double time) override;

    private:
        EffectObj* m_pObj;
        Ref<LocationCtrl> m_location;
        s3d::Array<Particle> m_particles;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Effect::Actor::Item::Recovery::Particles>
    {
        using Base = MultiComponents<
            Effect::IDrawParts
        >;
    };
}