#pragma once
#include <abyss/controllers/Camera/Camera.hpp>
#include <abyss/models/WorldModel.hpp>

namespace abyss
{
    /// <summary>
    /// アクションのシステム
    /// </summary>
    class ActionSystem
    {
        inline static ActionSystem* s_main = nullptr;

        Camera m_camera;
        WorldModel m_world;
        std::unique_ptr<StageModel> m_stage;
    public:
        ActionSystem();
        ActionSystem(std::unique_ptr<StageModel>&& stage);

        ~ActionSystem();

        void init();
        void update();
        void draw() const;

        void setStage(std::unique_ptr<StageModel>&& stage);

        static ActionSystem* const Main();
        static Camera* const MainCamera();
    };
}