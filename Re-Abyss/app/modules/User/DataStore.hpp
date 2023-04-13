#pragma once
#include <memory>
#include <abyss/services/User/base/IUserService.hpp>
#include <Emaject.hpp>

namespace abyss::User
{
    /// <summary>
    /// ユーザーDataStore統括
    /// </summary>
    class DataStore
    {
        friend struct emaject::InjectTraits<abyss::User::DataStore>;
    public:
        template<class T>
        std::shared_ptr<T> get() const
        {
            return std::get<std::shared_ptr<T>>(m_services);
        }
    private:
        template<class... T>
        using Services = std::tuple<std::shared_ptr<T>...>;

        Services<
            IUserService
        >m_services;
    };
}
namespace emaject
{
    template<>
    struct InjectTraits<abyss::User::DataStore>
    {
        void onInject(abyss::User::DataStore* value, emaject::Container* c)
        {
            std::apply([=]<class... T>(T&... s) {
                ((s = c->resolve<typename T::element_type>()), ...);
            }, value->m_services);
        }
    };
}
