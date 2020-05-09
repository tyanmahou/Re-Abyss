#pragma once
#include <abyss/models/Actors/base/IComponent.hpp>
namespace abyss
{
    class ILastUpdateModel : public IComponent
    {
    public:

        virtual void onLastUpdate(double dt) = 0;
    };
}