#include <abyss/datastores/Actor/Enemy/parser/TmxEnemyParser.hpp>

#include <abyss/entities/Actor/Enemy/EnemyEntity.hpp>
#include <abyss/entities/Actor/Enemy/SlimeEntity.hpp>
#include <abyss/entities/Actor/Enemy/RollingTakoEntity.hpp>
#include <abyss/entities/Actor/Enemy/CaptainTakoEntity.hpp>
#include <abyss/entities/Actor/Enemy/IkalienEntity.hpp>
#include <abyss/entities/Actor/Enemy/LaunSharkEntity.hpp>
#include <abyss/entities/Actor/Enemy/SchieldEntity.hpp>
#include <abyss/entities/Actor/Enemy/WarrusEntity.hpp>
#include <abyss/entities/Actor/Enemy/BabyDuxEntity.hpp>
#include <abyss/entities/Actor/Enemy/BazookaKunEntity.hpp>

#include <abyss/entities/Actor/Enemy/KingDuxEntity.hpp>

#include <abyss/entities/Actor/Enemy/CodeZeroEntity.hpp>

#include <abyss/utils/Enum/EnumTraits.hpp>

using namespace s3d;
using namespace s3dTiled;
using namespace abyss;
using namespace abyss::Actor::Enemy;

namespace
{
	std::shared_ptr<EnemyEntity> ParseCommon(const std::shared_ptr<EnemyEntity>& entity, const s3dTiled::Object& obj)
	{
		if (entity) {
			Vec2 size = obj.toRectF().size;
			entity->pos = obj.pos + Vec2{ size.x / 2, -size.y / 2 };
            entity->footPos = obj.pos + Vec2{ size.x / 2, 0 };
            entity->forward = obj.isMirrored ? Forward::Right() : Forward::Left();
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

	std::shared_ptr<EnemyEntity> Parse(EnemyType type, const s3dTiled::Object& obj)
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
			PARSE_ENEMY(Warrus);
            PARSE_ENEMY(BabyDux);
        case EnemyType::BazookaKun:
            {
                auto it = std::make_shared<BazookaKunEntity>();
                it->type = EnemyType::BazookaKun;
                it->isMirrored = obj.isMirrored;
                it->isFlipped = obj.isFlipped;
                it->rotate = obj.rotation;
                it->forward = obj.isMirrored ? Forward::Right() : Forward::Left();
                Vec2 size = obj.toRectF().size;
                RectF rect{ obj.pos + Vec2{0, -size.y}, size};
                it->pos = rect.center().rotatedAt(rect.bl(), s3d::ToRadians(obj.rotation));
                it->isFixBazooka = obj.getProperty(U"fix_bazooka").value_or(false);
                it->bazookaRotate = obj.getProperty(U"bazooka_rotate").value_or(0.0);
                return it;
            }
            PARSE_ENEMY(KingDux);
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
    TmxEnemyParser::TmxEnemyParser(const s3dTiled::Object& obj) :
        m_obj(obj)
    {}
    std::shared_ptr<EnemyEntity> TmxEnemyParser::parse() const
    {
        auto type = Enum::Parse<EnemyType>(m_obj.getProperty(U"type").value_or(s3d::String(U"None")));

        return Parse(type, m_obj);
    }
}
