#pragma once
#include <memory>
#include <abyss/commons/Fwd.hpp>

#include <abyss/models/Actors/base/IComponent.hpp>
#include <abyss/models/Actors/base/IDrawModel.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::RollingTako
{
    class RollingTakoVM;

    class DrawModel :
        public IComponent,
        public IDrawModel
    {
    public:
        enum class Kind
        {
            None,
            Wait,
            Run,
        };
    private:
        Kind m_kind = Kind::None;

        IActor* m_pActor = nullptr;
        Ref<BodyModel> m_body;
        Ref<HPModel> m_hp;
        std::unique_ptr<RollingTakoVM> m_view;

    public:
        DrawModel(IActor* pActor);

        void setup() override;

        void request(Kind kind)
        {
            m_kind = kind;
        }

        RollingTakoVM* getBindedView()const;

        void onDraw() const override;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<RollingTako::DrawModel>
    {
        using Base = IDrawModel;
    };
}