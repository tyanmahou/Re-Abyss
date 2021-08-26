#include "TmxGimmickParser.hpp"
#include <abyss/entities/Actor/Gimmick/StartPosEntity.hpp>
#include <abyss/entities/Actor/Gimmick/DoorEntity.hpp>
#include <abyss/entities/Actor/Gimmick/BulletinEntity.hpp>
#include <abyss/entities/Actor/Gimmick/BushEntity.hpp>
#include <abyss/entities/Actor/Gimmick/EventTriggerEntity.hpp>
#include <abyss/entities/Actor/Gimmick/BgmChangerEntity.hpp>

using namespace s3d;
using namespace s3dTiled;
using namespace abyss;
using namespace abyss::Actor::Gimmick;

namespace
{
	GimmickType ToType(const String& type)
	{
		static const std::unordered_map<String, GimmickType> toTypeMap{
			{U"start_pos", GimmickType::StartPos},
			{U"door", GimmickType::Door},
			{U"bulletin", GimmickType::Bulletin},
			{U"bush", GimmickType::Bush},
			{U"event_trigger", GimmickType::EventTrigger},
			{U"bgm_changer", GimmickType::BgmChanger},
		};
		if (toTypeMap.find(type) != toTypeMap.end()) {
			return toTypeMap.at(type);
		}
		return GimmickType::None;
	};

	std::shared_ptr<GimmickEntity> ParseCommon(const std::shared_ptr<GimmickEntity>& entity, const s3dTiled::Object& obj)
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

	std::shared_ptr<GimmickEntity> Parse(GimmickType type, const s3dTiled::Object& obj)
	{
		switch (type) {
			PARSE_GIMMICK(StartPos, {
				it->startId = obj.getProperty(U"start_id").value_or(0);
				it->forward = !obj.isMirrored ? Forward::Right : Forward::Left;
				it->isSave = obj.getProperty(U"is_save").value_or(false);
			});
			PARSE_GIMMICK(Door, {
				it->startId = obj.getProperty(U"start_id").value_or(0);
				it->size = obj.toRectF().size;

				auto kind = obj.getProperty(U"kind").value_or(U"common");
				if (kind == U"boss") {
					it->kind = DoorKind::Boss;
				} else {
					it->kind = DoorKind::Common;
				}
			});
			PARSE_GIMMICK(Bulletin, {
				it->event = obj.getProperty(U"event").value_or(U"");
			});
			PARSE_GIMMICK(Bush, {
				it->kind = Enum::Parse<BushKind>(obj.getProperty(U"kind").value_or(U""));
			});
			PARSE_GIMMICK(EventTrigger, {
				it->event = obj.getProperty(U"event").value_or(U"");
			});
			PARSE_GIMMICK(BgmChanger, {
				it->bgm = obj.getProperty(U"bgm").value_or(U"");
			});
		default:
			break;
		}
		return nullptr;
	}
#undef PARSE_GIMMICK
}
namespace abyss::Actor::Gimmick
{
	TmxGimmickParser::TmxGimmickParser(const s3dTiled::Object& obj) :
		m_obj(obj)
	{}
	std::shared_ptr<GimmickEntity> TmxGimmickParser::parse() const
	{
		auto typeStr = m_obj.getProperty(U"type").value_or(s3d::String(U"none"));
		auto type = ToType(typeStr);

		return Parse(type, m_obj);
	}
}