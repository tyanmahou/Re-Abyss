#include "UserSelect.hpp"
//#include "CreateUserConfirm.hpp"
//#include "EraseUserConfirm.hpp"

#include <abyss/commons/InputManager/InputManager.hpp>

#include <abyss/modules/UI/base/UIObj.hpp>
#include <abyss/modules/Cycle/CycleMaster.hpp>
#include <abyss/components/Cycle/SaveSelect/Master.hpp>

#include <abyss/components/UI/SaveSelect/UserInfo/ViewCtrl.hpp>
#include <abyss/components/UI/SaveSelect/UserInfo/KiraKiraCtrl.hpp>

namespace abyss::UI::SaveSelect::Main
{
    UserSelect::UserSelect(UIObj* pUi) :
        m_pUi(pUi)
    {}
    void UserSelect::start()
    {
        m_mode = m_pUi->find<ModeCtrl>();
        m_users = m_pUi->find<Users>();
        m_selector = m_pUi->find<UserSelector>();
    }
    bool UserSelect::update()
    {
        // selectId更新
        auto prevSelectId = m_selector->getSelectId();
        if (auto selectId = m_selector->onUpdate(); selectId != prevSelectId) {
            // 変わっていたら時間リセット
            m_pUi->find<UserInfo::ViewCtrl>()->resetTime();
            m_pUi->find<UserInfo::KiraKiraCtrl>()->releaseOneShot();
        }

        if (InputManager::A.down()) {
            //if (m_users->isDeleteSelect()) {
            //    // モード切替
            //    if (m_mode->is(Mode::GameStart)) {
            //        m_mode->set(Mode::Delete);
            //    } else {
            //        m_mode->set(Mode::GameStart);
            //    }
            //} else {
            //    // データ選択
            //    if (m_mode->is(Mode::GameStart)) {
            //        if (!m_users.contains(m_selectId)) {
            //            this->push<CreateUserConfirm>([this](UserPlayMode playMode) {
            //                // ユーザー生成
            //                m_users[m_selectId] = Resource::SaveUtil::CreateUser(m_selectId, playMode);
            //                m_pUi->getModule<CycleMaster>()
            //                    ->find<Cycle::SaveSelect::Master>()
            //                    ->newGame();
            //            });
            //            return true;
            //        } else {
            //            m_users[m_selectId] = Resource::SaveUtil::Login(m_users[m_selectId]);
            //            // 選択
            //            m_pUi->getModule<CycleMaster>()
            //                ->find<Cycle::SaveSelect::Master>()
            //                ->loadGame();
            //            return true;
            //        }
            //    } else {
            //        // 削除確認
            //        if (m_users.contains(m_selectId)) {
            //            this->push<EraseUserConfirm>([this]() {
            //                Resource::SaveUtil::EraseUser(m_selectId);
            //                m_users.erase(m_selectId);
            //            });
            //            return true;
            //        }
            //    }
            //}
        }

        if (InputManager::B.down()) {
            if (m_mode->is(Mode::Delete)) {
                // 削除キャンセル
                m_mode->set(Mode::GameStart);
            } else if (m_mode->is(Mode::GameStart)) {
                // 戻る
                m_pUi->getModule<CycleMaster>()
                    ->find<Cycle::SaveSelect::Master>()
                    ->back();
            }
        }
        return true;
    }
}
