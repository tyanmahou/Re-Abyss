#include "DecorObj.hpp"
#include <abyss/components/Decor/base/IUpdate.hpp>
#include <abyss/components/Decor/base/IDraw.hpp>

namespace abyss::Decor
{
    DecorObj::DecorObj()
    {}

    void DecorObj::update()
    {
        for (auto&& com : this->finds<IUpdate>()) {
            com->onUpdate();
        }
    }

    void DecorObj::draw() const
    {
        for (auto&& com : this->finds<IDraw>()) {
            com->onDraw();
        }
    }

}
