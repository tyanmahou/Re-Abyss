#include <abyss/scenes/Sys/System.hpp>
#include <abyss/views/Camera/CameraView.hpp>
#include <abyss/views/Camera/SnapshotView.hpp>
#include <abyss/debugs/Debug.hpp>
#include <Siv3D.hpp>

namespace abyss::Sys2
{
    System::System(std::shared_ptr<IBooter> booter)
    {
        m_mods = booter->module();
        m_mods->setManager(&m_manager);
        booter->onBoot(&m_manager);
    }

    void System::update()
    {
        auto* timer = mod<GlobalTime>();
        auto* events = mod<Events>();
        auto* ui = mod<UIs>();
        auto* actors = mod<Actors>();
        auto* decors = mod<Decors>();
        auto* pCollision = mod<CollisionManager>();
        auto* physics = mod<PhysicsManager>();

        // ポーズ制御
        if (auto* pauseManager = mod<Pause::PauseManager>()) {
            pauseManager->update();
        }

        timer->update();

        // フラッシュ
#if ABYSS_DEBUG
        mod<WorldComment>()->flush();
#endif
        if (actors) {
            actors->flush();
        }
        if (decors) {
            decors->flush();
        }
        if (pCollision) {
            pCollision->cleanUp();
        }
        if (physics) {
            physics->cleanUp();
        }
        // Dt計算
        double dt = timer->deltaTime();

        // 環境更新
        mod<Environment>()->update(dt);

        // ポストエフェクト更新
        mod<PostEffects>()->update(Scene::DeltaTime());
        if (auto* light = mod<Light>()) {
            light->update(dt);
        }
        if (actors) {
            actors->updateDeltaTime(dt);
        }

        bool isWorldStop = events ? events->isWorldStop() : false;
        // Actor更新
        if (!isWorldStop) {
            if (actors) {
                actors->update();
                actors->move();
            }
            {
                // 地形衝突
                if (actors) {
                    actors->prePhysics();
                }
                if (physics) {
                    physics->onPhysicsCollision();
                }
                if (actors) {
                    actors->postPhysics();
                }
            }
        }
        // カメラ更新
        mod<Camera>()->update(dt);

        // Actor衝突後更新
        if (!isWorldStop) {
            if (actors) {
                actors->preCollision();
            }
            if (pCollision) {
                pCollision->onCollision();
            }
            if (actors) {
                actors->postCollision();

                actors->lastUpdate();
            }
        }
        // イベント更新
        if (events) {
            events->update();
        }

        // ノベル更新
        if (auto* adv = mod<Adventures>()) {
            adv->update();
        }

        // ui更新
        ui->update();

        // 装飾更新
        if (decors) {
            decors->update();
        }

        // クーロン更新
        if (auto* cron = mod<Crons>()) {
            cron->update();
        }

        // クリーンアップ
        if (actors) {
            actors->cleanUp();
        }
        if (physics) {
            physics->cleanUp();
        }

        // エフェクト更新
        mod<Effects>()->updateAll(dt);

        // Sfx
        mod<SpecialEffects>()->update(dt);

        // 上位命令聴講
        mod<CycleMaster>()->listen();

#if ABYSS_DEBUG
        if (decors) {
            Debug::DebugUtil::AlertDecorCount(*decors);
        }
        Debug::DebugUtil::AlertEffectCount(*mod<Effects>());
#endif
    }

    void System::draw() const
    {

        auto* drawer = mod<DrawManager>();

        // バッファクリア
        drawer->clear();
        if (auto* light = mod<Light>()) {
            light->clear();
        }
        if (auto* distortion = mod<Distortion>()) {
            distortion->clear();
        }

        if (auto* actor = mod<Actors>()) {
            // Actor Draw
            actor->draw();
        }
        if (auto* decors = mod<Decors>()) {
            // Deor Draw
            decors->draw();
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

                if (auto room = mod<RoomManager>()) {
                    room->drawDeathLine();
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
                if (auto distortion = mod<Distortion>()) {
                    // Distortion Map更新
                    distortion->render();
                }
#if ABYSS_DEBUG
                if (auto* actor = mod<Actors>()) {
                    Debug::DebugUtil::DrawDebug(*actor);
                }
                if (auto* physics = mod<PhysicsManager>()) {
                    Debug::DebugUtil::DrawDebug(*physics);
                }
#endif
            }

            // PostEffect適用
            {
                Light* light = mod<Light>();
                Sfx::Bloom* bloom = mod<PostEffects>()->getBloom();
                Sfx::Moisture* moisture = mod<PostEffects>()->getMoisture();
                Distortion* dist = mod<Distortion>();
                Sfx::NegaPosiInv* negaPosiInv = mod<PostEffects>()->getNegaPosiInv();
                Sfx::DeadEffect* deadEffect = mod<PostEffects>()->getDeadEffect();
                Sfx::Blur* blur = mod<PostEffects>()->getBlur();
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
                    .drawWorld(cameraView.getQuakeOffset())
                    ;

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
}
