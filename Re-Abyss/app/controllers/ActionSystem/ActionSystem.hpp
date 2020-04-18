#pragma once
#include <abyss/controllers/Camera/Camera.hpp>
#include <abyss/controllers/World/World.hpp>
#include <abyss/controllers/Light/Light.hpp>
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
        std::shared_ptr<Stage> m_stage;

        ActManager m_manager;
    public:
        ActionSystem();
        ActionSystem(const std::shared_ptr<Stage>& stage);

        ~ActionSystem();

        void init();
        void update();
        void draw() const;

        void setStage(std::unique_ptr<Stage>&& stage);
    };
}