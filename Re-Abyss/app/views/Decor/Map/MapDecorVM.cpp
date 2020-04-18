#include "MapDecorVM.hpp"
#include <abyss/controllers/Decor/DecorGraphicsManager.hpp>
namespace abyss
{
    MapDecorVM::MapDecorVM(
        DecorGraphicsManager* manager,
        const MapDecorModel& model
    ):
        m_manager(manager),
        m_model(model)
    {}
    void MapDecorVM::draw(const s3d::RectF & screen) const
    {
        if (m_model.isInScreen(screen)) {
            auto tex = m_manager->getTexture(m_model.getGId());
            tex.draw(m_model.region().pos);
        }
    }
}
