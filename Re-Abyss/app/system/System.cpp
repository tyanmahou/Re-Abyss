#include "System.hpp"
#include <abyss/system/base/IBooter.hpp>

#include <abyss/views/Camera/CameraView.hpp>
#include <abyss/views/Camera/SnapshotView.hpp>

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

        // フラッシュ
        if constexpr (config.isStage) {
            world->flush();
            decors->flush();
            physics->cleanUp();
        }

        // Dt計算
        double dt = timer->deltaTime();

        // 環境更新
        mod<Environment>()->update(dt);

        if constexpr (config.isStage) {
            mod<Light>()->update(dt);

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
        }
        // クーロン更新
        mod<Crons>()->update();

        // クリーンアップ
        if constexpr (config.isStage) {
            world->cleanUp();
            physics->cleanUp();
        }

        // エフェクト更新
        mod<Effects>()->updateAll(dt);

        // 上位命令聴講
        mod<CycleMaster>()->listen();

        if constexpr (config.isStage) {
#if ABYSS_DEBUG
            Debug::DebugManager::DrawDebug(*decors);
            Debug::DebugManager::DrawDebug(*mod<Effects>());
#endif
        }
    }

    template<Config config>
    void System<config>::draw() const
    {
        auto* drawer = mod<DrawManager>();

        // バッファクリア
        drawer->clear();
        if constexpr (config.isStage) {
            mod<Light>()->clear();
            mod<Distortion>()->clear();
        }

        if constexpr (config.isStage) {
            // Actor Draw
            mod<World>()->draw();
            // Deor Draw
            mod<Decors>()->draw();
        }
        // UI Draw
        mod<UIs>()->draw();
        // Effect Draw
        mod<Effects>()->draw();

        auto* camera = mod<Camera>();
        auto cameraView = camera->createView();
        auto* snapshot = camera->getSnapshot();
        // in camera
        {
            auto sceneRender = snapshot->startSceneRender();
            auto t2d = cameraView.getTransformer();

            auto* env = mod<Environment>();
            // 背面
            env->applyWave([&] {
                if (auto bg = env->getBg()) {
                    bg->draw(cameraView.screenRegion());
                }
                if (auto sky = env->getSky()) {
                    sky->draw(cameraView.tl());
                }
                if constexpr (config.isStage) {
                    mod<BackGround>()->draw(cameraView);
                }
                drawer->draw(DrawLayer::BackGround);
            });
            if (auto ws = env->getWaterSurface()) {
                ws->drawBack(cameraView.getCameraPos());
            }
            drawer->draw(DrawLayer::DecorBack);

            if constexpr (config.isStage) {
                mod<RoomManager>()->drawDeathLine();
            }

            // 中面
            drawer->draw(DrawLayer::DecorMiddle);
            drawer->draw(DrawLayer::World);

            // 全面
            drawer->draw(DrawLayer::DecorFront);
            if (auto ws = env->getWaterSurface()) {
                ws->drawFront(cameraView.getCameraPos());
            }
            if constexpr (config.isStage) {
                // Light Map更新
                mod<Light>()->render();
                // Distortion Map更新
                mod<Distortion>()->render();
            }

            if constexpr (config.isStage) {
#if ABYSS_DEBUG
                Debug::DebugManager::DrawDebug(*mod<World>());
                Debug::DebugManager::DrawDebug(*mod<PhysicsManager>());
#endif
            }
        }
        // PostEffect適用
        if constexpr (config.isStage) {
            snapshot->copySceneToPost()
#if ABYSS_DEBUG
                .apply(Debug::Menu::IsDebug(Debug::DebugFlag::PostEffectLight), [=] { return mod<Light>()->start(); })
#else
                .apply([=] { return mod<Light>()->start(); })
#endif 
#if ABYSS_DEBUG
                .apply(Debug::Menu::IsDebug(Debug::DebugFlag::PostEffectDistortion), [=] { return mod<Distortion>()->start(); })
#else
                .apply([=] { return mod<Distortion>()->start(); })
#endif
                .draw(cameraView.getQuakeOffset());
        } else {
            snapshot->copySceneToPost()
                .draw(cameraView.getQuakeOffset());
        }
        // UI
        {
            drawer->draw(DrawLayer::UI);
        }
    }

    template class System<Config::Splash()>;
    template class System<Config::Title()>;
    template class System<Config::Main()>;
    template class System<Config::SaveSelect()>;
}