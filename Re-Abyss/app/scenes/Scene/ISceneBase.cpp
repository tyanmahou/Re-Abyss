#include <abyss/scenes/Scene/ISceneBase.hpp>

namespace abyss
{
    void ISceneBase::update()
    {
        fader().update();
        if (loader().update()) {
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
        bool isLoading = loader().isLoading();
        if (!isLoading) {
            this->onSceneDraw();
        }
        fader().draw();

        if (isLoading) {
            loader().draw();
            return;
        }
    }
}
