#if ABYSS_DEBUG
#include <abyss/debugs/Menu/Menu.hpp>
#include <abyss/commons/Path.hpp>
#include <Siv3D.hpp>

#include <abyss/debugs/Log/Log.hpp>
#include <abyss/utils/FPS/FrameRateHz.hpp>
#include <abyss/utils/Reflection/Reflection.hpp>

namespace abyss::Debug
{
    class Menu::Impl
    {
        inline static const String MenuPath = Path::DebugPath + U"menu.xml";
    public:
        Impl()
        {}

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
        size_t debugSelect(const s3d::String& label)
        {
            return m_debugSelect[label];
        }
        void bindScene(AppScene* pScene)
        {
            m_pScene = pScene;
        }
    private:

#pragma region Button コールバック
        void parseButton(
            Windows::MenuItem& menu,
            const XMLElement& xml
        )
        {
            using ButtonCallback = void (Impl::*)();

            auto customCallback = xml.attribute(U"callback").map([this](const String& funcName) {
                return Reflect<Impl>::find<ButtonCallback>(funcName);
            }).value_or(nullptr);

            auto callback = [this, customCallback]() {
                if (customCallback) {
                    (this->*customCallback)();
                }
            };
            menu.setButton(callback);
        }
        [[REFLECTION(execClearLog)]]
        void execClearLog()
        {
            Debug::LogUpdater::Clear();
        }
#pragma endregion

#pragma region CheckButton パース
        void parseCheckButton(
            Windows::MenuItem& menu,
            const XMLElement& xml,
            std::stack<String>& flagNamePath
        )
        {
            using CheckButtonCallback = void (Impl::*)(bool);

            bool isChecked = xml.attribute(U"isChecked").map(Parse<bool>).value_or(false);

            auto customCallback = xml.attribute(U"callback").map([this](const String& funcName) {
                return Reflect<Impl>::find<CheckButtonCallback>(funcName);
            }).value_or(nullptr);

            auto callback = [this, key = flagNamePath.top(), customCallback](bool isChecked) {
                m_debugFlag[key] = isChecked;
                if (customCallback) {
                    (this->*customCallback)(isChecked);
                }
            };
            callback(isChecked);
            menu.setCheckButton(callback, isChecked);
        }

        [[REFLECTION(execSoundMute)]]
        void execSoundMute(bool isChecked)
        {
            // マスターボリューム設定
            if (isChecked) {
                GlobalAudio::SetVolume(0.0);
            } else {
                GlobalAudio::SetVolume(1.0);
            }
        }
#pragma endregion

#pragma region RadioButton パース
        void parseRadioButton(
            Windows::MenuItem& menu,
            const XMLElement& xml,
            std::stack<String>& flagNamePath
        )
        {
            using RadioButtonCallback = void (Impl::*)(size_t, const s3d::Optional<String>&);

            size_t selectIndex = xml.attribute(U"select").map(Parse<size_t>).value_or(0);

            auto customCallback = xml.attribute(U"callback").map([this](const String& funcName) {
                return Reflect<Impl>::find<RadioButtonCallback>(funcName);
            }).value_or(nullptr);

            s3d::Array<s3d::String> items;
            s3d::Array<s3d::Optional<String>> values;
            for (auto item = xml.firstChild(); item; item = item.nextSibling()) {
                items.push_back(item.attribute(U"label").value_or(item.name()));
                values.push_back(item.attribute(U"value"));
            }

            auto callback = [this, key = flagNamePath.top(), values = std::move(values), customCallback](size_t selectIndex) {
                m_debugSelect[key] = selectIndex;
                if (customCallback) {
                    (this->*customCallback)(selectIndex, values[selectIndex]);
                }
            };
            callback(selectIndex);
            menu.createRadioButton(std::move(items), callback, selectIndex);
        }

        [[REFLECTION(execFPS)]]
        void execFPS([[maybe_unused]]size_t index, const s3d::Optional<String>& value)
        {
            FrameRateHz::Set(value.map(Parse<double>));
        }
#pragma endregion

#pragma region Custom パース
        void parseCustom(
            Windows::MenuItem& menu,
            const String& funcName
        )
        {
            using CustomFunc = void (Impl::*)(Windows::MenuItem&);
            if (auto func = Reflect<Impl>::find<CustomFunc>(funcName)) {
                (this->*func)(menu);
            }
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
        [[REFLECTION(buildSceneMenu)]]
        void buildSceneMenu(Windows::MenuItem& menu)
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
#pragma endregion

#pragma region Popup パース
        template<class MenuType>
        void parseList(
            MenuType& menu,
            const XMLElement& xml,
            std::stack<String>& flagNamePath
        )
        {
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
                if (e.attribute(U"isChecked")) {
                    // check
                    auto nextMenu = menu.createItem(label);
                    parseCheckButton(nextMenu, e, flagNamePath);
                } else if (e.attribute(U"select")) {
                    // radioButton
                    auto nextMenu = menu.createItem(label);
                    parseRadioButton(nextMenu, e, flagNamePath);
                } else if (e.firstChild()) {
                    // popup
                    auto nextMenu = menu.createItem(label);
                    parseList(nextMenu, e, flagNamePath);
                } else if (auto custom = e.attribute(U"custom")) {
                    // custom
                    auto nextMenu = menu.createItem(label);
                    parseCustom(nextMenu, *custom);
                } else {
                    // button
                    auto nextMenu = menu.createItem(label);
                    parseButton(nextMenu, e);
                }
                flagNamePath.pop();
            }
        }
#pragma endregion

    private:
        s3d::HashTable<String, bool> m_debugFlag;
        s3d::HashTable<String, size_t> m_debugSelect;
        AppScene* m_pScene = nullptr;
    };
    Menu::Menu() :
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
    size_t Menu::DebugSelect(const s3d::String& label)
    {
        return Instance()->m_pImpl->debugSelect(label);
    }
    void Menu::BindScene(AppScene* pScene)
    {
        return Instance()->m_pImpl->bindScene(pScene);
    }
}
#endif

