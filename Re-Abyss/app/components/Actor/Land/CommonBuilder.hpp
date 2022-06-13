#pragma once
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/modules/Physics/base/TerrainData.hpp>

namespace abyss::Actor::Land
{
    struct BuildOption
    {
        friend struct CommonBuilder;
    public:
        BuildOption();

        BuildOption& setPos(const s3d::Vec2& _pos)
        {
            this->pos = _pos;
            return *this;
        }

        BuildOption& setSize(const s3d::Vec2& _size)
        {
            this->size = _size;
            return *this;
        }
        BuildOption& setColDirection(ColDirection _col)
        {
            this->col = _col;
            return *this;
        }
        BuildOption& setTerrainTag(const Physics::TagType& tag)
        {
            this->terrainTag = tag;
            return *this;
        }

        BuildOption& setTerrainExtData(const std::shared_ptr<Physics::ITerrainExtData>& data)
        {
            this->terrainExtData = data;
            return *this;
        }

        template<Physics::TerrainExtended T, class... Args>
        BuildOption& setTerrainExtData(Args&&... args)
        {
            return this->setTerrainExtData(std::make_shared<T>(std::forward<Args>(args)...));
        }
    private:
        s3d::Vec2 pos{0,0};
        s3d::Vec2 size{0,0};

        ColDirection col;
        Physics::TagType terrainTag;
        std::shared_ptr<Physics::ITerrainExtData> terrainExtData;
    };
	struct CommonBuilder
	{
		static void Build(ActorObj* pActor, const BuildOption& opt = BuildOption{});
	};
}
