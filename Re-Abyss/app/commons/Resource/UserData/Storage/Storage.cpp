#include <abyss/commons/Resource/UserData/Storage/Storage.hpp>
#include <tuple>

#include <abyss/commons/Factory/Storage/Injector.hpp>
#include <abyss/services/User/base/IUserService.hpp>

namespace abyss::Resource::UserData
{
    using namespace abyss::User;

    class Storage::Impl
    {
    public:
        Impl() = default;

        template<class... T>
        using Services = std::tuple<std::shared_ptr<T>...>;

        Services<
            IUserService
        >services;
    };

    Storage::Storage()
    {
        m_pImpl = Factory::Storage::Injector().resolve<Impl>();
    }

    template<class T>
    std::shared_ptr<T> Storage::getService() const
    {
        return std::get<std::shared_ptr<T>>(m_pImpl->services);
    }
    template std::shared_ptr<IUserService> Storage::getService<IUserService>() const;
}

namespace emaject
{
    using abyss::Resource::UserData::Storage;
    template<>
    struct InjectTraits<Storage::Impl>
    {
        void onInject(Storage::Impl* value, Container* c)
        {
            std::apply([=]<class... T>(T&... s) {
                ((s = c->resolve<typename T::element_type>()),...);
            }, value->services);
        }
    };
}
