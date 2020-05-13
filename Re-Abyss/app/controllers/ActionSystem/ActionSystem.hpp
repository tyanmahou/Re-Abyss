#pragma once
#include <abyss/controllers/Camera/Camera.hpp>
#include <abyss/controllers/World/World.hpp>
#include <abyss/controllers/Event/Events.hpp>
#include <abyss/controllers/Light/Light.hpp>
#include <abyss/controllers/Sound/Sound.hpp>
#include <abyss/controllers/ActionSystem/ActManager.hpp>

namespace abyss
{
    /// <summary>
    /// アクションのシステム
    /// </summary>
    class ActionSystem
    {
        Camera m_camera;
        Light m_light;
        World m_world;
        Events m_events;
        std::shared_ptr<Stage> m_stage;

        Sound m_sound;
        ActManager m_manager;
    public:
        ActionSystem();
        ActionSystem(const std::shared_ptr<Stage>& stage);

        ~ActionSystem();

        void init();

        /// <summary>
        /// プレイヤー情報を継承して初期化
        /// デバッグモードなどで使用
        /// </summary>
        /// <param name="player"></param>
        void init(const std::shared_ptr<Player::PlayerActor>& player);

        void update();
        void draw() const;

        void setStage(std::unique_ptr<Stage>&& stage);

        std::shared_ptr<Player::PlayerActor> lockPlayer() const;
    };
}