#include <abyss/scenes/Scene/ISceneBase.hpp>

namespace abyss
{
    void ISceneBase::update()
    {
        if (loader().isLoading()) {
            return;
        }
#if ABYSS_DEBUG
        m_reloader.detection();
#endif
        this->onSceneUpdate();
    }
    void ISceneBase::draw() const
    {
        this->onSceneDraw();
    }
}
