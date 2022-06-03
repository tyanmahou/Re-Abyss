#if ABYSS_DEBUG
#include <abyss/debugs/Menu/Menu.hpp>
#include <abyss/commons/Path.hpp>
#include <abyss/utils/DebugMenu/Menu.hpp>
#include <Siv3D.hpp>

namespace abyss::Debug
{
    class Menu::Impl
    {
        inline static const String MenuPath = Path::DebugPath + U"menu.xml";
    public:
        Impl():
            m_menu(DebugMenu::Menu::FromXML(MenuPath))
        {}
        void update()
        {
            m_menu.update();
            m_menu.draw();
        }
        bool isDebug(const String& label)
        {
            return m_menu.root().find(label).value().toBool();
        }
        size_t debugSelect(const s3d::String& label)
        {
            return m_menu.root().find(label).value().toIndex();
        }
        bool isRequestedClose() const
        {
            return m_isRequestedClose;
        }
        void setRequestedClose(bool value)
        {
            m_isRequestedClose = value;
        }
    private:
        DebugMenu::Menu m_menu;
        bool m_isRequestedClose = false;
    };
    Menu::Menu() :
        m_pImpl(std::make_unique<Impl>())
    {}
    void Menu::Update()
    {
        Instance()->m_pImpl->update();
    }
    bool Menu::IsDebug(const String& label)
    {
        return Instance()->m_pImpl->isDebug(label);
    }
    size_t Menu::DebugSelect(const s3d::String& label)
    {
        return Instance()->m_pImpl->debugSelect(label);
    }
    bool Menu::IsRequestedClose()
    {
        return Instance()->m_pImpl->isRequestedClose();
    }
    void Menu::RequestClose()
    {
        Instance()->m_pImpl->setRequestedClose(true);
    }
    void Menu::ResetRequestClose()
    {
        Instance()->m_pImpl->setRequestedClose(false);
    }
}
#endif

