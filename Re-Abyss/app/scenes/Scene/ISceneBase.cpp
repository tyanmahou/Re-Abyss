#include <abyss/scenes/Scene/ISceneBase.hpp>

namespace abyss
{
    void ISceneBase::update()
    {
        if (this->getData().loader.update()) {
            // ローディング
            return;
        }
#if ABYSS_NO_BUILD_RESOURCE
        m_reloader.detection();
#endif
        this->onSceneUpdate();
    }
    void ISceneBase::draw() const
    {
        if (this->getData().loader.isLoading()) {
            this->getData().loader.draw();
            return;
        }
        this->onSceneDraw();
    }
}
