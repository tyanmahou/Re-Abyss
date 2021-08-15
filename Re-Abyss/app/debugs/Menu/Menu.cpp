#if ABYSS_DEBUG
#include "Menu.hpp"
#include <abyss/commons/Path.hpp>
#include <Siv3D.hpp>
namespace
{
    using namespace abyss;
    using namespace abyss::Debug;

    void ParseCheckButton(
        Windows::MenuItem& menu,
        const String& label,
        JSONValue& json,
        std::stack<String>& flagNamePath,
        s3d::HashTable<String, bool>& flags
    ) {
        bool isChecked = json[U"isChecked"].getOr<bool>(false);
        auto callback = [&flags, key = flagNamePath.top()](bool isChecked) {
            flags[key] = isChecked;
        };
        callback(isChecked);
        menu.createCheckButton(label, callback, isChecked);
    }
    void ParseList(
        Windows::MenuItem& menu,
        JSONObjectView json,
        std::stack<String>& flagNamePath,
        s3d::HashTable<String, bool>& flags
    ) {
        for (auto&& [name, obj] : json) {
            if (flagNamePath.empty()) {
                flagNamePath.push(name);
            } else {
                flagNamePath.push(flagNamePath.top() + U"/" + name);
            }

            auto kind = obj[U"kind"].getOr<String>(U"checkButton");
            if (kind == U"checkButton") {
                auto label = obj[U"label"].getOr<String>(name);
                ParseCheckButton(menu, label, obj, flagNamePath, flags);
            } else if (kind == U"radioButton") {

            } else if (kind == U"popup") {
                auto label = obj[U"label"].getOr<String>(name);
                auto nextMenu = menu.createItem(label);
                ParseList(nextMenu, obj[U"list"].objectView(), flagNamePath, flags);
            }
            flagNamePath.pop();
        }
    }
}
namespace abyss::Debug
{
    class Menu::Impl
    {
        inline static const String MenuPath = Path::DebugPath + U"menu.json";
    public:
        Impl()
        {
        }

        void init()
        {
            auto& mainMenu = Windows::WindowMenu::Main();
            m_debugRoot = mainMenu.createItem(U"デバッグ(&D)");

            JSONReader json(MenuPath);
            std::stack<String> flagNamePath;

            // パース
            ::ParseList(m_debugRoot, json.objectView(), flagNamePath, m_debugFlag);

            {
                auto menu = m_debugRoot.createItem(U"FPS");
                auto list = menu.createRadioButton({U"FPS：可変", U"FPS: 10", U"FPS: 30", U"FPS: 60", U"FPS: 120"}, [](size_t index) {
                    switch (index) {
                    case 0:
                        Graphics::SetTargetFrameRateHz(s3d::none);
                        break;
                    case 1:
                        Graphics::SetTargetFrameRateHz(10);
                        break;
                    case 2:
                        Graphics::SetTargetFrameRateHz(30);
                        break;
                    case 3:
                        Graphics::SetTargetFrameRateHz(60);
                        break;
                    case 4:
                        Graphics::SetTargetFrameRateHz(120);
                        break;
                    default:
                        break;
                    }
                }, 0);
            }
            mainMenu.show(true);
        }
        bool isDebug(const String& label)
        {
            return m_debugFlag[label];
        }
        Windows::MenuItem debugRoot()
        {
            return m_debugRoot;
        }
    private:
        s3d::HashTable<String, bool> m_debugFlag;
        Windows::MenuItem m_debugRoot;
    };
    Menu::Menu():
        m_pImpl(std::make_unique<Impl>())
    {}
    void Menu::Init()
    {
        return Instance()->m_pImpl->init();
    }
    bool Menu::IsDebug(const String& label)
    {
        return Instance()->m_pImpl->isDebug(label);
    }
    Windows::MenuItem Menu::DebugRoot()
    {
        return Instance()->m_pImpl->debugRoot();
    }
}
#endif

