#pragma once
#include <abyss/controllers/Actors/Enemy/Ikalien/IkalienActor.hpp>

namespace abyss::Ikalien
{
    class BaseState : public IOldState<IkalienActor>
    {
    protected:
        BodyModel* m_body;
        RotateModel* m_rotate;
    public:
        void setup()override;
    };
}
