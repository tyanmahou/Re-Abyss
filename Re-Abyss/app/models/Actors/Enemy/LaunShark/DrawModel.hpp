#pragma once
#include <memory>
#include <abyss/commons/Fwd.hpp>

#include <abyss/models/Actors/base/IComponent.hpp>
#include <abyss/models/Actors/base/IDrawModel.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::LaunShark
{
    class LaunSharkVM;

    class DrawModel :
        public IComponent,
        public IDrawModel
    {
    public:
        enum class Kind
        {
            None,
            Swim,
            LaunShark,
            Attack,
        };
    private:
        Kind m_kind = Kind::None;

        IActor* m_pActor = nullptr;
        Ref<BodyModel> m_body;
        Ref<HPModel> m_hp;
        std::unique_ptr<LaunSharkVM> m_view;

        double m_transitionTime = 0.0f;
    public:
        DrawModel(IActor* pActor);

        void setup() override;

        void request(Kind kind)
        {
            m_kind = kind;
        }
        DrawModel& setTransitionTime(double time)
        {
            m_transitionTime = time;
            return *this;
        }
        LaunSharkVM* getBindedView()const;

        void onDraw() const override;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<LaunShark::DrawModel>
    {
        using Base = IDrawModel;
    };
}