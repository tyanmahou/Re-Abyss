#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/components/Actor/Common/DrawBase.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Actor
{
    /// <summary>
    /// ライト制御
    /// </summary>
    class LightCtrl:
        public IComponent,
        public DrawBase
    {
        ActorObj* m_pActor;
        
        Ref<Body> m_body;
        double m_radius = 2.0;
        double m_brightness = 1.0;
    public:
        LightCtrl(ActorObj* pActor);

        void onStart()override;
        void onDraw() const override;

        LightCtrl& setRadius(double radius)
        {
            m_radius = radius;
            return *this;
        }

        LightCtrl& setBrightness(double brightness)
        {
            m_brightness = brightness;
            return *this;
        }
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::LightCtrl>
    {
        using Base = Actor::DrawBase;
    };
}