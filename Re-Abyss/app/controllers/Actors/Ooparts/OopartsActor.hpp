#pragma once
#include <abyss/controllers/Actors/base/IActor.hpp>

namespace abyss::Ooparts
{
    class OopartsVM;

    class OopartsActor:
        public IActor
    {
    protected:
        Ref<BodyModel> m_body;
    public:
        OopartsActor(IActor* parent);

        virtual OopartsVM* getBindedView() const = 0;
    };
}