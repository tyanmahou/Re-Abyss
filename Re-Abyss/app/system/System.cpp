#include "System.hpp"
#include <abyss/system/base/IBooter.hpp>

#include <abyss/debugs/DebugManager/DebugManager.hpp>
#include <abyss/debugs/Menu/Menu.hpp>
#include <Siv3D.hpp>

namespace abyss::Sys
{
    template<Config config>
    bool System<config>::boot(IBooter* pBooter)
    {
        return pBooter->onBoot(&m_manager);
    }

    template<Config config>
    void System<config>::update()
    {
        auto* timer = mod<GlobalTime>();
        auto* events = mod<Events>();
        auto* ui = mod<UIs>();
        [[maybe_unused]] World* world = nullptr;
        [[maybe_unused]] Decors* decors = nullptr;
        [[maybe_unused]] PhysicsManager* physics = nullptr;
        if constexpr (config.isStage) {
            world = mod<World>();
            decors = mod<Decors>();
            physics = mod<PhysicsManager>();
        }

        timer->update();
        // バッファクリア
        if constexpr(config.isStage) {
            mod<Light>()->clear();
            mod<Distortion>()->clear();
        }

        // フラッシュ
        if constexpr (config.isStage) {
            world->flush();
            decors->flush();
            physics->cleanUp();
        }

        // Dt計算
        double dt = timer->deltaTime();
        if constexpr (config.isStage) {
            world->updateDeltaTime(dt);
        }

        // World更新
        [[maybe_unused]]bool isWorldStop = false;
        if constexpr (config.isStage) {
            isWorldStop = events->isWorldStop();
            if (!isWorldStop) {
                world->update();
                world->move();
                {
                    // 地形衝突
                    world->prePhysics();
                    physics->onPhysicsCollision();
                    world->postPhysics();
                }
            }
        }

        // カメラ更新
        mod<Camera>()->update(dt);

        // World衝突後更新
        if constexpr (config.isStage) {
            if (!isWorldStop) {
                world->collision();
                world->lastUpdate();
            }
        }
        // イベント更新
        events->update();
        // ui更新
        ui->update();

        if constexpr (config.isStage) {
            // 装飾更新
            decors->update();
            // 背景更新
            mod<BackGround>()->update(time->time());
        }
        // クーロン更新
        mod<Crons>()->update();

        // クリーンアップ
        if constexpr (config.isStage) {
            world->cleanUp();
            physics->cleanUp();

#if ABYSS_DEBUG
            Debug::DebugManager::DrawDebug(*decors);
            Debug::DebugManager::DrawDebug(*mod<Effects>());
#endif
        }

        // 上位命令聴講
        mod<CycleMaster>()->listen();
    }

    template<Config config>
    void System<config>::draw() const
    {
        auto* drawer = mod<DrawManager>();
    }

    template class System<Config::Splash()>;
}