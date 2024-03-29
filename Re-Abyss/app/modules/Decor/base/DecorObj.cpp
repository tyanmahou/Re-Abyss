#include <abyss/modules/Decor/base/DecorObj.hpp>
#include <abyss/modules/Decor/base/IUpdate.hpp>
#include <abyss/modules/Decor/base/IDraw.hpp>
#include <abyss/modules/DrawManager/DrawManager.hpp>

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
        auto drawer = this->getModule<DrawManager>();
        for (auto&& com : this->finds<IDraw>()) {
            drawer->add(com->getLayer(), [com] {
                com->onDraw();
            }, com->getOrder());
        }
    }

}
