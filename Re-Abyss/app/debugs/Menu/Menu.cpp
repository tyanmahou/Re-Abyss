#if ABYSS_DEBUG
#include "Menu.hpp"
#include <abyss/commons/Path.hpp>
#include <Siv3D.hpp>

#include <abyss/debugs/Log/Log.hpp>
#include <abyss/utils/FPS/FrameRateHz.hpp>

namespace abyss::Debug
{
    class Menu::Impl
    {
        inline static const String MenuPath = Path::DebugPath + U"menu.xml";
    public:
        Impl()
        {
        }

        void init()
        {
            const FilePathView path = MenuPath;
            const XMLReader xml(path);
            std::stack<String> flagNamePath;

            auto& mainMenu = Windows::WindowMenu::Main();

            if (xml) {
                // パース
                this->parseList(mainMenu, xml, flagNamePath);
            }
            mainMenu.show(true);
        }
        bool isDebug(const String& label)
        {
            return m_debugFlag[label];
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
                    FrameRateHz::Set(s3d::none);
                    break;
                case 1:
                    FrameRateHz::Set(10.0);
                    break;
                case 2:
                    FrameRateHz::Set(30.0);
                    break;
                case 3:
                    FrameRateHz::Set(60.0);
                    break;
                case 4:
                    FrameRateHz::Set(120.0);
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
                    m_pScene->changeScene(key, 1000, CrossFade::No);
                }
            });
        }
        void createMainSceneChangeButtons(Windows::MenuItem& m, const s3d::FilePath& basePath)
        {
            for (auto&& path : s3d::FileSystem::DirectoryContents(basePath, Recursive::No)) {
                if (s3d::FileSystem::IsDirectory(path)) {
                    if (s3d::FileSystem::DirectoryContents(path).any([](const s3d::FilePath& p) {
                        return s3d::FileSystem::Extension(p) == U"tmx";
                    })) {
                        auto child = m.createItem(s3d::FileSystem::BaseName(path));
                        createMainSceneChangeButtons(child, path);
                    }
                    continue;
                }
                if (s3d::FileSystem::Extension(path) != U"tmx") {
                    continue;
                }
                MainSceneContext context{
                    .mapPath = s3d::FileSystem::RelativePath(path)
                };
                auto name = s3d::FileSystem::RelativePath(path, basePath);
                createSceneChangeButton(m, SceneName::Main, name, [context](GameData* data) {
                    data->context = context;
                });
            }
        }
        void execScene(Windows::MenuItem& menu)
        {
            createSceneChangeButton(menu, SceneName::Splash);
            createSceneChangeButton(menu, SceneName::Title);
            createSceneChangeButton(menu, SceneName::SaveSelect);
            // マップロード
            {
                auto child = menu.createItem(SceneName::Main);
                createMainSceneChangeButtons(child, Path::MapPath);
                child.createSeperator();
                createMainSceneChangeButtons(child, Path::TestMapPath);
            }
        }
        void execSoundMute(Windows::MenuItem& menu)
        {
            menu.setCheckButton([]([[maybe_unused]] bool isChecked) {
                // マスターボリューム設定
                // TODO ミュート
            });
        }
        void parseCustom(
            Windows::MenuItem& menu,
            const String& funcName
        ) {
            static const std::unordered_map<s3d::String, decltype(&Impl::execFPS)> funcMap
            {
                { U"execFPS", &Impl::execFPS},
                { U"execScene", &Impl::execScene },
                { U"execSoundMute", &Impl::execSoundMute },
            };
            if (funcMap.find(funcName) == funcMap.end()) {
                return;
            }
            (this->*funcMap.at(funcName))(menu);
        }
        void parseCheckButton(
            Windows::MenuItem& menu,
            const XMLElement& xml,
            std::stack<String>& flagNamePath
        ) {
            bool isChecked = xml.attribute(U"isChecked").map(Parse<bool>).value_or(U"false");
            auto callback = [this, key = flagNamePath.top()](bool isChecked) {
                m_debugFlag[key] = isChecked;
            };
            callback(isChecked);
            menu.setCheckButton(callback, isChecked);
        }
        template<class MenuType>
        void parseList(
            MenuType& menu,
            const XMLElement& xml,
            std::stack<String>& flagNamePath
        ) {
            for (auto e = xml.firstChild(); e; e = e.nextSibling()) {
                auto name = e.name();
                if (name == U"hr") {
                    if constexpr (!std::is_same_v<MenuType, Windows::WindowMenu>) {
                        menu.createSeperator();
                    }
                    continue;
                }
                if (flagNamePath.empty()) {
                    flagNamePath.push(name);
                } else {
                    flagNamePath.push(flagNamePath.top() + U"/" + name);
                }
                auto label = e.attribute(U"label").value_or(name);
                if (e.attribute(U"select")) {
                    // radioButton
                } else if (e.firstChild()) {
                    // popup
                    auto nextMenu = menu.createItem(label);
                    parseList(nextMenu, e, flagNamePath);
                } else if (auto custom = e.attribute(U"custom")) {
                    // custom
                    auto nextMenu = menu.createItem(label);
                    parseCustom(nextMenu, *custom);
                } else {
                    // check
                    auto nextMenu = menu.createItem(label);
                    parseCheckButton(nextMenu, e, flagNamePath);
                }
                flagNamePath.pop();
            }
        }
    private:
        s3d::HashTable<String, bool> m_debugFlag;
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
}
#endif

