#include <abyss/commons/Factory/Sound/Injector.hpp>

#include <abyss/datastores/Sound/CSVSoundBankDataStore.hpp>
#include <abyss/services/Sound/SoundBankService.hpp>
#include <abyss/modules/Sound/SoundBank/SoundBank.hpp>

namespace abyss::Factory::Sound
{
    emaject::Injector SoundBank::Injector()
    {
        using namespace abyss::Sound;

        emaject::Injector injector;
        injector
            // datastore
            .install<CSVSoundBankDataStoreInstaller> (Path::SoundPath + U"soundbank.csv", Resource::Assets::Norelease())
            // service
            .install<SoundBankServiceInstaller>()
            // module
            .install([](emaject::Container* c) {
                c->bind<ISoundBank>().to<abyss::Sound::SoundBank>().asCached();
            })
            ;
        return injector;
    }
}