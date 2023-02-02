#include <abyss/scenes/Scene/ISceneBase.hpp>

namespace abyss
{
    void ISceneBase::update()
    {
        if (!this->getData().loading.isDone()) {
            return;
        }
#if ABYSS_NO_BUILD_RESOURCE
        m_reloader.detection();
#endif
        this->onSceneUpdate();
    }
    void ISceneBase::draw() const
    {
        if (!this->getData().loading.isDone()) {
            this->getData().loading.draw();
            return;
        }
        this->onSceneDraw();
    }
}
