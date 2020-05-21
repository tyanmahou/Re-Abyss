#pragma once
#include <abyss/models/Actors/base/IComponent.hpp>
#include <abyss/models/Actors/base/IPreDrawModel.hpp>
#include <abyss/utils/Ref/Ref.hpp>
#include <abyss/commons/Fwd.hpp>

namespace abyss::Ooparts
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
    public:
        PursuitModel(IActor* pActor, const Ref<BodyModel>& pParent);

        void setup() override;
        void onPreDraw(double dt) override;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Ooparts::PursuitModel>
    {
        using Base = IPreDrawModel;
    };
}