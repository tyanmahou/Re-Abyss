#include <abyss/scenes/Sys/System.hpp>
#include <abyss/views/Camera/CameraView.hpp>
#include <abyss/views/Camera/SnapshotView.hpp>
#include <abyss/debugs/Debug.hpp>
#include <Siv3D.hpp>

namespace abyss::Sys2
{
    System::System(std::shared_ptr<IBooter> booter)
    {
        m_mods = booter->build(&m_manager);
        m_mods->setManager(&m_manager);
        booter->onBoot(&m_manager);
    }

    void System::update()
    {
        auto* timer = mod<GlobalTime>();

        // ポーズ制御
        call(&Pause::PauseManager::update);

        timer->update();

        // フラッシュ
#if ABYSS_DEBUG
        call(&WorldComment::flush);
#endif
        call(&Actors::flush);
        call(&Decors::flush);
        call(&CollisionManager::cleanUp);
        call(&PhysicsManager::cleanUp);

        // Dt計算
        double dt = timer->deltaTime();

        // 環境更新
        call(&Environment::update, dt);

        // ポストエフェクト更新
        mod<PostEffects>()->update(Scene::DeltaTime());
        call(&Light::update, dt);

        call(&Actors::updateDeltaTime, dt);

        auto* events = mod<Events>();
        bool isWorldStop = events ? events->isWorldStop() : false;
        // Actor更新
        if (!isWorldStop) {
            call(&Actors::update);
            call(&Actors::move);
            {
                // 地形衝突
                call(&Actors::prePhysics);
                call(&PhysicsManager::onPhysicsCollision);
                call(&Actors::postPhysics);
            }
        }
        // カメラ更新
        mod<Camera>()->update(dt);

        // Actor衝突後更新
        if (!isWorldStop) {
            call(&Actors::preCollision);
            call(&CollisionManager::onCollision);
            call(&Actors::postCollision);
            call(&Actors::lastUpdate);
        }
        // イベント更新
        if (events) {
            events->update();
        }

        // ノベル更新
        call(&Adventures::update);

        // ui更新
        call(&UIs::update);

        // 装飾更新
        call(&Decors::update);

        // クーロン更新
        call(&Crons::update);

        // クリーンアップ
        call(&Actors::cleanUp);
        call(&PhysicsManager::cleanUp);

        // エフェクト更新
        call(&Effects::updateAll, dt);

        // Sfx
        call(&SpecialEffects::update, dt);

        // 上位命令聴講
        mod<CycleMaster>()->listen();

#if ABYSS_DEBUG
        call(Debug::DebugUtil::AlertDecorCount);
        call(Debug::DebugUtil::AlertEffectCount);
#endif
    }

    void System::draw() const
    {

        auto* drawer = mod<DrawManager>();

        // バッファクリア
        drawer->clear();
        call(&Light::clear);
        call(&Distortion::clear);

        // Draw
        call(&Actors::draw);
        call(&Decors::draw);
        call(&UIs::draw);
        call(&Effects::draw);
        call(&SpecialEffects::draw);

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
                auto getEnv = [env](auto func) {
                    return env ? (env->*func)() : nullptr;
                };
                // 背面
                const auto bgDrawer = [&] {
                    if (auto bg = getEnv(&Environment::getBg)) {
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
                if (auto sky = getEnv(&Environment::getSky)) {
                    sky->draw(cameraView.tl());
                }
                if (auto caustics = getEnv(&Environment::getCaustics)) {
                    caustics->drawBack(cameraView.getCameraPos());
                }
                drawer->draw(DrawLayer::DecorBack);

                call(&RoomManager::drawDeathLine);

                // 中面
                drawer->draw(DrawLayer::Land);
                drawer->draw(DrawLayer::WorldBack);
                drawer->draw(DrawLayer::World);
                drawer->draw(DrawLayer::WorldFront);

                // 全面
                drawer->draw(DrawLayer::DecorFront);
                if (auto caustics = getEnv(&Environment::getCaustics)) {
                    caustics->drawFront(cameraView.getCameraPos());
                }
                // Distortion Map更新
                call(&Distortion::render);
#if ABYSS_DEBUG
                call<Actors>(Debug::DebugUtil::DrawDebug);
                call<PhysicsManager>(Debug::DebugUtil::DrawDebug);
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
                call(&WorldComment::draw);
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
