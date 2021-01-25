#include "ISceneBase.hpp"
#include <abyss/debugs/Menu/Menu.hpp>

namespace abyss
{
    void ISceneBase::update()
    {
#if ABYSS_NO_BUILD_RESOURCE
        m_reloader.detection();
#endif
        this->onSceneUpdate();
    }
    void ISceneBase::draw() const
    {
        this->onSceneDraw();
#if ABYSS_DEBUG
        Debug::Menu::OnGUI();
#endif
    }
}
