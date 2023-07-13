#if ABYSS_DEBUG
#include <abyss/debugs/Menu/Menu.hpp>
#include <abyss/commons/Path.hpp>
#include <abyss/utils/DebugMenu/Menu.hpp>
#include <Siv3D.hpp>

namespace abyss::Debug
{
    class Menu::Impl
    {
        inline static const FilePath MenuPath = Path::DebugPath + U"menu.xml";
        inline static const FilePath SavePath = Path::UserDataPath + U"DebugMenu/Root.json";
    public:
        Impl():
            m_menu(DebugMenu::Menu::FromXML(MenuPath))
        {}
        ~Impl()
        {
        }
        void update()
        {
            if (!m_isOpend) {
                return;
            }
            m_menu.update();
        }
        void draw() const
        {
            if (!m_isOpend) {
                return;
            }
            m_menu.draw();
        }
        bool isDebug(const String& label)
        {
            return m_menu.root().find(label).value().toBool();
        }
        void open()
        {
            m_isOpend = true;
        }
        void close()
        {
            m_isOpend = false;
        }
        bool isOpend() const
        {
            return m_isOpend;
        }
        void save() const
        {
            m_menu.save(SavePath);
        }
    private:
        DebugMenu::Menu m_menu;
        bool m_isOpend = false;
    };
    Menu::Menu() :
        m_pImpl(std::make_unique<Impl>())
    {}
    Menu::~Menu()
    {}
    void Menu::update()
    {
        m_pImpl->update();
    }
    void Menu::draw() const
    {
        m_pImpl->draw();
    }
    bool Menu::isDebug(const String& label) const
    {
        return m_pImpl->isDebug(label);
    }
    void Menu::open()
    {
        m_pImpl->open();
    }
    void Menu::close()
    {
        m_pImpl->close();
    }
    bool Menu::isOpend() const
    {
        return m_pImpl->isOpend();
    }
    void Menu::save() const
    {
        m_pImpl->save();
    }
}
#endif

