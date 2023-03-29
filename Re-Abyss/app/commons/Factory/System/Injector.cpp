#include <abyss/commons/Factory/System/Injector.hpp>
#include <abyss/scenes/Sys/Modules.hpp>
#include <abyss/commons/Factory/Project/Injector.hpp>

namespace
{
    using namespace abyss;

    struct ModuleInstaller : emaject::IInstaller
    {
        void onBinding(emaject::Container* c) const override
        {
            c->bind<Sys2::Modules>().asCached();
        }
    };
    struct CommonInstaller : emaject::IInstaller
    {
        CommonInstaller(
            const Sfx::PostEffectsDesc& postEffectDesc = Sfx::PostEffectsDesc::CreateDefault()
        ) :
            m_postEffectDesc(postEffectDesc)
        {}
        void onBinding(emaject::Container* c) const override
        {
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
                .withArgs()
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
                .fromFactory([](emaject::Container* c) {
                return std::make_shared<Project>(c->resolve<Devs::Project::IProjectService>());
                })
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
            .install<ModuleInstaller>()
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
            .install<ModuleInstaller>()
            .install<CommonInstaller>()
            ;

        return injector;
    }
    emaject::Injector Title([[maybe_unused]] SequecneData* pData)
    {
        emaject::Injector injector;

        injector
            .install<ModuleInstaller>()
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
            .install<ModuleInstaller>()
            .install<CommonInstaller>()
            .install<EffectsInstaller>()
            ;

        return injector;
    }
}
