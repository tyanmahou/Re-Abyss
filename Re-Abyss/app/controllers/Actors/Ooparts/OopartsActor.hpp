#pragma once
#include <abyss/controllers/Actors/base/IActor.hpp>

namespace abyss::Ooparts
{
    class DrawModel;

    class OopartsVM;

    class OopartsActor:
        public IActor
    {
    protected:
        Ref<BodyModel> m_body;

    public:
        OopartsActor(IActor* parent);

        void start() override;
        virtual OopartsVM* getBindedView() const = 0;
    };
}