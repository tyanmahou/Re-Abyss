#pragma once
#include <abyss/modules/User/DataStore.hpp>
#include <abyss/modules/User/RuntimeData.hpp>

namespace abyss::User
{
    /// <summary>
    /// ストレージ
    /// </summary>
    class Storage
    {
    public:
        Storage(std::shared_ptr<DataStore> dataStore);
        s3d::HashTable<s3d::int32, User::UserModel> getUsers() const;

        bool eraseUser(s3d::int32 userId) const;
        UserModel createUser(s3d::int32 userId, UserPlayMode playMode) const;        
        UserModel login(const UserModel& user) const;
    private:
        std::shared_ptr<DataStore> m_dataStore;
    };
}
