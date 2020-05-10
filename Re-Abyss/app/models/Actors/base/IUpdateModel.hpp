#pragma once
#include <abyss/models/Actors/base/IComponent.hpp>
namespace abyss
{
    class IUpdateModel : virtual public IComponent
    {
    public:

        virtual void onUpdate(double dt) = 0;
    };
}