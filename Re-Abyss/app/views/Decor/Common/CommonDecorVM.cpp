#include "CommonDecorVM.hpp"
#include <abyss/controllers/Decor/DecorGraphicsManager.hpp>

namespace abyss
{
    CommonDecorVM::CommonDecorVM(
        DecorGraphicsManager* manager,
        const CommonDecorModel& model
    ):
        m_manager(manager),
        m_model(model)
    {}

    void CommonDecorVM::draw(const s3d::RectF & screen) const
    {
        if (m_model.isInScreen(screen)) {
            auto tex = m_manager
                ->getTexture(m_model.getGId(), m_time)
                .mirrored(m_model.isMirroed())
                .flipped(m_model.isFlipped())
            ;
            m_model.getQuad()(tex).draw();
        }
    }

}
