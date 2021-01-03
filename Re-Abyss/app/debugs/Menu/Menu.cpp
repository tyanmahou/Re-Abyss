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
            // 描画
            m_gui.draw();

            // FPS制御
            if (m_gui.hasChanged(U"cb-fix-fps") || 
                m_gui.hasChanged(U"sl-fps")
            ) {
                const bool isFixFps = m_gui.checkBox(U"cb-fix-fps");
                std::get<SimpleGUIWidget::Slider>(m_gui.widget(U"sl-fps").widget).enabled = isFixFps;
                if (isFixFps) {
                    Graphics::SetTargetFrameRateHz(m_gui.slider(U"sl-fps"));
                } else {
                    Graphics::SetTargetFrameRateHz(s3d::none);
                }
            }
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

