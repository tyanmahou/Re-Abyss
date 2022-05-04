#pragma once
#include <abyss/modules/GameObject/IComponent.hpp>

namespace abyss::Effect
{
	class BossFadeMask final : public IComponent
	{

	};
}

namespace abyss
{
    template<>
    struct ComponentTree<Effect::BossFadeMask>
    {
        //using Base = Effect::IDraw;
    };
}