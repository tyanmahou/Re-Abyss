#include "UserSelector.hpp"
#include <abyss/commons/Constants.hpp>
#include <abyss/commons/InputManager/InputManager.hpp>

#include <abyss/modules/UI/base/UIObj.hpp>
#include <abyss/modules/Cycle/CycleMaster.hpp>
#include <abyss/components/Cycle/SaveSelect/Master.hpp>

#include <abyss/components/UI/SaveSelect/UserInfo/ViewCtrl.hpp>
#include <abyss/components/UI/SaveSelect/UserInfo/KiraKiraCtrl.hpp>

#include <abyss/components/UI/utils/DialogUtil.hpp>
#include <abyss/components/UI/SaveSelect/CreateUserConfirm/Dialog.hpp>
#include <abyss/components/UI/SaveSelect/EraseUserConfirm/Dialog.hpp>

namespace abyss::UI::SaveSelect::Main
{
    UserSelector::UserSelector(UIObj* pUi) :
        m_pUi(pUi)
    {
        m_state.reset(std::bind(&UserSelector::stateSelect, this));
    }
    void UserSelector::setup(Executer executer)
    {
        executer.on<IUpdate>().addAfter<UserInfo::KiraKiraCtrl>();
    }
    void UserSelector::onStart()
    {
        m_mode = m_pUi->find<ModeCtrl>();
        m_users = m_pUi->find<Users>();
    }
    void UserSelector::onUpdate()
    {
        m_state.moveNext();
    }
    bool UserSelector::isValidUser() const
    {
        return !this->isDeleteSelect() && m_users->isContains(m_selectId);
    }
    bool UserSelector::isDeleteSelect() const
    {
        return m_selectId == -1;
    }
    s3d::Optional<User::UserModel> UserSelector::getSelectUser() const
    {
        if (this->isDeleteSelect()) {
            return s3d::none;
        }
        return m_users->getUser(m_selectId);
    }
    Coro::Task<> UserSelector::stateSelect()
    {
        // 変わっていたら時間リセット
        auto userInfoView = m_pUi->find<UserInfo::ViewCtrl>();
        auto kiraKira = m_pUi->find<UserInfo::KiraKiraCtrl>();

        while (true) {
            auto prevSelectId = m_selectId;
            // 選択
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

            if (m_selectId != prevSelectId) {
                // 変わっていたら時間リセット
                userInfoView->resetTime();
                kiraKira->releaseOneShot();
            }

            // 決定入力
            if (InputManager::A.down()) {
                if (isDeleteSelect()) {
                    // モード切替
                    if (m_mode->is(Mode::GameStart)) {
                        m_mode->set(Mode::Delete);
                    } else {
                        m_mode->set(Mode::GameStart);
                    }
                } else {
                    // データ選択
                    if (m_mode->is(Mode::GameStart)) {
                        if (!m_users->isContains(m_selectId)) {
                            m_state.reset(std::bind(&UserSelector::stateCreateUserConfirm, this));
                            co_return;
                        } else {
                            m_users->login(m_selectId);
                            // 選択
                            m_pUi->getModule<CycleMaster>()
                                ->find<Cycle::SaveSelect::Master>()
                                ->loadGame();
                            co_return;
                        }
                    } else {
                        // 削除確認
                        if (m_users->isContains(m_selectId)) {
                            m_state.reset(std::bind(&UserSelector::stateEraseUserConfirm, this));
                            co_return;
                        }
                    }
                }
            } else if (InputManager::B.down()) {
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
            co_yield{};
        }
        co_return;
    }
    Coro::Task<> UserSelector::stateCreateUserConfirm()
    {
        // コンパイラがぶっこわれとるのでco_yieldで受け取れない
        //auto result = co_yield DialogUtil::Wait<CreateUserConfirm::Dialog>(m_pUi);

        auto dialogTask = DialogUtil::Wait<CreateUserConfirm::Dialog>(m_pUi);
        while (!dialogTask.isDone()) {
            dialogTask.moveNext();
            co_yield{};
        }
        const auto& result = dialogTask.get();
        if (!result.isBack) {
            // ユーザー生成
            m_users->create(m_selectId, result.playMode);
            m_pUi->getModule<CycleMaster>()
                ->find<Cycle::SaveSelect::Master>()
                ->newGame();
            co_return;
        }

        m_state.reset(std::bind(&UserSelector::stateSelect, this));
        co_return;
    }
    Coro::Task<> UserSelector::stateEraseUserConfirm()
    {
        // コンパイラがぶっこわれとるのでco_yieldで受け取れない
        //auto [yes] = co_yield DialogUtil::Wait<EraseUserConfirm::Dialog>(m_pUi);

        auto dialogTask = DialogUtil::Wait<EraseUserConfirm::Dialog>(m_pUi);
        while (!dialogTask.isDone()) {
            dialogTask.moveNext();
            co_yield{};
        }
        bool yes = dialogTask.get().yes;
        // ユーザー削除
        if (yes) {
            m_users->erase(m_selectId);
        }
        m_state.reset(std::bind(&UserSelector::stateSelect, this));
        co_return;
    }
}
