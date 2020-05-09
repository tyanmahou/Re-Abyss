#pragma once
#include <abyss/models/Actors/base/IUpdateModel.hpp>
#include <abyss/commons/Fwd.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Slime::Sencer
{
    class ParentCtrlModel;
    class CollisionModel;

    class MainUpdateModel : public IUpdateModel
    {
        IActor* m_pActor;
        Ref<ParentCtrlModel> m_parentCtrl;
        Ref<CollisionModel> m_collision;
        Ref<PosModel> m_pos;
    public:
        MainUpdateModel(IActor* pActor);
        void setup() override;
        void onUpdate(double dt) override;
    };
}
namespace abyss
{
    template<>
    struct ComponentTree<Slime::Sencer::MainUpdateModel>
    {
        using Base = IUpdateModel;
    };
}