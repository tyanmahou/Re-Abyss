#include "UserSelect.hpp"
#include "CreateUserConfirm.hpp"
#include "EraseUserConfirm.hpp"

#include <abyss/commons/Constants.hpp>
#include <abyss/commons/FontName.hpp>
#include <abyss/commons/InputManager/InputManager.hpp>
#include <abyss/commons/Resource/UserData/Storage/Storage.hpp>
#include <abyss/commons/Resource/SaveUtil.hpp>
#include <abyss/services/User/base/IUserService.hpp>

#include <abyss/modules/UI/base/UIObj.hpp>
#include <abyss/modules/Cycle/CycleMaster.hpp>
#include <abyss/components/Cycle/SaveSelect/Master.hpp>
#include <abyss/views/util/Pivot/PivotUtil.hpp>
#include <abyss/params/UI/SaveSelect/Param.hpp>

namespace abyss::UI::SaveSelect::Panel
{
    using Resource::UserData::Storage;

    UserSelect::UserSelect(UIObj* pUi) :
        m_pUi(pUi),
        m_bg(std::make_unique<BackGround::BackGroundVM>()),
        m_selectFrame(std::make_unique<SelectFrame::SelectFrameVM>()),
        m_userInfo(std::make_unique<UserInfo::UserInfoView>()),
        m_users(Storage::Get<User::IUserService>()->getUsers())
    {}
    void UserSelect::start()
    {}
    bool UserSelect::update()

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
                            m_pUi->getModule<CycleMaster>()
                                ->find<Cycle::SaveSelect::Master>()
                                ->newGame();
                        });
                    } else {
                        m_users[m_selectId] = Resource::SaveUtil::Login(m_users[m_selectId]);
                        // 選択
                        m_pUi->getModule<CycleMaster>()
                            ->find<Cycle::SaveSelect::Master>()
                            ->loadGame();
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
                m_pUi->getModule<CycleMaster>()
                    ->find<Cycle::SaveSelect::Master>()
                    ->back();
            }
        }
        return true;
    }
    void UserSelect::draw() const
    {
        m_bg->draw(m_mode == Mode::Delete ? Palette::Red : Color(93, 93, 255));
        m_selectFrame
            ->setSelectUserId(m_selectId)
            .draw();

        if (m_mode == Mode::GameStart) {
            FontAsset(FontName::SceneName)(U"- データ選択 -").drawAt(PivotUtil::FromTc(0, 50), Color(0, 255, 255));
        } else {
            FontAsset(FontName::SceneName)(U"- データ削除 -").drawAt(PivotUtil::FromTc(0, 50), Color(255, 0, 0));
        }

        auto msgPos = PivotUtil::FromCc(Param::SelectFrame::BasePos) + Param::Confirm::BoardPos;
        if (m_selectId != -1) {
            if (m_users.contains(m_selectId)) {
                m_userInfo->draw(m_users.at(m_selectId));
            } else {
                FontAsset(FontName::SceneName)(U"はじめから").drawAt(msgPos);
            }
        } else {
            FontAsset(FontName::SceneName)(U"データ削除").drawAt(msgPos);
        }
    }
}
