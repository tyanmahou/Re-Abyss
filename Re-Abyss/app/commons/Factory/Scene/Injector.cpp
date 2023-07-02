#include <abyss/commons/Factory/Scene/Injector.hpp>

#include <abyss/commons/Factory/Storage/Injector.hpp>
#include <abyss/commons/Factory/Sound/Injector.hpp>
#include <abyss/modules/User/UserData.hpp>
#include <abyss/modules/Sound/SceneSound.hpp>

namespace abyss::Factory::Scene
{
    emaject::Injector SequenceData::Injector()
    {
        emaject::Injector injector;

        Storage::Install(injector);
        Sound::SoundBank::Install(injector);

        injector.install([](emaject::Container* container) {
            container->bind<User::UserData>()
                .asCached();
            container->bind<abyss::Sound::SceneSound>()
                .fromFactory([](emaject::Container* c) {
                    return std::make_shared<abyss::Sound::SceneSound>(
                        c->resolve<abyss::Sound::ISoundBank>()
                    );
                })
                .asCached();
        });
        return injector;
    }
}
