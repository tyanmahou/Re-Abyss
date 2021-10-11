#include "UserSelector.hpp"
#include <abyss/commons/Constants.hpp>
#include <abyss/modules/UI/base/UIObj.hpp>
#include <abyss/commons/InputManager/InputManager.hpp>

namespace abyss::UI::SaveSelect::Main
{
    UserSelector::UserSelector(UIObj* pUi):
        m_pUi(pUi)
    {}
    void UserSelector::onStart()
    {
        m_users = m_pUi->find<Users>();
    }
    s3d::int32 UserSelector::onUpdate()
    {
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
        return m_selectId;
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
}
