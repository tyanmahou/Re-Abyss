#include "EnemyEntityParser.hpp"
#include <abyss/entities/Enemy/EnemyEntity.hpp>
#include <abyss/entities/Enemy/SlimeEntity.hpp>
#include <abyss/entities/Enemy/RollingTakoEntity.hpp>
#include <abyss/entities/Enemy/CaptainTakoEntity.hpp>

using namespace s3d;
using namespace s3dTiled;
using namespace abyss;

namespace
{
	EnemyType ToType(const String& type) 
	{
		static const std::unordered_map<String, EnemyType> toTypeMap{
			{U"slime", EnemyType::Slime},
			{U"rolling_tako", EnemyType::RollingTako},
			{U"captain_tako", EnemyType::CaptainTako},
		};
		if (toTypeMap.find(type) != toTypeMap.end()) {
			return toTypeMap.at(type);
		}
		return EnemyType::None;
	};

	std::shared_ptr<EnemyEntity> ParseCommon(const std::shared_ptr<EnemyEntity>& entity, const s3dTiled::TiledObject& obj)
	{
		if (entity) {
			Vec2 size = obj.toRectF().size;
			entity->pos = obj.pos + Vec2{ size.x / 2, -size.y / 2 };
			entity->forward = obj.isMirrored ? Forward::Right : Forward::Left;
		}
		return entity;
	}
	std::shared_ptr<EnemyEntity> ParseSlime(const s3dTiled::TiledObject& obj)
	{
		auto ret = std::make_shared<SlimeEntity>();
		ret->type = EnemyType::Slime;
		return ParseCommon(ret, obj);
	}

	std::shared_ptr<EnemyEntity> ParseRollingTako(const s3dTiled::TiledObject& obj)
	{
		auto ret = std::make_shared<RollingTakoEntity>();
		ret->type = EnemyType::RollingTako;
		ret->wait = obj.getProperty(U"wait").value_or(true);
		return ParseCommon(ret, obj);
	}

	std::shared_ptr<EnemyEntity> ParseCaptainTako(const s3dTiled::TiledObject& obj)
	{
		auto ret = std::make_shared<CaptainTako>();
		ret->type = EnemyType::CaptainTako;
		return ParseCommon(ret, obj);
	}
	
	std::shared_ptr<EnemyEntity> Parse(EnemyType type, const s3dTiled::TiledObject& obj)
	{
		switch (type) {
		case EnemyType::Slime:
			return ParseSlime(obj);
		case EnemyType::RollingTako:
			return ParseRollingTako(obj);
		case EnemyType::CaptainTako:
			return ParseCaptainTako(obj);
		default:
			break;
		}
		return nullptr;
	}
}
namespace abyss
{
    TiledEnemyEntityParser::TiledEnemyEntityParser(const s3dTiled::TiledObject& obj):
        m_obj(obj)
    {}
    std::shared_ptr<EnemyEntity> TiledEnemyEntityParser::parse() const
    {
		auto typeStr = m_obj.getProperty(U"type").value_or(s3d::String(U"none"));
		auto type = ToType(typeStr);

		return Parse(type, m_obj);
    }
}
