#pragma once
#include <abyss/modules/GlobalTime/GlobalTime.hpp>
#include <abyss/modules/Camera/Camera.hpp>
#include <abyss/modules/World/World.hpp>
#include <abyss/modules/Event/Events.hpp>
#include <abyss/modules/Light/Light.hpp>
#include <abyss/modules/Effects/Effects.hpp>
#include <abyss/modules/Sound/Sound.hpp>
#include <abyss/modules/UI/UI.hpp>
#include <abyss/modules/Actors/Player/PlayerManager.hpp>
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
        std::unique_ptr<Actor::Player::PlayerManager> m_playerManager;
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
        void init(const std::shared_ptr<Actor::IActor>& player);

        void update();
        void draw() const;
        void loadStage(const std::shared_ptr<StageData>& stageData);

        /// <summary>
        /// セーブデータを設定する
        /// </summary>
        /// <param name="saveData"></param>
        void loadSaveData(const std::shared_ptr<SaveData>& saveData);

        std::shared_ptr<Actor::IActor> lockPlayer() const;

        void restart();
    private:
    };
}