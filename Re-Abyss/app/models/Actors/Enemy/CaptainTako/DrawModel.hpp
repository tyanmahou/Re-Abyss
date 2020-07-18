#pragma once
#include <memory>
#include <abyss/commons/Fwd.hpp>

#include <abyss/models/Actors/base/IComponent.hpp>
#include <abyss/models/Actors/base/IDrawModel.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::CaptainTako
{
    class CaptainTakoVM;

    class DrawModel :
        public IComponent,
        public IDrawModel
    {
    public:
        enum class Kind
        {
            None,
            Wait,
            Charge,
        };
    private:
        Kind m_kind = Kind::None;

        IActor* m_pActor = nullptr;
        Ref<BodyModel> m_body;
        Ref<HPModel> m_hp;

        double m_chargeTime = 0.0f;
        std::unique_ptr<CaptainTakoVM> m_view;

    public:
        DrawModel(IActor* pActor);

        void setup() override;

        void request(Kind kind)
        {
            m_kind = kind;
        }
        void setChargeTime(double chargeTime)
        {
            m_chargeTime = chargeTime;
        }
        CaptainTakoVM* getBindedView()const;

        void onDraw() const override;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<CaptainTako::DrawModel>
    {
        using Base = IDrawModel;
    };
}