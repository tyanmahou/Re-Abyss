#include <abyss/scenes/Scene/ISceneBase.hpp>

namespace abyss
{
    void ISceneBase::update()
    {
        this->fader().update();
        if (this->loader().update()) {
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
        bool isLoading = this->loader().isLoading();
        if (!isLoading) {
            this->onSceneDraw();
        }
        this->fader().draw();

        if (isLoading) {
            this->loader().draw();
            return;
        }
    }
}
