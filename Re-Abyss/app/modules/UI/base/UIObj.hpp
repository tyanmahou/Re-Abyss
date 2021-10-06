#pragma once
#include <Siv3D/Fwd.hpp>
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/GameObject/GameObject.hpp>

namespace abyss::UI
{
    class UIObj final : public GameObject
    {
    public:

        void update();
        void postUpdate();

        void draw() const;

        double deltaTime() const;
    };
}