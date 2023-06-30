#include <abyss/scenes/Scene/Stage/Booter.hpp>

#include <abyss/modules/Manager/Manager.hpp>
#include <abyss/modules/Actor/Actors.hpp>
#include <abyss/modules/Actor/Player/PlayerManager.hpp>
#include <abyss/modules/Cron/Crons.hpp>
#include <abyss/modules/Cycle/CycleMaster.hpp>
#include <abyss/modules/Event/Events.hpp>
#include <abyss/modules/Sfx/PostEffects.hpp>
#include <abyss/modules/Stage/Stage.hpp>
#include <abyss/modules/Stage/StageData.hpp>
#include <abyss/modules/Temporary/Temporary.hpp>
#include <abyss/modules/Adv/Adventures.hpp>
#include <abyss/modules/Adv/Project/Project.hpp>
#include <abyss/modules/Sound/Sounds.hpp>

#include <abyss/components/Actor/Player/Builder.hpp>
#include <abyss/components/Actor/God/Builder.hpp>
#include <abyss/components/Event/GameReady/Builder.hpp>
#include <abyss/components/Cron/BubbleGenerator/Builder.hpp>
#include <abyss/components/Cron/FishGenerator/Builder.hpp>
#include <abyss/components/Cycle/Main/Builder.hpp>

namespace abyss::Scene::Stage
{
    template<BootKind kind>
    Booter<kind>::Booter(Cycle::Main::IMasterObserver* pObserver) :
        m_pObserver(pObserver)
    {}
    template<BootKind kind>
    bool Booter<kind>::onBoot(Manager* pManager) const
    {
        // Cycle初期化
        {
            auto* cycle = pManager->getModule<CycleMaster>();
            cycle->build<Cycle::Main::Builder>(m_pObserver);
            cycle->init();
        }

        // Stage初期化
        auto* stage = pManager->getModule<abyss::Stage>();

        // Temporary初期化
        auto* temporary = pManager->getModule<Temporary>();
        {
            if constexpr (kind == BootKind::Restart) {
                // リスタートでリセットのフラグをリセット
                temporary->clearFlag(TempLevel::Restart);
            }
        }

        // Events初期化
        {
            std::shared_ptr<Event::EventObj> initEvent = m_initEvent;
            if (!initEvent) {
                // 指定がなければReadyイベント生成
                initEvent = std::make_shared<Event::EventObj>();
                Event::GameReady::Builder::Build(initEvent.get());
            }
            auto events = pManager->getModule<Events>();
            events->regist(initEvent);
            events->init();
        }

        // プレイヤー初期化
        auto* playerManager = pManager->getModule<Actor::Player::PlayerManager>();
        std::shared_ptr<Actor::ActorObj> player;
        {
            auto desc = m_playerDesc;
            if constexpr (kind == BootKind::Restart) {
                // リスタートの場合保存されているスタート地点から再開
                desc.startId = temporary->getRestartId().value_or(0);
            }
            s3d::int32 startId = desc.startId;

            auto initStartPos = stage->findStartPos(startId);
            if (!initStartPos) {
                return false;
            }
            player = std::make_shared<Actor::ActorObj>();
            player->setManager(pManager);
            Actor::Player::Builder::Build(player.get(), desc);

            // PlayerManager初期化
            playerManager->regist(player);
        }

        // Actor初期化
        auto* actors = pManager->getModule<Actors>();
        {
            actors->create<Actor::God::Builder>(); // God生成
            actors->regist(player);          // プレイヤー登録
        }

        // Cron初期化
        {
            auto* cron = pManager->getModule<Crons>();

            // バブルエフェクト
            cron->create<Cron::BubbleGenerator::BuildOnce>();

            // 魚
            cron->create<Cron::FishGenerator::BuildOnce>();
        }
        // Sound
        {
            pManager->getModule<Sounds>()->stop();
        }
        return stage->init();
    }

    template class Booter<BootKind::Normal>;
    template class Booter<BootKind::Restart>;
}
