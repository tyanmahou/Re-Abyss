#pragma once
#include <memory>
#include <abyss/commons/Fwd.hpp>

#include <abyss/models/Actors/base/IComponent.hpp>
#include <abyss/models/Actors/base/IDrawModel.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::LaunShark::Shot
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
            Wait,
            Firinged,
            Pursuit,
        };
    private:
        Kind m_kind = Kind::None;

        IActor* m_pActor = nullptr;
        Ref<BodyModel> m_body;
        Ref<RotateModel> m_rotate;
        Ref<HPModel> m_hp;
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
    struct ComponentTree<LaunShark::Shot::DrawModel>
    {
        using Base = IDrawModel;
    };
}