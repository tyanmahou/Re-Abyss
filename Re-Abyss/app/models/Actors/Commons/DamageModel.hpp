#pragma once
#include <abyss/models/Actors/base/ICollisionCallbackModel.hpp>
#include <abyss/models/Actors/Commons/HPModel.hpp>
#include <abyss/utils/Ref/Ref.hpp>
namespace abyss
{
    class DamageModel : public ICollisionCallbackModel
    {
        Ref<experimental::HPModel> m_hp;
        IActor* m_pActor;
    public:
        DamageModel(IActor* pActor);

        void setup() override;
        void onCollisionStay(IActor* col)override;
    };
}