#pragma once
#include <abyss/controllers/TimeController/TimeController.hpp>
#include <abyss/controllers/Camera/Camera.hpp>
#include <abyss/controllers/World/World.hpp>
#include <abyss/controllers/Event/Events.hpp>
#include <abyss/controllers/Light/Light.hpp>
#include <abyss/controllers/Effects/Effects.hpp>
#include <abyss/controllers/Sound/Sound.hpp>
#include <abyss/controllers/UI/UI.hpp>
#include <abyss/controllers/Manager/Manager.hpp>

namespace abyss
{
    /// <summary>
    /// アクションのシステム
    /// </summary>
    class System
    {
        TimeController m_time;

        Camera m_camera;
        Light m_light;
        World m_world;
        Events m_events;
        Effects m_effects;

        Sound m_sound;
        UI m_userInterface;

        Manager m_manager;
        std::unique_ptr<Stage> m_stage;
        std::unique_ptr<BackGround> m_backGround;
        std::unique_ptr<Decor> m_decor;
        std::unique_ptr<Cron> m_cron;
    public:
        System();
        ~System();

        void init();

        /// <summary>
        /// プレイヤー情報を継承して初期化
        /// デバッグモードなどで使用
        /// </summary>
        /// <param name="player"></param>
        void init(const std::shared_ptr<Player::PlayerActor>& player);

        void update();
        void draw() const;

        void loadStage(const std::shared_ptr<StageData>& stageData);

        std::shared_ptr<Player::PlayerActor> lockPlayer() const;
    };
}