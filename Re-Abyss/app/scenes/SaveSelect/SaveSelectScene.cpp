#include "SaveSelectScene.hpp"
#include <Siv3D.hpp>
#include <abyss/commons/Constants.hpp>
#include <abyss/commons/FontName.hpp>
#include <abyss/commons/InputManager/InputManager.hpp>

#include <abyss/commons/Resource/Preload/ParamPreloader.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>

#include <abyss/commons/Resource/UserData/Storage/Storage.hpp>
#include <abyss/commons/Resource/SaveUtil.hpp>

#include <abyss/services/User/base/IUserService.hpp>
#include <abyss/models/User/UserModel.hpp>

#include <abyss/views/Cycle/SaveSelect/BackGround/BackGroundVM.hpp>
#include <abyss/views/Cycle/SaveSelect/SelectFrame/SelectFrameVM.hpp>

#include <abyss/debugs/HotReload/HotReload.hpp>

namespace abyss
{
    using Resource::UserData::Storage;
    using namespace Cycle::SaveSelect;

    class SaveSelectScene::Impl
    {
        enum class Mode
        {
            GameStart,
            Delete,
        };
        int32 m_selectId = 0;
        Mode m_mode = Mode::GameStart;


        std::function<void()> m_onLoadGameFunc;
        std::function<void()> m_onNewGameFunc;
        std::function<void()> m_onBackFunc;
        s3d::HashTable<s3d::int32, User::UserModel> m_users;

        Cycle::SaveSelect::BackGround::BackGroundVM m_bg;
        std::unique_ptr<SelectFrame::SelectFrameVM> m_selectFrame;

#if ABYSS_DEBUG
        Debug::HotReload m_reloader;
#endif
    public:
        Impl([[maybe_unused]] const InitData& init):
            m_selectFrame(std::make_unique<SelectFrame::SelectFrameVM>())
        {
#if ABYSS_DEBUG
            m_reloader
                .setMessage(U"SaveSelect")
                .setCallback([this]() {
                    this->reload();
                })
                .setSuperCallback([this] {
                    this->init();
                })
                ;
#endif
            this->init();
        }

        void reload()
        {
            Resource::Assets::Main()->release();
            // リロード時はリソースを直で
            Resource::Assets::Main()->setIsBuilded(false);
            this->init();
        }
        void init()
        {
            Resource::Prelaod::LoadSaveSelectToml(*Resource::Assets::Main());
            Resource::Prelaod::LoadUIToml(*Resource::Assets::Main());
            m_users = Storage::Get<User::IUserService>()->getUsers();
        }
        void update()
        {
#if ABYSS_DEBUG
            m_reloader.detection();
#endif
            // selectId更新
            if (InputManager::Left.down()) {
                --m_selectId;
            }
            if (InputManager::Right.down()) {
                ++m_selectId;
            }
            if (m_selectId < -1) {
                m_selectId = Constants::UserNum - 1;
            } else if(m_selectId >= Constants::UserNum) {
                m_selectId = -1;
            }

            if (InputManager::A.down()) {
                if (m_selectId == -1) {
                    // モード切替
                    if (m_mode == Mode::GameStart) {
                        m_mode = Mode::Delete;
                    } else {
                        m_mode = Mode::GameStart;
                    }
                } else {
                    // データ選択
                    if (m_mode == Mode::GameStart) {
                        if (!m_users.contains(m_selectId)) {
                            m_users[m_selectId] = Resource::SaveUtil::CreateUser(m_selectId);
                        } else {
                            m_users[m_selectId] = Resource::SaveUtil::Login(m_users[m_selectId]);
                        }
                        // 選択
                        m_onLoadGameFunc();
                    } else {
                        // 削除確認
                        if (m_users.contains(m_selectId)) {
                            Resource::SaveUtil::EraseUser(m_selectId);
                            m_users.erase(m_selectId);
                        }
                    }
                }
            }

            if (InputManager::B.down()) {
                if (m_mode == Mode::Delete) {
                    // 削除キャンセル
                    m_mode = Mode::GameStart;
                } else if (m_mode == Mode::GameStart) {
                    // 戻る
                    m_onBackFunc();
                }
            }
        }

        void draw() const
        {
            m_bg.draw(m_mode == Mode::Delete ? Palette::Red : Color(93, 93, 255));
            m_selectFrame
                ->setSelectUserId(m_selectId)
                .draw();



            if (m_mode == Mode::GameStart) {
                FontAsset(FontName::SceneName)(U"- データ選択 -").drawAt(480, 50, Color(0, 255, 255));
            } else {
                FontAsset(FontName::SceneName)(U"- データ削除 -").drawAt(480, 50, Color(255, 0, 0));
            }

            if (m_selectId != -1) {
                if (m_users.contains(m_selectId)) {
                    FontAsset(FontName::SceneName)(U"つづきから").drawAt(480, 270);
                } else {
                    FontAsset(FontName::SceneName)(U"はじめから").drawAt(480, 270);
                }
            }
        }

        void finally()
        {
        }
        void bindLoadGameFunc(const std::function<void()>& callback)
        {
            m_onLoadGameFunc = callback;
        }
        void bindNewGameFunc(const std::function<void()>& callback)
        {
            m_onNewGameFunc = callback;
        }
        void bindBackFunc(const std::function<void()>& callback)
        {
            m_onBackFunc = callback;
        }
    };
    SaveSelectScene::SaveSelectScene(const InitData& init) :
        ISceneBase(init),
        m_pImpl(std::make_unique<Impl>(init))
    {
        m_pImpl->bindLoadGameFunc([this] {
            this->changeScene(SceneName::Main);
        });
        m_pImpl->bindNewGameFunc([this] {
            this->changeScene(SceneName::Main);
        });
        m_pImpl->bindBackFunc([this] {
            this->changeScene(SceneName::Title);
        });
    }

    void SaveSelectScene::update()
    {
        m_pImpl->update();
    }

    void SaveSelectScene::draw() const
    {
        m_pImpl->draw();
    }
    void SaveSelectScene::finally()
    {
        m_pImpl->finally();
    }
}
