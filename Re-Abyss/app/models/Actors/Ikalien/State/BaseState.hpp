#pragma once
#include <abyss/controllers/Actors/Ikalien/IkalienActor.hpp>

namespace abyss::Ikalien
{
    class BaseState : public IState<IkalienActor>
    {
    protected:
        BodyModel* m_body;
        RotateModel* m_rotate;
    public:
        void setup()override;
    };
}
