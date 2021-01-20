#include "Main.hpp"

#include <abyss/commons/Constants.hpp>
#include <abyss/commons/FontName.hpp>
#include <abyss/commons/InputManager/InputManager.hpp>
#include <abyss/commons/Resource/UserData/Storage/Storage.hpp>
#include <abyss/commons/Resource/SaveUtil.hpp>
#include <abyss/services/User/base/IUserService.hpp>

#include <abyss/views/Cycle/SaveSelect/BackGround/BackGroundVM.hpp>
#include <abyss/views/Cycle/SaveSelect/SelectFrame/SelectFrameVM.hpp>
#include <abyss/views/Cycle/SaveSelect/UserInfo/UserInfoView.hpp>

#include <Siv3D.hpp>

namespace abyss::Cycle::SaveSelect
{
    using Resource::UserData::Storage;


    class EraseUserConfirm : public IHierarchy
    {
        bool m_yes = false;
        std::function<void()> m_callback;
    public:
        EraseUserConfirm(std::function<void()> callback) :
            m_callback(callback)
        {}

        bool update() override
        {
            if (InputManager::Up.down()) {
                m_yes = true;
            }
            if (InputManager::Down.down()) {
                m_yes = false;
            }
            if (InputManager::A.down()) {
                if (m_yes) {
                    m_callback();
                }
                return false;
            }
            return !InputManager::B.down();
        }

        void draw() const override
        {
            FontAsset(FontName::UserInfo)(U"本当に削除しますか？").drawAt(480, 320);
        }
    };
    class CreateUserConfirm : public IHierarchy
    {
        UserPlayMode m_playMode = UserPlayMode::Normal;
        std::function<void(UserPlayMode)> m_callback;

        bool m_isDone = false;
    public:
        CreateUserConfirm(std::function<void(UserPlayMode)> callback):
            m_callback(callback)
        {}
        bool update() override
        {
            if (InputManager::Up.down()) {
                m_playMode = UserPlayMode::Normal;
            }
            if (InputManager::Down.down()) {
                m_playMode = UserPlayMode::Hard;
            }
            if (InputManager::A.down()) {
                m_callback(m_playMode);
                m_isDone = true;
            }
            return m_isDone || !InputManager::B.down();
        }

        void draw() const override
        {
            FontAsset(FontName::UserInfo)(U"難易度をえらんでください").drawAt(480, 320);
        }
    };
    class UserSelect : public IHierarchy
    {
        enum class Mode
        {
            GameStart,
            Delete,
        };
        IMainObserver* m_observer;

        s3d::int32 m_selectId = 0;
        Mode m_mode = Mode::GameStart;
        s3d::HashTable<s3d::int32, User::UserModel> m_users;

        std::unique_ptr<BackGround::BackGroundVM> m_bg;
        std::unique_ptr<SelectFrame::SelectFrameVM> m_selectFrame;
        std::unique_ptr<UserInfo::UserInfoView> m_userInfo;
    public:
        UserSelect(IMainObserver* observer):
            m_observer(observer),
            m_bg(std::make_unique<BackGround::BackGroundVM>()),
            m_selectFrame(std::make_unique<SelectFrame::SelectFrameVM>()),
            m_userInfo(std::make_unique<UserInfo::UserInfoView>()),
            m_users(Storage::Get<User::IUserService>()->getUsers())
        {}
        void start() override
        {

        }

        bool update() override
        {
            // selectId更新
            if (InputManager::Left.down()) {
                --m_selectId;
            }
            if (InputManager::Right.down()) {
                ++m_selectId;
            }
            if (m_selectId < -1) {
                m_selectId = Constants::UserNum - 1;
            } else if (m_selectId >= Constants::UserNum) {
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
                            this->push<CreateUserConfirm>([this](UserPlayMode playMode) {
                                // ユーザー生成
                                m_users[m_selectId] = Resource::SaveUtil::CreateUser(m_selectId, playMode);
                                m_observer->onNewGame();
                            });
                        } else {
                            m_users[m_selectId] = Resource::SaveUtil::Login(m_users[m_selectId]);
                            // 選択
                            m_observer->onLoadGame();
                            return true;
                        }
                    } else {
                        // 削除確認
                        if (m_users.contains(m_selectId)) {
                            this->push<EraseUserConfirm>([this]() {
                                Resource::SaveUtil::EraseUser(m_selectId);
                                m_users.erase(m_selectId);
                            });
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
                    m_observer->onBack();
                }
            }
            return true;
        }

        void draw() const override
        {
            m_bg->draw(m_mode == Mode::Delete ? Palette::Red : Color(93, 93, 255));
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
                    m_userInfo->draw(m_users.at(m_selectId));
                } else {
                    FontAsset(FontName::SceneName)(U"はじめから").drawAt(480, 320);
                }
            } else {
                FontAsset(FontName::SceneName)(U"データ削除").drawAt(480, 320);
            }
        }
    };
    Main::Main(IMainObserver* observer)
    {
        m_hierarcy.push<UserSelect>(observer);
        m_hierarcy.hierarchyUpdate();
    }

    Main::~Main()
    {}
    void Main::update()
    {
        m_hierarcy.update();
    }

    void Main::draw() const
    {
        m_hierarcy.draw();
    }

    void Main::finally()
    {

    }
}