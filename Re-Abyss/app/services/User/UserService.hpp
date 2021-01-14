#pragma once
#include <abyss/services/User/base/IUserService.hpp>
#include <Emaject.hpp>
namespace abyss::User
{
    class IUserDataStore;

    class UserService : public IUserService
    {
    public:
        s3d::HashTable<s3d::int32, UserModel> getUsers() const override;
        UserModel create(s3d::int32 userId, UserPlayMode playMode) const override;
        UserModel login(const UserModel& user) const override;
    private:
        [[INJECT(m_users)]]
        std::shared_ptr<IUserDataStore> m_users;
    };

    struct UserServiceInstaller : emaject::IInstaller
    {
        void onBinding(emaject::Container* container) const override;
    };
}