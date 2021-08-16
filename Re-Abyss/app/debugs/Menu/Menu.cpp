#if ABYSS_DEBUG
#include "Menu.hpp"
#include <abyss/commons/Path.hpp>
#include <Siv3D.hpp>

#include <abyss/debugs/Log/Log.hpp>
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
            this->parseList(m_debugRoot, json.objectView(), flagNamePath);

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
        void bindScene(AppScene* pScene)
        {
            m_pScene = pScene;
        }
    private:
        void execFPS(Windows::MenuItem& menu)
        {
            menu.createRadioButton({ U"FPS：可変", U"FPS: 10", U"FPS: 30", U"FPS: 60", U"FPS: 120" }, [](size_t index) {
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

        void createSceneChangeButton(Windows::MenuItem& m, const s3d::String& key, std::function<void(GameData*)> callback = nullptr)
        {
            this->createSceneChangeButton(m, key, key, callback);
        }

        void createSceneChangeButton(Windows::MenuItem& m, const s3d::String& key, const s3d::String& label, std::function<void(GameData*)> callback = nullptr)
        {
            m.createButton(label, [this, key, callback] {
                if (m_pScene) {
                    if (callback) {
                        callback(m_pScene->get().get());
                    }
                    m_pScene->changeScene(key, 1000, false);
                }
            });
        }
        void execScene(Windows::MenuItem& menu)
        {
            createSceneChangeButton(menu, SceneName::Splash);
            createSceneChangeButton(menu, SceneName::Title);
            createSceneChangeButton(menu, SceneName::SaveSelect);
            // マップロード
            {
                auto child = menu.createItem(SceneName::Main);
                auto chaneMap = [&](const s3d::FilePath& basePath) {
                    for (auto&& path : s3d::FileSystem::DirectoryContents(basePath)) {
                        if (s3d::FileSystem::Extension(path) != U"tmx") {
                            continue;
                        }
                        MainSceneContext context{
                            .mapPath = s3d::FileSystem::RelativePath(path)
                        };
                        auto name = s3d::FileSystem::RelativePath(path, basePath);
                        createSceneChangeButton(child, SceneName::Main, name, [context](GameData* data) {
                            data->context = context;
                        });
                    }
                };
                chaneMap(Path::MapPath);
                child.createSeperator();
                chaneMap(Path::TestMapPath);
            }
        }
        void parseCustom(
            Windows::MenuItem& menu,
            const String& funcName
        ) {
            static const std::unordered_map<s3d::String, decltype(&Impl::execFPS)> funcMap
            {
                { U"execFPS", &Impl::execFPS},
                { U"execScene", &Impl::execScene },
            };
            if (funcMap.find(funcName) == funcMap.end()) {
                return;
            }
            (this->*funcMap.at(funcName))(menu);
        }
        void parseCheckButton(
            Windows::MenuItem& menu,
            const String& label,
            JSONValue& json,
            std::stack<String>& flagNamePath
        ) {
            bool isChecked = json[U"isChecked"].getOr<bool>(false);
            auto callback = [this, key = flagNamePath.top()](bool isChecked) {
                m_debugFlag[key] = isChecked;
            };
            callback(isChecked);
            menu.createCheckButton(label, callback, isChecked);
        }
        void parseList(
            Windows::MenuItem& menu,
            JSONObjectView json,
            std::stack<String>& flagNamePath
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
                    parseCheckButton(menu, label, obj, flagNamePath);
                } else if (kind == U"radioButton") {

                } else if (kind == U"popup") {
                    auto label = obj[U"label"].getOr<String>(name);
                    auto nextMenu = menu.createItem(label);
                    parseList(nextMenu, obj[U"list"].objectView(), flagNamePath);
                } else if (kind == U"custom") {
                    auto label = obj[U"label"].getOr<String>(name);
                    auto nextMenu = menu.createItem(label);
                    parseCustom(nextMenu, obj[U"func"].getOr<String>(U""));
                }
                flagNamePath.pop();
            }
        }
    private:
        s3d::HashTable<String, bool> m_debugFlag;
        Windows::MenuItem m_debugRoot;
        AppScene* m_pScene = nullptr;
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
    void Menu::BindScene(AppScene* pScene)
    {
        return Instance()->m_pImpl->bindScene(pScene);
    }
    Windows::MenuItem Menu::DebugRoot()
    {
        return Instance()->m_pImpl->debugRoot();
    }
}
#endif

