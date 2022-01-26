#include <abyss/utils/Windows/WindowMenu/WindowMenu.hpp>
#include <abyss/utils/Windows/CustomWindowProc/CustomWindowProc.hpp>
#include <Siv3D.hpp>
#include <variant>

namespace 
{
    UINT g_wId = 0;

    enum MenuKind
    {
        Invalid,
        Popup,
        Button,
        CheckButton,
        RadioButton,
    };

    struct ButtonInfo
    {
        std::function<void()> callback;
    };

    struct CheckButtonInfo
    {
        HMENU parent;
        std::function<void(bool)> callback;
    };

    struct RadioButtonInfo
    {
        HMENU parent;
        UINT firstWId;
        UINT lastWId;
        std::function<void(size_t)> callback;
    };

    struct MenuStatus
    {
        MenuKind kind = MenuKind::Invalid;
        std::variant<ButtonInfo, CheckButtonInfo, RadioButtonInfo> info;
    };
    s3d::HashTable<s3d::int32, MenuStatus> g_status;

    struct ShareData
    {
        HWND hWnd;
        s3d::Array<UINT> useWIds;
    };

    bool ExecButton(UINT wId)
    {
        if (auto callback = std::get<ButtonInfo>(g_status[wId].info).callback; callback) {
            callback();
            return true;
        }
        return false;
    }

    void CheckMenu(HMENU hMenu, UINT wId, bool isChecked)
    {
        if (isChecked) {
            ::CheckMenuItem(hMenu, wId, MF_BYCOMMAND | MFS_CHECKED);
        } else {
            ::CheckMenuItem(hMenu, wId, MF_BYCOMMAND | MFS_UNCHECKED);
        }
    }
    bool ExecCheckButton(UINT wId)
    {
        auto&& [hMenu, callback] = std::get<CheckButtonInfo>(g_status[wId].info);
        bool isCheckedNext = !(::GetMenuState(hMenu, wId, MF_BYCOMMAND) & MFS_CHECKED) != 0;
        CheckMenu(hMenu, wId, isCheckedNext);
        if (callback) {
            callback(isCheckedNext);
            return true;
        }
        return false;
    }

    bool ExecCheckRadioButton(UINT wId)
    {
        auto&& [hMenu, firstWId, lastWId, callback] = std::get<RadioButtonInfo>(g_status[wId].info);
        ::CheckMenuRadioItem(hMenu, firstWId, lastWId, wId, MF_BYCOMMAND);
        if (callback) {
            callback(static_cast<size_t>(wId - firstWId));
            return true;
        }
        return false;
    }
}
namespace abyss::Windows
{
    class MenuItem::Impl
    {
    public:
        Impl(const s3d::String& name, ShareData* pShareData, HMENU hParentMenu):
            m_name(name.toWstr()),
            m_pShareData(pShareData),
            m_hParentMenu(hParentMenu),
            m_wId(++g_wId)
        {
            m_hMenu = ::CreateMenu();

            {
                MENUITEMINFO mi = this->getItemInfo(MIIM_STRING);
                InsertMenuItem(m_hParentMenu, m_wId, FALSE, &mi);
            }
            m_pShareData->useWIds.push_back(m_wId);
        }
        void setButton(const std::function<void()>& callback)
        {
            {
                this->setItemInfo(MIIM_STRING);
            }
            g_status[m_wId].kind = MenuKind::Button;
            g_status[m_wId].info = ButtonInfo{
                .callback = callback
            };
        }
        void setCheckButton(const std::function<void(bool)>& callback, bool isChecked)
        {
            {
                this->setItemInfo(MIIM_STRING);
            }
            g_status[m_wId].kind = MenuKind::CheckButton;
            g_status[m_wId].info = CheckButtonInfo{
                .parent = m_hParentMenu,
                .callback = callback
            };

            ::CheckMenu(m_hParentMenu, m_wId, isChecked);
        }
        void setRadioCheckButton(const std::function<void(size_t)>& callback, std::pair<UINT, UINT> firstLastWId)
        {
            {
                this->setItemInfo(MIIM_STRING);
            }
            g_status[m_wId].kind = MenuKind::RadioButton;
            g_status[m_wId].info = RadioButtonInfo{
                .parent = m_hParentMenu,
                .firstWId = firstLastWId.first,
                .lastWId = firstLastWId.second,
                .callback = callback
            };
        }
        void createSeperator()
        {
            AppendMenuW(m_hMenu, MF_SEPARATOR, 0, NULL);
        }

        bool enabled() const
        {
            return (::GetMenuState(m_hParentMenu, m_wId, MF_BYCOMMAND) & MFS_GRAYED) == 0;
        }
        void setEnabled(bool enabled)
        {
            auto flag = enabled ? MFS_ENABLED : MFS_GRAYED;

            ::EnableMenuItem(m_hParentMenu, m_wId, MF_BYCOMMAND | flag);
        }
        MenuItem createItem(const s3d::String& name)
        {
            {
                this->setItemInfo(MIIM_STRING | MIIM_SUBMENU);
            }

            g_status[m_wId].kind = MenuKind::Popup;
            return MenuItem(this->createItemRaw(name));
        }
        s3d::Array<MenuItem> createRadioButton(const s3d::Array<s3d::String>& name, std::function<void(size_t)> callback, size_t checkIndex)
        {
            {
                this->setItemInfo(MIIM_STRING | MIIM_SUBMENU);
            }
            s3d::Array<MenuItem> items;
            for (auto&& elm : name) {
                items.emplace_back(this->createItemRaw(elm));
            }
            if (!items.isEmpty()) {
                auto firstWId = items.front().m_pImpl->m_wId;
                auto lastWId = items.back().m_pImpl->m_wId;

                for (auto&& item : items) {
                    item.m_pImpl->setRadioCheckButton(callback, { firstWId, lastWId });
                }
                checkIndex = s3d::Clamp<size_t>(checkIndex, 0, static_cast<size_t>(items.size() - 1));
                ::CheckMenuRadioItem(m_hMenu, firstWId, lastWId, firstWId + static_cast<UINT>(checkIndex), MF_BYCOMMAND);
            }
            return items;
        }
        s3d::String name() const
        {
            return s3d::Unicode::FromWstring(m_name);
        }
        void release() const
        {
            ::DeleteMenu(m_hParentMenu, m_wId, FALSE);
        }
    private:
        std::shared_ptr<Impl> createItemRaw(const s3d::String& name)
        {
            return std::make_shared<MenuItem::Impl>(name, m_pShareData, m_hMenu);
        }
        void setItemInfo(UINT mask)
        {
            auto mi = this->getItemInfo(mask);
            SetMenuItemInfo(m_hParentMenu, m_wId, FALSE, &mi);
        }
        MENUITEMINFO getItemInfo(UINT mask)
        {
            MENUITEMINFO mi;
            memset(&mi, 0, sizeof(MENUITEMINFO));
            mi.cbSize = sizeof(MENUITEMINFO);
            mi.fMask = MIIM_ID | mask;
            mi.wID = m_wId;
            mi.hSubMenu = m_hMenu;
            mi.dwTypeData = const_cast<LPWSTR>(m_name.data());
            return mi;
        }
    private:
        std::wstring m_name;
        ShareData* m_pShareData;
        HMENU m_hParentMenu;
        HMENU m_hMenu;
        UINT m_wId;
    };
    class WindowMenu::Impl
    {
    public:
        Impl()
        {
            m_shareData.hWnd = static_cast<HWND>(s3d::Platform::Windows::Window::GetHWND());
            m_hMenu = ::CreateMenu();

            m_winProc.setCallback([](HWND , UINT message, WPARAM wParam, LPARAM )->s3d::Optional<LRESULT> {
                switch (message) {
                case WM_COMMAND:
                {
                    auto wId = LOWORD(wParam);
                    switch (g_status[wId].kind) {
                    case MenuKind::Button:
                        if (::ExecButton(wId)) {
                            return 0;
                        }
                        break;
                    case MenuKind::CheckButton:
                        if (::ExecCheckButton(wId)) {
                            return 0;
                        }
                        break;
                    case MenuKind::RadioButton:
                        if (::ExecCheckRadioButton(wId)) {
                            return 0;
                        }
                        break;
                    default:
                        break;
                    }
                }
                break;
                default:
                    break;
                }
                return s3d::none;
            });
        }
        ~Impl()
        {
            this->release();
        }
        bool isShow() const
        {
            return m_hMenu == ::GetMenu(m_shareData.hWnd);
        }
        void show(bool show)
        {
            if (show) {
                ::SetMenu(m_shareData.hWnd, m_hMenu);
            } else if(this->isShow()) {
                ::SetMenu(m_shareData.hWnd, NULL);
            }
        }
        MenuItem createItem(const s3d::String& name)
        {
            return MenuItem(std::make_shared<MenuItem::Impl>(name, &m_shareData, m_hMenu));
        }
        void release()
        {
            for (auto wId : m_shareData.useWIds) {
                g_status[wId] = MenuStatus{};
            }
            this->show(false);
            ::DestroyMenu(m_hMenu);
        }
    private:
        ShareData m_shareData;
        HMENU m_hMenu;
        CustomWindowProc m_winProc;
    };

    WindowMenu& Windows::WindowMenu::Main()
    {
        static WindowMenu menu;
        return menu;
    }

    WindowMenu::WindowMenu():
        m_pImpl(std::make_shared<Impl>())
    {}
    bool WindowMenu::isShow() const
    {
        return m_pImpl->isShow();
    }
    void WindowMenu::show(bool show)
    {
        m_pImpl->show(show);
    }
    MenuItem WindowMenu::createItem(const s3d::String& name)
    {
        return m_pImpl->createItem(name);
    }
    MenuItem WindowMenu::createPopup(const s3d::String& name, std::function<void(MenuItem)> setup)
    {
        auto popup = this->createItem(name);
        setup(popup);
        return popup;
    }
    MenuItem::MenuItem(std::shared_ptr<Impl> pImpl):
        m_pImpl(pImpl)
    {}
    MenuItem::SubMenu MenuItem::createItem(const s3d::String& name)
    {
        return m_pImpl->createItem(name);
    }
    MenuItem& Windows::MenuItem::setButton(std::function<void()> callback)
    {
        m_pImpl->setButton(callback);
        return *this;
    }
    MenuItem::SubMenu MenuItem::createButton(const s3d::String& name, std::function<void()> callback)
    {
        return this->createItem(name).setButton(callback);
    }
    MenuItem& Windows::MenuItem::setCheckButton(std::function<void(bool)> callback, bool isChecked)
    {
        m_pImpl->setCheckButton(callback, isChecked);
        return *this;
    }
    MenuItem::SubMenu MenuItem::createCheckButton(const s3d::String& name, std::function<void(bool)> callback, bool isChecked)
    {
        return this->createItem(name).setCheckButton(callback, isChecked);
    }
    s3d::Array<MenuItem::SubMenu> MenuItem::createRadioButton(const s3d::Array<s3d::String>& name, std::function<void(size_t)> callback, size_t checkIndex)
    {
        return m_pImpl->createRadioButton(name, callback, checkIndex);
    }
    MenuItem::SubMenu MenuItem::createPopup(const s3d::String& name, std::function<void(MenuItem)> setup)
    {
        auto sub = this->createItem(name);
        setup(sub);
        return sub;
    }
    void MenuItem::createSeperator()
    {
        m_pImpl->createSeperator();
    }

    bool MenuItem::enabled() const
    {
        return m_pImpl->enabled();
    }

    void MenuItem::setEnabled(bool enabled)
    {
        m_pImpl->setEnabled(enabled);
    }
    s3d::String MenuItem::name() const
    {
        return m_pImpl->name();
    }
    MenuItem::operator bool() const
    {
        return static_cast<bool>(m_pImpl);
    }
    void MenuItem::release() const
    {
        return m_pImpl->release();
    }
}