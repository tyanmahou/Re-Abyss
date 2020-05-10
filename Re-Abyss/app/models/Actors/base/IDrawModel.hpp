#pragma once
#include <abyss/models/Actors/base/IComponent.hpp>
namespace abyss
{
    class IDrawModel : virtual public IComponent
    {
    public:

        virtual void onDraw()const = 0;
    };
}