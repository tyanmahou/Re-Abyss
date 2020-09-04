#pragma once
#include <abyss/models/Actors/base/IComponent.hpp>
#include <abyss/models/Actors/base/IPreDrawModel.hpp>
#include <abyss/utils/Ref/Ref.hpp>
#include <abyss/commons/Fwd.hpp>

namespace abyss::Actor::Ooparts
{
    class PursuitModel:
        public IComponent,
        public IPreDrawModel
    {
    private:
        IActor* m_pActor = nullptr;
        Ref<BodyModel> m_body = nullptr;
        Ref<BodyModel> m_pParent = nullptr;

        s3d::Vec2 m_localPos;
        bool m_isPursuit = true;
    public:
        PursuitModel(IActor* pActor, const Ref<BodyModel>& pParent);

        void setup() override;
        void onPreDraw(double dt) override;

        PursuitModel& setLocalPos(const s3d::Vec2& pos)
        {
            m_localPos = pos;
            return *this;
        }
        PursuitModel& setIsPursuit(bool active)
        {
            m_isPursuit = active;
            return *this;
        }
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::Ooparts::PursuitModel>
    {
        using Base = IPreDrawModel;
    };
}