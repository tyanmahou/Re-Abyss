#include <abyss/modules/User/Storage.hpp>

namespace abyss::User
{
    Storage::Storage(std::shared_ptr<DataStore> dataStore):
        m_dataStore(dataStore)
    {}
    s3d::HashTable<s3d::int32, User::UserModel> Storage::getUsers() const
    {
        return m_dataStore->get<IUserService>()->getUsers();
    }
    bool Storage::eraseUser(s3d::int32 userId) const
    {
        m_dataStore->get<IUserService>()->erase(userId);
        return true;
    }
    UserModel Storage::createUser(s3d::int32 userId, UserPlayMode playMode) const
    {
        return m_dataStore->get<IUserService>()->create(userId, playMode);
    }
    UserModel Storage::login(const UserModel& user) const
    {
        return m_dataStore->get<IUserService>()->login(user);
    }
}
