#pragma once
#include <Siv3D/Array.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Physics
{
    class IDetectionAlgorithm;
    class IDetector;
    class ITerrain;

    /// <summary>
    /// 地形衝突マネージャー
    /// </summary>
    class PhysicsManager
    {
    public:
        PhysicsManager();

        void addDetector(const std::shared_ptr<IDetector>& detector);
        void addTerrain(const std::shared_ptr<ITerrain>& terrain);

        void onPhysicsCollision();
        void cleanUp();
    private:
        std::shared_ptr<IDetectionAlgorithm> m_detection;
        s3d::Array<Ref<IDetector>> m_detectors;
        s3d::Array<Ref<ITerrain>> m_terrains;
    };
}

namespace abyss
{
    using Physics::PhysicsManager;
}