#include <abyss/commons/Factory/System/Injector.hpp>
#include <abyss/scenes/Sys/Modules.hpp>
#include <abyss/commons/Factory/Project/Injector.hpp>
#include <abyss/commons/Factory/Adv/Injector.hpp>
#include <abyss/commons/Factory/Stage/Injector.hpp>
#include <abyss/commons/Factory/System/StageFactoryOption.hpp>
#include <abyss/modules/Stage/StageData.hpp>

namespace
{
    using namespace abyss;

    struct CommonInstaller : emaject::IInstaller
    {
        CommonInstaller(
            const Sfx::PostEffectsDesc& postEffectDesc = Sfx::PostEffectsDesc::CreateDefault()
        ) :
            m_postEffectDesc(postEffectDesc)
        {}
        void onBinding(emaject::Container* c) const override
        {
            c->bind<Sys::Modules>().asCached();

            c->bind<GlobalTime>()
                .asCached();

            c->bind<Camera>()
                .asCached();

            c->bind<CycleMaster>()
                .asCached();

            c->bind<DrawManager>()
                .asCached();

            c->bind<Sound>()
                .asCached();

            c->bind<UIs>()
                .asCached();

            c->bind<PostEffects>()
                .withArgs(m_postEffectDesc)
                .asCached();
        }
    private:
        Sfx::PostEffectsDesc m_postEffectDesc;
    };
    struct AdvInstaller : emaject::IInstaller
    {
        void onBinding(emaject::Container* c) const override
        {
            c->bind<Adventures>()
                .asCached();
        }
    };
    struct CronsInstaller : emaject::IInstaller
    {
        void onBinding(emaject::Container* c) const override
        {
            c->bind<Crons>()
                .asCached();
        }
    };
    struct EventsInstaller : emaject::IInstaller
    {
        void onBinding(emaject::Container* c) const override
        {
            c->bind<Events>()
                .asCached();
        }
    };
    struct EnvironmentInstaller : emaject::IInstaller
    {
        EnvironmentInstaller(const FieldEnv::EnvDesc& desc = {}) :
            m_desc(desc)
        {}
        void onBinding(emaject::Container* c) const override
        {
            c->bind<Environment>()
                .withArgs(m_desc)
                .asCached();
        }
    private:
        FieldEnv::EnvDesc m_desc;
    };
    struct EffectsInstaller : emaject::IInstaller
    {
        void onBinding(emaject::Container* c) const override
        {
            c->bind<Effects>()
                .asCached();
        }
    };
    struct StageInstaller : emaject::IInstaller
    {
        void onBinding(emaject::Container* c) const override
        {
            c->bind<Actor::Actors>()
                .asCached();

            c->bind<Actor::Player::PlayerManager>()
                .asCached();

            c->bind<CollisionManager>()
                .asCached();

            c->bind<Decors>()
                .asCached();

            c->bind<Light>()
                .asCached();

            c->bind<Distortion>()
                .asCached();

            c->bind<Pause::PauseManager>()
                .asCached();

            c->bind<PhysicsManager>()
                .asCached();

            c->bind<RoomManager>()
                .asCached();

            c->bind<Stage>()
                .asCached();

            c->bind<Temporary>()
                .asCached();

            c->bind<SpecialEffects>()
                .asCached();

#if ABYSS_DEBUG
            c->bind<WorldComment>()
                .asCached();
#endif
        }
    };
#if ABYSS_DEVELOP
    struct ProjectInstaller : emaject::IInstaller
    {
        void onBinding(emaject::Container* c) const override
        {
            c->bind<Project>()
                .asCached();
        }
    };
#endif
}
namespace abyss::Factory::System
{

#if ABYSS_DEVELOP
    emaject::Injector DevPortal([[maybe_unused]]SequecneData* pData)
    {
        emaject::Injector injector;
        injector
            .install<CommonInstaller>()
            .install<ProjectInstaller>()
            ;

        // Project
        Factory::Project::Install(injector);

        return injector;
    }
#endif

    emaject::Injector Splash([[maybe_unused]]SequecneData* pData)
    {
        emaject::Injector injector;

        injector
            .install<CommonInstaller>()
            ;

        return injector;
    }
    emaject::Injector Title([[maybe_unused]] SequecneData* pData)
    {
        emaject::Injector injector;

        injector
            .install<CommonInstaller>(Sfx::PostEffectsDesc::CreateTitle())
            .install<CronsInstaller>()
            .install<EffectsInstaller>()
            .install<EnvironmentInstaller>(FieldEnv::EnvDesc{
                .useCaustics = true,
            })
            ;

        return injector;
    }
    emaject::Injector SaveSelect([[maybe_unused]] SequecneData* pData)
    {
        emaject::Injector injector;

        injector
            .install<CommonInstaller>()
            .install<EffectsInstaller>()
            ;

        return injector;
    }
    emaject::Injector Home([[maybe_unused]] SequecneData* pData)
    {
        emaject::Injector injector;

        injector
            .install<CommonInstaller>()
            ;

        return injector;
    }
    emaject::Injector Stage([[maybe_unused]] SequecneData* pData, const StageFactoryOption& option)
    {
        emaject::Injector injector;

        injector
            .install<CommonInstaller>(Sfx::PostEffectsDesc::CreateStage())
            .install<AdvInstaller>()
            .install<CronsInstaller>()
            .install<EffectsInstaller>()
            .install<EventsInstaller>()
            .install<EnvironmentInstaller>(FieldEnv::EnvDesc{
                .useSky = true,
                .useCaustics = true,
                .useFog = true
            })
            .install<StageInstaller>()
            ;

        // Adv Project
        if (option.advProject) {
            injector.install([instance = option.advProject](emaject::Container* c) {
                c->bind<abyss::Adv::Project>()
                    .fromInstance(instance)
                    .asCached();
            });
        } else {
            Adv::Install(injector);
            injector.install([](emaject::Container* c) {
                c->bind<abyss::Adv::Project>()
                    .fromNew()
                    .asCached();
            });
        }

        // StageData
        if (option.stageData) {
            injector.install([instance = option.stageData](emaject::Container* c) {
                c->bind<StageData>()
                    .fromInstance(instance)
                    .asCached();
            });
        } else {
            Stage::Install(injector, option.mapPath);
            injector.install([](emaject::Container* c) {
                c->bind<StageData>()
                    .fromNew()
                    .asCached();
            });
        }

        return injector;
    }
    emaject::Injector StageResult([[maybe_unused]] SequecneData* pData)
    {
        emaject::Injector injector;

        injector
            .install<CommonInstaller>()
            ;

        return injector;
    }
}
