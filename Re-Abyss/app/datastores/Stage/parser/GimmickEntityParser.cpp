#include "GimmickEntityParser.hpp"
#include <abyss/entities/Actors/Gimmick/StartPosEntity.hpp>
#include <abyss/entities/Actors/Gimmick/DoorEntity.hpp>

using namespace s3d;
using namespace s3dTiled;
using namespace abyss;

namespace
{
	GimmickType ToType(const String& type)
	{
		static const std::unordered_map<String, GimmickType> toTypeMap{
			{U"start_pos", GimmickType::StartPos},
			{U"door", GimmickType::Door},
		};
		if (toTypeMap.find(type) != toTypeMap.end()) {
			return toTypeMap.at(type);
		}
		return GimmickType::None;
	};

	std::shared_ptr<GimmickEntity> ParseCommon(const std::shared_ptr<GimmickEntity>& entity, const s3dTiled::TiledObject& obj)
	{
		if (entity) {
			Vec2 size = obj.toRectF().size;
			entity->pos = obj.pos + Vec2{ size.x / 2, -size.y / 2 };
		}
		return entity;
	}

#define PARSE_GIMMICK(Name, ...) case GimmickType::##Name :\
{\
    auto it = std::make_shared<Name##Entity>();\
    it->type = GimmickType::##Name;\
    __VA_ARGS__\
	return ParseCommon(it, obj);\
}

	std::shared_ptr<GimmickEntity> Parse(GimmickType type, const s3dTiled::TiledObject& obj)
	{
		switch (type) {
			PARSE_GIMMICK(StartPos, {
				it->startId = obj.getProperty(U"start_id").value_or(0);
				it->forward = !obj.isMirrored ? Forward::Right : Forward::Left;
			});
			PARSE_GIMMICK(Door, {
				it->startId = obj.getProperty(U"start_id").value_or(0);
				it->size = obj.toRectF().size;
			});
		default:
			break;
		}
		return nullptr;
	}
#undef PARSE_GIMMICK
}
namespace abyss
{
	TiledGimmickEntityParser::TiledGimmickEntityParser(const s3dTiled::TiledObject& obj) :
		m_obj(obj)
	{}
	std::shared_ptr<GimmickEntity> TiledGimmickEntityParser::parse() const
	{
		auto typeStr = m_obj.getProperty(U"type").value_or(s3d::String(U"none"));
		auto type = ToType(typeStr);

		return Parse(type, m_obj);
	}
}
