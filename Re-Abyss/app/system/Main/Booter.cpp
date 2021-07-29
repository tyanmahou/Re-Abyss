#include "Booter.hpp"

#include <abyss/modules/Manager/Manager.hpp>
#include <abyss/modules/World/World.hpp>
#include <abyss/modules/Actor/Player/PlayerManager.hpp>
#include <abyss/modules/Cron/Crons.hpp>
#include <abyss/modules/Cycle/CycleMaster.hpp>
#include <abyss/modules/Event/Events.hpp>

#include <abyss/modules/Stage/Stage.hpp>
#include <abyss/modules/Temporary/Temporary.hpp>

#include <abyss/components/Actor/Player/Builder.hpp>
#include <abyss/components/Actor/God/Builder.hpp>
#include <abyss/components/Cron/BubbleGenerator/Builder.hpp>
#include <abyss/components/Event/GameReady/Builder.hpp>

#include <abyss/components/Cycle/Main/Builder.hpp>

namespace abyss::Sys::Main
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
        auto* stage = pManager->getModule<Stage>();
        {
            stage->setStageData(m_stageData);
            stage->load();
        }

        // Temporary初期化
        auto* temporary = pManager->getModule<Temporary>();
        {
            temporary->setTemporaryData(m_tempData);
            if constexpr (kind == BootKind::Restart) {
                // リスタートでリセットのフラグをリセット
                temporary->clearFlag(TempLevel::Restart);
            }
        }

        // Events初期化
        {
            std::shared_ptr<Event::IEvent> initEvent = m_initEvent;
            if (!initEvent) {
                // 指定がなければReadyイベント生成
                initEvent = std::make_shared<Event::IEvent>();
                Event::GameReady::Builder::Build(initEvent.get());
            }
            auto events = pManager->getModule<Events>();
            events->regist(initEvent);
            events->init();
        }

        // プレイヤー初期化
        auto* playerManager = pManager->getModule<Actor::Player::PlayerManager>();
        std::shared_ptr<Actor::ActorObj> player = m_initPlayer;
        {
            if (!player) {
                // 未初期化なら生成
                s3d::int32 startId = 0;
                if constexpr (kind == BootKind::Restart) {
                    // リスタートの場合保存されているスタート地点から再開
                    startId = temporary->getRestartId().value_or(0);
                }

                auto initStartPos = stage->findStartPos(startId);
                if (!initStartPos) {
                    return false;
                }
                player = std::make_shared<Actor::ActorObj>();
                Actor::Player::Builder::Build(player.get(), *initStartPos);
            }
            // PlayerManager初期化
            playerManager->regist(player);
        }

        // World初期化
        auto* world = pManager->getModule<World>();
        {
            world->create<Actor::God::Builder>(); // God生成
            world->regist(player);          // プレイヤー登録
        }

        // Cron初期化
        {
            auto* cron = pManager->getModule<Crons>();

            // バブルエフェクト
            cron->create<Cron::BubbleGenerator::BuildIntervalTime>(3s);
        }
        return stage->init();
    }

    template class Booter<BootKind::Normal>;
    template class Booter<BootKind::Restart>;
}
