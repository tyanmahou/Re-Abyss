#pragma once
#include <abyss/modules/GlobalTime/GlobalTime.hpp>
#include <abyss/modules/Camera/Camera.hpp>
#include <abyss/modules/World/World.hpp>
#include <abyss/modules/Physics/PhysicsManager.hpp>
#include <abyss/modules/Event/Events.hpp>
#include <abyss/modules/Effect/Effects.hpp>
#include <abyss/modules/Sound/Sound.hpp>
#include <abyss/modules/UI/UIs.hpp>
#include <abyss/modules/Actor/Player/PlayerManager.hpp>
#include <abyss/modules/Cycle/CycleMaster.hpp>
#include <abyss/modules/Manager/Manager.hpp>

#include <abyss/components/Cycle/Main/Builder.hpp>

namespace abyss::Sys::Main
{
    class System
    {
    public:
        System(Cycle::Main::IMasterObserver* pObserver);
        ~System();

        /// <summary>
        /// 初期化
        /// </summary>
        void init();

        /// <summary>
        /// プレイヤー情報を継承して初期化
        /// デバッグモードなどで使用
        /// </summary>
        /// <param name="player"></param>
        void init(const std::shared_ptr<Actor::ActorObj>& player);

        /// <summary>
        /// 更新
        /// </summary>
        void update();

        /// <summary>
        /// 描画
        /// </summary>
        void draw() const;

        /// <summary>
        /// ステージデータをロード
        /// </summary>
        void loadStage(const std::shared_ptr<StageData>& stageData);

        /// <summary>
        /// 一時セーブデータを設定する
        /// </summary>
        /// <param name="saveData"></param>
        void loadTemporaryData(const std::shared_ptr<TemporaryData>& tempData);

        /// <summary>
        /// プレイヤーを取得
        /// </summary>
        std::shared_ptr<Actor::ActorObj> lockPlayer() const;

        /// <summary>
        /// リスタート
        /// </summary>
        void restart();
    private:
        std::unique_ptr<GlobalTime> m_time;
        std::unique_ptr<World> m_world;
        std::unique_ptr<PhysicsManager> m_physics;
        std::unique_ptr<Events> m_events;
        std::unique_ptr<Camera> m_camera;
        std::unique_ptr<Light> m_light;
        std::unique_ptr<Distortion> m_distortion;

        std::unique_ptr<Effects> m_effects;

        std::unique_ptr<Sound> m_sound;
        std::unique_ptr<UIs> m_userInterface;
        std::unique_ptr<Stage> m_stage;
        std::unique_ptr<BackGround> m_backGround;
        std::unique_ptr<Decors> m_decors;
        std::unique_ptr<Crons> m_crons;

        std::unique_ptr<Temporary> m_temporary;
        std::unique_ptr<Actor::Player::PlayerManager> m_playerManager;
        std::unique_ptr<DrawManager> m_drawer;
        std::unique_ptr<CycleMaster> m_cycleMaster;
        Manager m_manager;
    };
}