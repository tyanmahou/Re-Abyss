#pragma once
#include <memory>
#include <abyss/commons/Fwd.hpp>

#include <abyss/models/Actors/base/IComponent.hpp>
#include <abyss/models/Actors/base/IDrawModel.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::CaptainTako::Shot
{
    class ShotVM;

    class DrawModel :
        public IComponent,
        public IDrawModel
    {
    public:
        enum class Kind
        {
            None,
            Base,
        };
    private:
        Kind m_kind = Kind::Base;

        IActor* m_pActor = nullptr;
        Ref<BodyModel> m_body;
        std::unique_ptr<ShotVM> m_view;

    public:
        DrawModel(IActor* pActor);

        void setup() override;

        void request(Kind kind)
        {
            m_kind = kind;
        }

        ShotVM* getBindedView()const;

        void onDraw() const override;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<CaptainTako::Shot::DrawModel>
    {
        using Base = IDrawModel;
    };
}