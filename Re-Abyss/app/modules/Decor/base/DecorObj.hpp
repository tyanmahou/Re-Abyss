#pragma once
#include <abyss/modules/GameObject/GameObject.hpp>

namespace abyss::Decor
{
    class DecorObj final : public GameObject
    {
    public:
        DecorObj();

        void update();
        void draw() const;
    private:
    };
}