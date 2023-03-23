#include <abyss/commons/Factory/System/Injector.hpp>
#include <abyss/scenes/System/ModulePackage.hpp>

namespace abyss::Factory::System
{
    struct Config
    {
#if ABYSS_DEVELOP
        static consteval Config DevPortal()
        {
            return Config{
                .useProject = true
            };
        }
#endif
        static consteval Config Splash()
        {
            return Config{
            };
        }
        static consteval Config Title()
        {
            return Config{
                .useCron = true,
            };
        }
        static consteval Config SaveSelect()
        {
            return Config{
            };
        }
        static consteval Config Home()
        {
            return Config{
            };
        }
        static consteval Config Stage()
        {
            return Config{
                .isStage = true,
                .useCron = true,
                .useEvent = true,
            };
        }
        static consteval Config StageResult()
        {
            return Config{
            };
        }
    public:
        bool isStage = false;
        bool useCron = false;
        bool useEvent = false;
#if ABYSS_DEVELOP
        bool useProject = false;
#endif
    };
    struct CommonInstaller : emaject::IInstaller
    {
        CommonInstaller(Manager* pManager, const Config& config):
            m_pManager(pManager),
            m_config(config)
        {}
        void onBinding(emaject::Container* c) const override
        {
            if (m_config.isStage) {
                c->bind<Actor::Actors>()
                    .withArgs()
                    .asCached();

                c->bind<Actor::Player::PlayerManager>()
                    .withArgs()
                    .asCached();
            }

            c->bind<Camera>()
                .withArgs()
                .asCached();

            if (m_config.isStage) {
                c->bind<CollisionManager>()
                    .withArgs()
                    .asCached();
            }
            if (m_config.useCron) {
                c->bind<Crons>()
                    .withArgs()
                    .asCached();
            }

            c->bind<CycleMaster>()
                .withArgs()
                .asCached();

            if (m_config.isStage) {
                c->bind<Decors>()
                    .withArgs()
                    .asCached();
            }
#if ABYSS_DEVELOP
            if (m_config.useProject) {
                c->bind<Project>()
                    .withArgs()
                    .asCached();
            }
#endif
#if ABYSS_DEBUG
            c->bind<WorldComment>()
                .withArgs()
                .asCached();
#endif
            if (m_config.isStage) {
                c->bind<Distortion>()
                    .withArgs()
                    .asCached();
            }

            c->bind<DrawManager>()
                .withArgs()
                .asCached();

            c->bind<Effects>()
                .withArgs()
                .asCached();

            c->bind<Environment>()
                .withArgs()
                .asCached();

            if (m_config.useEvent) {
                c->bind<Events>()
                    .withArgs()
                    .asCached();
            }

            c->bind<GlobalTime>()
                .withArgs()
                .asCached();

            if (m_config.isStage) {
                c->bind<Light>()
                    .withArgs()
                    .asCached();

                c->bind<Adventures>()
                    .withArgs()
                    .asCached();

                c->bind<Pause::PauseManager>()
                    .withArgs()
                    .asCached();

                c->bind<PhysicsManager>()
                    .withArgs()
                    .asCached();

                c->bind<RoomManager>()
                    .withArgs()
                    .asCached();
            }

            c->bind<SpecialEffects>()
                .withArgs()
                .asCached();

            c->bind<PostEffects>()
                .withArgs()
                .asCached();

            c->bind<Sound>()
                .withArgs()
                .asCached();

            if (m_config.isStage) {
                c->bind<Stage>()
                    .withArgs()
                    .asCached();

                c->bind<Temporary>()
                    .withArgs()
                    .asCached();
            }

            c->bind<UIs>()
                .withArgs()
                .asCached();
        }
        private:
            Manager* m_pManager;
            Config m_config;
    };

    emaject::Injector Splash(Manager* pManager)
    {
        emaject::Injector injector;

        injector
            .install<CommonInstaller>(pManager, Config::Splash())
            ;

        return injector;
    }
}
