﻿#pragma once
#include <abyss/controllers/Camera/Camera.hpp>
#include <abyss/controllers/World/World.hpp>

namespace abyss
{
    /// <summary>
    /// アクションのシステム
    /// </summary>
    class ActionSystem
    {
        inline static ActionSystem* s_main = nullptr;

        Camera m_camera;
        World m_world;
        std::unique_ptr<Stage> m_stage;
    public:
        ActionSystem();
        ActionSystem(std::unique_ptr<Stage>&& stage);

        ~ActionSystem();

        void init();
        void update();
        void draw() const;

        void setStage(std::unique_ptr<Stage>&& stage);

        static ActionSystem* const Main();
        static Camera* const Camera();
    };
}