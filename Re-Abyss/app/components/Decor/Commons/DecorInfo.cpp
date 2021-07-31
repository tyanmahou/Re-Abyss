#include "DecorInfo.hpp"
#include <abyss/modules/Decor/base/DecorObj.hpp>
#include <abyss/modules/Decor/DecorBuildUtil.hpp>
#include <abyss/modules/Camera/Camera.hpp>

namespace abyss::Decor
{
    DecorInfo::DecorInfo(DecorObj* pObj, const DecorEntity& entity):
        m_pObj(pObj),
        m_entity(entity)
    {}
    bool DecorInfo::isInScreen(const s3d::RectF & screen) const
    {
        return DecorBuildUtil::IsInScreen(m_entity, screen);
    }
    s3d::RectF DecorInfo::toRect() const
    {
        return DecorBuildUtil::ToRect(m_entity);
    }
    s3d::Vec2 DecorInfo::parallaxPos() const
    {
        const auto& cameraPos = m_pObj->getModule<Camera>()->getPos();
        return m_entity.pos + cameraPos - cameraPos * m_entity.parallax;
    }
    s3d::Quad DecorInfo::toQuad() const
    {
        return DecorBuildUtil::ToQuad(m_entity);
    }
    s3d::Quad DecorInfo::toParallaxQuad() const
    {
        return DecorBuildUtil::ToQuad(parallaxPos(), m_entity);
    }
}
