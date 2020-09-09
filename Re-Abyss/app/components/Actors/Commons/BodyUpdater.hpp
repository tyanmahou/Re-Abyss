#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/utils/Ref/Ref.hpp>
#include <abyss/components/base/IComponent.hpp>
#include <abyss/models/Actors/base/IMoveModel.hpp>

namespace abyss::Actor
{
    class BodyUpdater :
        public IComponent,
        public IMoveModel
    {
    private:
        IActor* m_pActor = nullptr;
        Ref<Body> m_body;

        bool m_isActive = true;
    public:
        BodyUpdater(IActor* pActor);

        void setup() override;
        void onMove(double dt) override;

        BodyUpdater& setActive(bool isActive)
        {
            m_isActive = isActive;
            return *this;
        }
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::BodyUpdater>
    {
        using Base = IMoveModel;
    };
}