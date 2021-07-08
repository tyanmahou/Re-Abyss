#pragma once
#include <abyss/modules/GlobalTime/GlobalTime.hpp>
#include <abyss/modules/Camera/Camera.hpp>
#include <abyss/modules/World/World.hpp>
#include <abyss/modules/Physics/PhysicsManager.hpp>
#include <abyss/modules/Event/Events.hpp>
#include <abyss/modules/Effects/Effects.hpp>
#include <abyss/modules/Sound/Sound.hpp>
#include <abyss/modules/UI/UIs.hpp>
#include <abyss/modules/Actor/Player/PlayerManager.hpp>
#include <abyss/modules/Manager/Manager.hpp>

namespace abyss
{
    /// <summary>
    /// アクションのシステム
    /// </summary>
    class System
    {
        std::unique_ptr<Master> m_master;
        GlobalTime m_time;
        World m_world;
        std::unique_ptr<PhysicsManager> m_physics;
        Events m_events;
        Camera m_camera;
        std::unique_ptr<Light> m_light;
        std::unique_ptr<Distortion> m_distortion;

        Effects m_effects;

        Sound m_sound;
        UIs m_userInterface;
        std::unique_ptr<Stage> m_stage;
        std::unique_ptr<BackGround> m_backGround;
        std::unique_ptr<Decors> m_decors;
        std::unique_ptr<Crons> m_crons;

        std::unique_ptr<Temporary> m_temporary;
        std::unique_ptr<Actor::Player::PlayerManager> m_playerManager;
        std::unique_ptr<DrawManager> m_drawer;
        Manager m_manager;
    public:

        System(IMasterObserver* masterObserver = nullptr);
        ~System();

        void init();

        /// <summary>
        /// プレイヤー情報を継承して初期化
        /// デバッグモードなどで使用
        /// </summary>
        /// <param name="player"></param>
        void init(const std::shared_ptr<Actor::ActorObj>& player);

        void update();
        void draw() const;
        void loadStage(const std::shared_ptr<StageData>& stageData);

        /// <summary>
        /// 一時セーブデータを設定する
        /// </summary>
        /// <param name="saveData"></param>
        void loadTemporaryData(const std::shared_ptr<TemporaryData>& tempData);

        std::shared_ptr<Actor::ActorObj> lockPlayer() const;

        void restart();
    private:
    };
}