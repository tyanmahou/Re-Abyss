#pragma once
#include <abyss/controllers/GlobalTime/GlobalTime.hpp>
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
        GlobalTime m_time;
        World m_world;
        Events m_events;
        Camera m_camera;
        Light m_light;
        Effects m_effects;

        Sound m_sound;
        UI m_userInterface;

        std::unique_ptr<Stage> m_stage;
        std::unique_ptr<BackGround> m_backGround;
        std::unique_ptr<Decor> m_decor;
        std::unique_ptr<Cron> m_cron;

        std::unique_ptr<Save> m_save;

        Manager m_manager;
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

        /// <summary>
        /// セーブデータを設定する
        /// </summary>
        /// <param name="saveData"></param>
        void loadSaveData(const std::shared_ptr<SaveData>& saveData);

        std::shared_ptr<Player::PlayerActor> lockPlayer() const;

        void restart();
    private:
    };
}