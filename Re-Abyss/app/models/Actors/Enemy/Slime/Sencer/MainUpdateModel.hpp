#pragma once
#include <abyss/models/Actors/base/IComponent.hpp>
#include <abyss/models/Actors/base/IUpdateModel.hpp>
#include <abyss/commons/Fwd.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Slime::Sencer
{
    class ParentCtrlModel;

    class MainUpdateModel : 
        public IComponent,
        public IUpdateModel
    {
        IActor* m_pActor;
        Ref<ParentCtrlModel> m_parentCtrl;
        Ref<MapColliderModel> m_mapColl;
        Ref<BodyModel> m_body;
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