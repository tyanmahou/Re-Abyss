#pragma once
#include <memory>
#include <abyss/commons/Fwd.hpp>

#include <abyss/models/Actors/base/IComponent.hpp>
#include <abyss/models/Actors/base/IDrawModel.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::CodeZero::Shot
{
    class ShotVM;

    class DrawModel :
        public IComponent,
        public IDrawModel
    {
    public:
        enum class Motion
        {
            None,
            Base,
            Charge,
        };
    private:
        Motion m_motion = Motion::Base;

        IActor* m_pActor = nullptr;
        Ref<BodyModel> m_body;
        Ref<ScaleModel> m_scale;
        std::unique_ptr<ShotVM> m_view;

    public:
        DrawModel(IActor* pActor);

        void setup() override;

        void request(Motion motion)
        {
            m_motion = motion;
        }

        ShotVM* getBindedView()const;

        void onDraw() const override;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<CodeZero::Shot::DrawModel>
    {
        using Base = IDrawModel;
    };
}