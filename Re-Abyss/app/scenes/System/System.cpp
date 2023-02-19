#include <abyss/scenes/System/System.hpp>
#include <abyss/scenes/System/IBooter.hpp>

#include <abyss/views/Camera/CameraView.hpp>
#include <abyss/views/Camera/SnapshotView.hpp>

#include <abyss/debugs/Debug.hpp>
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
        [[maybe_unused]] Actors* actors = nullptr;
        [[maybe_unused]] Decors* decors = nullptr;
        [[maybe_unused]] CollisionManager* pCollision = nullptr;
        [[maybe_unused]] PhysicsManager* physics = nullptr;
        if constexpr (config.isStage) {
            actors = mod<Actors>();
            decors = mod<Decors>();
            pCollision = mod<CollisionManager>();
            physics = mod<PhysicsManager>();
        }
        // ポーズ制御
        if constexpr (config.isStage) {
            mod<Pause::PauseManager>()->update();
        }
        timer->update();

        // フラッシュ
#if ABYSS_DEBUG
        mod<WorldComment>()->flush();
#endif
        if constexpr (config.isStage) {
            actors->flush();
            decors->flush();
            pCollision->cleanUp();
            physics->cleanUp();
        }

        // Dt計算
        double dt = timer->deltaTime();

        // 環境更新
        mod<Environment>()->update(dt);

        // ポストエフェクト更新
        mod<PostEffects>()->update(Scene::DeltaTime());

        if constexpr (config.isStage) {
            mod<Light>()->update(dt);

            actors->updateDeltaTime(dt);
        }

        // Actor更新
        [[maybe_unused]]bool isWorldStop = false;
        if constexpr (config.isStage) {
            isWorldStop = events->isWorldStop();
            if (!isWorldStop) {
                actors->update();
                actors->move();
                {
                    // 地形衝突
                    actors->prePhysics();
                    physics->onPhysicsCollision();
                    actors->postPhysics();
                }
            }
        }

        // カメラ更新
        mod<Camera>()->update(dt);

        // Actor衝突後更新
        if constexpr (config.isStage) {
            if (!isWorldStop) {

                actors->preCollision();
                pCollision->onCollision();
                actors->postCollision();

                actors->lastUpdate();
            }
        }
        // イベント更新
        events->update();

        // ノベル更新
        if constexpr (config.isStage) {
            mod<Novels>()->update();
        }

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
            actors->cleanUp();
            physics->cleanUp();
        }

        // エフェクト更新
        mod<Effects>()->updateAll(dt);

        // Sfx
        mod<SpecialEffects>()->update(dt);

        // 上位命令聴講
        mod<CycleMaster>()->listen();

#if ABYSS_DEBUG
        if constexpr (config.isStage) {
            Debug::DebugUtil::AlertDecorCount(*decors);
        }
        Debug::DebugUtil::AlertEffectCount(*mod<Effects>());
#endif
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
            mod<Actors>()->draw();
            // Deor Draw
            mod<Decors>()->draw();
        }
        // UI Draw
        mod<UIs>()->draw();
        // Effect Draw
        mod<Effects>()->draw();
        // SpecialEffects Draw
        mod<SpecialEffects>()->draw();

#if ABYSS_DEBUG
        Debug::DebugUtil::AlertDrawerCount(drawer);
#endif
        auto* camera = mod<Camera>();
        auto cameraView = camera->createView();
        auto cameraMat = cameraView.getMat();
        auto* snapshot = camera->getSnapshot();
        {
            auto sceneRender = snapshot->startSceneRender();

            // in camera
            {
                auto worldRender = snapshot->startWorldRender();
                auto t2d = CameraView::Transformer(cameraMat);

                auto* env = mod<Environment>();
                // 背面
                const auto bgDrawer = [&] {
                    if (auto bg = env->getBg()) {
                        bg->draw(cameraView.screenRegion());
                    }
                    drawer->draw(DrawLayer::BackGround);
                };
                if (auto* decorFar = mod<PostEffects>()->getDecorFar()) {
                    // 遠方表現の使用
                    {
                        auto decorFarRender = snapshot->startDecorFarRender();
                        bgDrawer();
                    }
                    {
                        auto scopedShader = decorFar->start();
                        snapshot->getDecorFarTexture().draw(
                            cameraView.tl()
                        );
                    }
                } else {
                    bgDrawer();
                }
                if (auto sky = env->getSky()) {
                    sky->draw(cameraView.tl());
                }
                if (auto caustics = env->getCaustics()) {
                    caustics->drawBack(cameraView.getCameraPos());
                }
                drawer->draw(DrawLayer::DecorBack);

                if constexpr (config.isStage) {
                    mod<RoomManager>()->drawDeathLine();
                }

                // 中面
                drawer->draw(DrawLayer::Land);
                drawer->draw(DrawLayer::WorldBack);
                drawer->draw(DrawLayer::World);
                drawer->draw(DrawLayer::WorldFront);

                // 全面
                drawer->draw(DrawLayer::DecorFront);
                if (auto caustics = env->getCaustics()) {
                    caustics->drawFront(cameraView.getCameraPos());
                }
                if constexpr (config.isStage) {
                    // Distortion Map更新
                    mod<Distortion>()->render();
                }

                if constexpr (config.isStage) {
#if ABYSS_DEBUG
                    Debug::DebugUtil::DrawDebug(*mod<Actors>());
                    Debug::DebugUtil::DrawDebug(*mod<PhysicsManager>());
#endif
                }
            }

            // PostEffect適用
            {
                Light* light = nullptr;
                Sfx::Bloom* bloom = mod<PostEffects>()->getBloom();
                Sfx::Moisture* moisture = mod<PostEffects>()->getMoisture();
                Distortion* dist = nullptr;
                Sfx::NegaPosiInv* negaPosiInv = mod<PostEffects>()->getNegaPosiInv();
                Sfx::DeadEffect* deadEffect = mod<PostEffects>()->getDeadEffect();
                Sfx::Blur* blur = mod<PostEffects>()->getBlur();
                if constexpr (config.isStage) {
                    light = mod<Light>();
                    dist = mod<Distortion>();
                }
#if ABYSS_DEBUG
                if (!Debug::MenuUtil::IsDebug(Debug::DebugFlag::RenderLight)) {
                    light = nullptr;
                }
                if (!Debug::MenuUtil::IsDebug(Debug::DebugFlag::RenderBloom)) {
                    bloom = nullptr;
                }
                if (!Debug::MenuUtil::IsDebug(Debug::DebugFlag::RenderMoisture)) {
                    moisture = nullptr;
                }
                if (!Debug::MenuUtil::IsDebug(Debug::DebugFlag::RenderDistortion)) {
                    dist = nullptr;
                }
                if (!Debug::MenuUtil::IsDebug(Debug::DebugFlag::RenderNegaPosiInv)) {
                    negaPosiInv = nullptr;
                }
                if (!Debug::MenuUtil::IsDebug(Debug::DebugFlag::RenderDeadEffect)) {
                    deadEffect = nullptr;
                }
                if (!Debug::MenuUtil::IsDebug(Debug::DebugFlag::RenderBlur)) {
                    blur = nullptr;
                }
#endif

                snapshot->copyWorldToPost()
                    .apply(light != nullptr, [=] { return light->start(); })
                    .applyF(bloom, &Sfx::Bloom::apply)
                    .applyF(moisture, &Sfx::Moisture::apply)
                    .paint([=] {
                        // ライトより前
                        drawer->draw(DrawLayer::LightFront);
                    })
                    .apply(dist != nullptr, [=] { return dist->start(); })
                    .apply(negaPosiInv != nullptr && negaPosiInv->isValid(), [=] { return negaPosiInv->start(); })
                    .apply(deadEffect != nullptr && deadEffect->isValid(), [=] { return deadEffect->start(); })
                    .apply(blur != nullptr && blur->isValid(), [=] { return blur->start(); })
                    .drawWorld(cameraView.getQuakeOffset());

            }
            // UI
            {
#if ABYSS_DEBUG
                auto t2d = CameraView::Transformer(cameraMat);
                mod<WorldComment>()->draw();
#endif
            }
            {
                drawer->draw(DrawLayer::UI);
            }
        }
        // 最終描画
        {
            Sfx::Scanline* scanline = mod<PostEffects>()->getScanline();
#if ABYSS_DEBUG
            if (!Debug::MenuUtil::IsDebug(Debug::DebugFlag::RenderScanline)) {
                scanline = nullptr;
            }
#endif
            snapshot->copySceneToPost()
                .apply(scanline != nullptr, [=] { return scanline->start(); })
                .drawScene();
        }
    }

    template class System<Config::Splash()>;
    template class System<Config::Title()>;
    template class System<Config::SaveSelect()>;
    template class System<Config::Home()>;
    template class System<Config::Stage()>;
    template class System<Config::StageResult()>;

#if ABYSS_DEVELOP
    template class System<Config::DevPortal()>;
#endif
}
