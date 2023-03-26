#include <abyss/commons/Factory/System/Injector.hpp>
#include <abyss/scenes/System/ModulePackage.hpp>
#include <abyss/commons/Factory/Project/Injector.hpp>

namespace
{
    using namespace abyss;
    struct ProjectInstaller : emaject::IInstaller
    {
        ProjectInstaller(Manager* pManager) :
            m_pManager(pManager)
        {}
        void onBinding(emaject::Container* c) const override
        {
            c->bind<Project>()
                .fromFactory([](emaject::Container* c) {
                    return std::make_shared<Project>(c->resolve<Devs::Project::IProjectService>());
                })
                .asCached();
        }
    private:
        Manager* m_pManager;
    };

}
namespace abyss::Factory::System
{
    struct CommonInstaller : emaject::IInstaller
    {
        CommonInstaller(Manager* pManager) :
            m_pManager(pManager)
        {}
        void onBinding(emaject::Container* c) const override
        {
            //            if (m_config.isStage) {
            //                c->bind<Actor::Actors>()
            //                    .withArgs()
            //                    .asCached();
            //
            //                c->bind<Actor::Player::PlayerManager>()
            //                    .withArgs()
            //                    .asCached();
            //            }
            //
            //            c->bind<Camera>()
            //                .withArgs()
            //                .asCached();
            //
            //            if (m_config.isStage) {
            //                c->bind<CollisionManager>()
            //                    .withArgs()
            //                    .asCached();
            //            }
            //            if (m_config.useCron) {
            //                c->bind<Crons>()
            //                    .withArgs()
            //                    .asCached();
            //            }
            //
            //            c->bind<CycleMaster>()
            //                .withArgs()
            //                .asCached();
            //
            //            if (m_config.isStage) {
            //                c->bind<Decors>()
            //                    .withArgs()
            //                    .asCached();
            //            }
            //#if ABYSS_DEVELOP
            //            if (m_config.useProject) {
            //                c->bind<Project>()
            //                    .withArgs()
            //                    .asCached();
            //            }
            //#endif
            //#if ABYSS_DEBUG
            //            c->bind<WorldComment>()
            //                .withArgs()
            //                .asCached();
            //#endif
            //            if (m_config.isStage) {
            //                c->bind<Distortion>()
            //                    .withArgs()
            //                    .asCached();
            //            }
            //
            //            c->bind<DrawManager>()
            //                .withArgs()
            //                .asCached();
            //
            //            c->bind<Effects>()
            //                .withArgs()
            //                .asCached();
            //
            //            c->bind<Environment>()
            //                .withArgs()
            //                .asCached();
            //
            //            if (m_config.useEvent) {
            //                c->bind<Events>()
            //                    .withArgs()
            //                    .asCached();
            //            }
            //
            //            c->bind<GlobalTime>()
            //                .withArgs()
            //                .asCached();
            //
            //            if (m_config.isStage) {
            //                c->bind<Light>()
            //                    .withArgs()
            //                    .asCached();
            //
            //                c->bind<Adventures>()
            //                    .withArgs()
            //                    .asCached();
            //
            //                c->bind<Pause::PauseManager>()
            //                    .withArgs()
            //                    .asCached();
            //
            //                c->bind<PhysicsManager>()
            //                    .withArgs()
            //                    .asCached();
            //
            //                c->bind<RoomManager>()
            //                    .withArgs()
            //                    .asCached();
            //            }
            //
            //            c->bind<SpecialEffects>()
            //                .withArgs()
            //                .asCached();
            //
            //            c->bind<PostEffects>()
            //                .withArgs()
            //                .asCached();
            //
            //            c->bind<Sound>()
            //                .withArgs()
            //                .asCached();
            //
            //            if (m_config.isStage) {
            //                c->bind<Stage>()
            //                    .withArgs()
            //                    .asCached();
            //
            //                c->bind<Temporary>()
            //                    .withArgs()
            //                    .asCached();
            //            }
            //
            //            c->bind<UIs>()
            //                .withArgs()
            //                .asCached();
        }
    private:
        Manager* m_pManager;
    };

    emaject::Injector DevPortal(Manager* pManager, SequecneData* pData)
    {
        emaject::Injector injector;
        injector
            .install<ProjectInstaller>(pManager)
            ;

        // Project
        Factory::Project::Install(injector);

        return injector;
    }
    emaject::Injector Splash(Manager* pManager)
    {
        emaject::Injector injector;

        injector
            .install<CommonInstaller>(pManager)
            ;

        return injector;
    }
}
