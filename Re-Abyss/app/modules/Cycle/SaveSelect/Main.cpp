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

    Main::Main(IMainObserver* observer):
        m_observer(observer),
        m_bg(std::make_unique<BackGround::BackGroundVM>()),
        m_selectFrame(std::make_unique<SelectFrame::SelectFrameVM>()),
        m_userInfo(std::make_unique<UserInfo::UserInfoView>()),
        m_users(Storage::Get<User::IUserService>()->getUsers())
    {}

    Main::~Main()
    {}
    void Main::update()
    {
        // selectId更新
        if (m_phase == Phase::Select) {
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
        } else {
            if (m_mode == Mode::GameStart) {
                if (InputManager::Up.down()) {
                    m_playMode = UserPlayMode::Normal;
                }
                if (InputManager::Down.down()) {
                    m_playMode = UserPlayMode::Hard;
                }
            } else {
                if (InputManager::Up.down()) {
                    m_yesNo = true;
                }
                if (InputManager::Down.down()) {
                    m_yesNo = false;
                }
            }
        }

        if (InputManager::A.down()) {
            if (m_phase == Phase::Select) {
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
                            m_phase = Phase::Confirm;
                        } else {
                            m_users[m_selectId] = Resource::SaveUtil::Login(m_users[m_selectId]);
                            // 選択
                            m_observer->onLoadGame();
                            return;
                        }
                    } else {
                        // 削除確認
                        if (m_users.contains(m_selectId)) {
                            m_phase = Phase::Confirm;
                            m_yesNo = false;
                        }
                    }
                }
            } else {
                if (m_mode == Mode::GameStart) {
                    // ユーザー生成
                    m_users[m_selectId] = Resource::SaveUtil::CreateUser(m_selectId);
                    m_observer->onNewGame();
                } else {
                    if (m_yesNo) {
                        Resource::SaveUtil::EraseUser(m_selectId);
                        m_users.erase(m_selectId);
                    } else {
                        m_phase = Phase::Select;
                    }
                }
            }
        }

        if (InputManager::B.down()) {
            if (m_phase == Phase::Confirm) {
                m_phase = Phase::Select;
            } else {
                if (m_mode == Mode::Delete) {
                    // 削除キャンセル
                    m_mode = Mode::GameStart;
                } else if (m_mode == Mode::GameStart) {
                    // 戻る
                    m_observer->onBack();
                }
            }
        }
    }

    void Main::draw() const
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

        if (m_phase == Phase::Confirm) {
            if (m_mode == Mode::GameStart) {
                FontAsset(FontName::UserInfo)(U"難易度をえらんでください").drawAt(480, 320);
            } else {
                FontAsset(FontName::UserInfo)(U"本当に削除しますか？").drawAt(480, 320);
            }
        }
    }

    void Main::finally()
    {

    }
}