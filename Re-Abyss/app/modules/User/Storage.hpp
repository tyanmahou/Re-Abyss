#pragma once
#include <abyss/modules/User/DataStore.hpp>
#include <abyss/modules/User/RuntimeData.hpp>
#include <Emaject.hpp>

namespace abyss::User
{
    /// <summary>
    /// ストレージ
    /// </summary>
    class Storage
    {
    public:
        s3d::HashTable<s3d::int32, User::UserModel> getUsers() const;

        bool eraseUser(s3d::int32 userId) const;
        UserModel createUser(s3d::int32 userId, UserPlayMode playMode) const;        
        UserModel login(const UserModel& user) const;
    private:
        [[INJECT(m_dataStore)]]
        std::shared_ptr<DataStore> m_dataStore;
    };
}
