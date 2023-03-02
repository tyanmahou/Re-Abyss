#include <abyss/commons/Factory/Message/Injector.hpp>

#include <abyss/datastores/Msg/CSVMessageDataStore.hpp>
#include <abyss/services/Msg/MessageService.hpp>

namespace abyss::Factory::Message
{
    emaject::Injector Injector(const Resource::Msg::Language& lang, Resource::Assets* pAssets)
    {
        using namespace abyss::Resource::Msg;

        emaject::Injector injector;
        injector
            // datastore
            .install<CSVMessageDataStoreInstaller>(pAssets)
            // service
            .install<MessageServiceInstaller>(lang)
            ;
        return injector;
    }
}
