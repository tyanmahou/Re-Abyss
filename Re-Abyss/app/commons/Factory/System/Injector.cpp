#include <abyss/commons/Factory/System/Injector.hpp>
#include <abyss/scenes/Sys/Modules.hpp>
#include <abyss/commons/Factory/Project/Injector.hpp>
#include <abyss/commons/Factory/Adv/Injector.hpp>
#include <abyss/commons/Factory/Stage/Injector.hpp>
#include <abyss/commons/Factory/System/StageFactoryOption.hpp>
#include <abyss/modules/Stage/StageData.hpp>
#include <abyss/modules/Temporary/TemporaryData.hpp>

namespace
{
    using namespace abyss;

    struct CommonInstaller : emaject::IInstaller
    {
        CommonInstaller(
            SequecneData* pData,
            const Sfx::PostEffectsDesc& postEffectDesc = Sfx::PostEffectsDesc::CreateDefault()
        ) :
            m_pData(pData),
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

            c->bind<Sounds>()
                .withArgs(m_pData->sound.get())
                .asCached();

            c->bind<UIs>()
                .asCached();

            c->bind<PostEffects>()
                .withArgs(m_postEffectDesc)
                .asCached();

            // ストレージ
            c->bind<Storage>()
                .withArgs(m_pData->dataStore)
                .asCached();

            c->bind<Fader>()
                .withArgs(&m_pData->fader)
                .asCached();
        }
    private:
        SequecneData* m_pData;
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
    emaject::Injector DevPortal(SequecneData* pData)
    {
        emaject::Injector injector;
        injector
            .install<CommonInstaller>(pData)
            .install<ProjectInstaller>()
            ;

        // Project
        Factory::Project::Install(injector);

        return injector;
    }
    emaject::Injector Experiment(SequecneData* pData)
    {
        emaject::Injector injector;
        injector
            .install<CommonInstaller>(pData)
            ;

        return injector;
    }
#endif

    emaject::Injector Splash(SequecneData* pData)
    {
        emaject::Injector injector;

        injector
            .install<CommonInstaller>(pData)
            ;

        return injector;
    }
    emaject::Injector Title(SequecneData* pData)
    {
        emaject::Injector injector;

        injector
            .install<CommonInstaller>(pData, Sfx::PostEffectsDesc::CreateTitle())
            .install<CronsInstaller>()
            .install<EffectsInstaller>()
            .install<EnvironmentInstaller>(FieldEnv::EnvDesc{
                .useCaustics = true,
            })
            ;

        return injector;
    }
    emaject::Injector SaveSelect(SequecneData* pData)
    {
        emaject::Injector injector;

        injector
            .install<CommonInstaller>(pData)
            .install<EffectsInstaller>()
            ;

        return injector;
    }
    emaject::Injector Home(SequecneData* pData)
    {
        emaject::Injector injector;

        injector
            .install<CommonInstaller>(pData)
            ;

        return injector;
    }
    emaject::Injector Stage(SequecneData* pData, const StageFactoryOption& option)
    {
        emaject::Injector injector;

        injector
            .install<CommonInstaller>(pData, Sfx::PostEffectsDesc::CreateStage())
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
            Stage::Install(injector, option.stageDef.mapPath());
            injector.install([stageDef = option.stageDef](emaject::Container* c) {
                c->bind<StageData>()
                    .withArgs(stageDef)
                    .asCached();
            });
        }
        // TempData
        {
            injector.install([instance = option.tempData](emaject::Container* c) {
                c->bind<TemporaryData>()
                    .fromInstance(instance)
                    .asCached();
            });
        }
        return injector;
    }
    emaject::Injector StageResult(SequecneData* pData)
    {
        emaject::Injector injector;

        injector
            .install<CommonInstaller>(pData)
            ;

        return injector;
    }
}
