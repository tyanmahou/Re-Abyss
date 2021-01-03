#if ABYSS_DEBUG
#include "Menu.hpp"
#include <abyss/commons/Path.hpp>
#include <Siv3D.hpp>

namespace abyss::Debug
{
    class Menu::Impl
    {
        inline static const String MenuTomlPath = Path::DebugPath + U"menu.toml";

        bool m_isActive = false;
        SimpleGUIManager m_gui;
        DirectoryWatcher m_watcher;
    public:
        Impl():
            m_gui(MenuTomlPath),
            m_watcher(FileSystem::ParentPath(MenuTomlPath))
        {}
        bool isDebug(StringView label)
        {
            return m_gui.checkBox(label);
        }
        void onGUI()
        {
            if (!m_watcher.retrieveChanges().isEmpty()) {
                m_gui.load(MenuTomlPath);
            }
            if (KeyF11.down()) {
                m_isActive = !m_isActive;
            }
            if (!m_isActive) {
                return;
            }
            m_gui.draw();
        }
    };
    Menu::Menu():
        m_pImpl(std::make_unique<Impl>())
    {}
    bool Menu::IsDebug(StringView label)
    {
        return Instance()->m_pImpl->isDebug(label);
    }
    void Menu::OnGUI()
    {
        Instance()->m_pImpl->onGUI();
    }
}
#endif

