#include <abyss/scenes/base/ISceneBase.hpp>

namespace abyss
{
    void ISceneBase::update()
    {
        if (!m_loading.isDone()) {
            return;
        }
#if ABYSS_NO_BUILD_RESOURCE
        m_reloader.detection();
#endif
        this->onSceneUpdate();
    }
    void ISceneBase::draw() const
    {
        if (!m_loading.isDone()) {
            m_loading.draw();
            return;
        }
        this->onSceneDraw();
    }
}
