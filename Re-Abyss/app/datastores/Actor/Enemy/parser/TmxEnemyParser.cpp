#include "TmxEnemyParser.hpp"

#include <abyss/entities/Actor/Enemy/EnemyEntity.hpp>
#include <abyss/entities/Actor/Enemy/SlimeEntity.hpp>
#include <abyss/entities/Actor/Enemy/RollingTakoEntity.hpp>
#include <abyss/entities/Actor/Enemy/CaptainTakoEntity.hpp>
#include <abyss/entities/Actor/Enemy/IkalienEntity.hpp>
#include <abyss/entities/Actor/Enemy/LaunSharkEntity.hpp>
#include <abyss/entities/Actor/Enemy/SchieldEntity.hpp>

#include <abyss/entities/Actor/Enemy/CodeZeroEntity.hpp>

using namespace s3d;
using namespace s3dTiled;
using namespace abyss;
using namespace abyss::Actor::Enemy;

namespace
{
	EnemyType ToType(const String& type)
	{
		static const std::unordered_map<String, EnemyType> toTypeMap{
			{U"slime", EnemyType::Slime},
			{U"rolling_tako", EnemyType::RollingTako},
			{U"captain_tako", EnemyType::CaptainTako},
			{U"ikalien", EnemyType::Ikalien},
			{U"laun_shark", EnemyType::LaunShark},
			{U"schield", EnemyType::Schield},

			{U"code_zero", EnemyType::CodeZero},
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

#define PARSE_ENEMY(Name, ...) case EnemyType::##Name :\
{\
    auto it = std::make_shared<Name##Entity>();\
    it->type = EnemyType::##Name;\
    __VA_ARGS__\
	return ParseCommon(it, obj);\
}

	std::shared_ptr<EnemyEntity> Parse(EnemyType type, const s3dTiled::TiledObject& obj)
	{
		switch (type) {
			PARSE_ENEMY(Slime);
			PARSE_ENEMY(RollingTako, {
				it->wait = obj.getProperty(U"wait").value_or(true);
				});
			PARSE_ENEMY(CaptainTako);
			PARSE_ENEMY(Ikalien);
			PARSE_ENEMY(LaunShark);
			PARSE_ENEMY(Schield);
			PARSE_ENEMY(CodeZero);
		default:
			break;
		}
		return nullptr;
	}
#undef PARSE_ENEMY
}
namespace abyss::Actor::Enemy
{
    TmxEnemyParser::TmxEnemyParser(const s3dTiled::TiledObject& obj) :
        m_obj(obj)
    {}
    std::shared_ptr<EnemyEntity> TmxEnemyParser::parse() const
    {
        auto typeStr = m_obj.getProperty(U"type").value_or(s3d::String(U"none"));
        auto type = ToType(typeStr);

        return Parse(type, m_obj);
    }
}
