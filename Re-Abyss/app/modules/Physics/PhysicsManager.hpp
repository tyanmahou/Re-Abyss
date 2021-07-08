#pragma once
#include <memory>
#include <Siv3D/Array.hpp>
#include <abyss/utils/IdGenerator/IdGenerator.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Physics
{
    class IDetectionAlgorithm;
    class IContacter;
    class ITerrain;

    /// <summary>
    /// 地形衝突マネージャー
    /// </summary>
    class PhysicsManager
    {
    public:
        PhysicsManager();

        template<class Type, class... Args>
        Ref<Type> regist(Args&&... args)
        {
            auto obj = std::make_shared<Type>(std::forward<Args>(args)...);
            this->regist(obj);
            return obj;
        }
        void regist(const std::shared_ptr<IContacter>& contacter);
        void regist(const std::shared_ptr<ITerrain>& terrain);

        void onPhysicsCollision();
        void cleanUp();
    private:
        std::shared_ptr<IDetectionAlgorithm> m_detection;
        s3d::Array<std::shared_ptr<IContacter>> m_contacters;
        s3d::Array<std::shared_ptr<ITerrain>> m_terrains;

        IdGenerator m_idCounter;
    };
}

namespace abyss
{
    using Physics::PhysicsManager;
}