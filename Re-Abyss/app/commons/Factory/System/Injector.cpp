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

            c->bind<PostEffects>()
                .asCached();

            c->bind<Sound>()
                .asCached();

            c->bind<UIs>()
                .asCached();
        }
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
        void onBinding(emaject::Container* c) const override
        {
            c->bind<Environment>()
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

            c->bind<Effects>()
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
            .install<CommonInstaller>()
            ;

        return injector;
    }
}
