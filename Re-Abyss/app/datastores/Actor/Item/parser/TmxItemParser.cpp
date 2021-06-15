#include "TmxItemParser.hpp"

#include <abyss/entities/Actor/Item/ItemEntity.hpp>
#include <abyss/entities/Actor/Item/RecoveryEntity.hpp>


namespace
{
	using namespace s3d;
	using namespace s3dTiled;
	using namespace abyss;
	using namespace abyss::Actor::Item;


	ItemType ToType(const String& type)
	{
		static const std::unordered_map<String, ItemType> toTypeMap{
			{U"recovery", ItemType::Recovery},
		};
		if (toTypeMap.find(type) != toTypeMap.end()) {
			return toTypeMap.at(type);
		}
		return ItemType::None;
	};

	RecoveryKind ToRecoveyKind(const String& type)
	{
		static const std::unordered_map<String, RecoveryKind> toTypeMap{
			{U"small", RecoveryKind::Small},
			{U"middle", RecoveryKind::Middle},
			{U"big", RecoveryKind::Big},
		};
		if (toTypeMap.find(type) != toTypeMap.end()) {
			return toTypeMap.at(type);
		}
		return RecoveryKind::Small;
	};

	std::shared_ptr<ItemEntity> ParseCommon(const std::shared_ptr<ItemEntity>& entity, const s3dTiled::Object& obj)
	{
		if (entity) {
			Vec2 size = obj.toRectF().size;
			entity->pos = obj.pos + Vec2{ size.x / 2, -size.y / 2 };
		}
		return entity;
	}

#define PARSE_ITEM(Name, ...) case ItemType::##Name :\
{\
    auto it = std::make_shared<Name##Entity>();\
    it->type = ItemType::##Name;\
    __VA_ARGS__\
	return ParseCommon(it, obj);\
}

	std::shared_ptr<ItemEntity> Parse(ItemType type, const s3dTiled::Object& obj)
	{
		switch (type) {
			PARSE_ITEM(Recovery, {
				it->kind = ToRecoveyKind(obj.getProperty(U"kind").value_or(U"small"));
			});
		default:
			break;
		}
		return nullptr;
	}
#undef PARSE_ITEM
}

namespace abyss::Actor::Item
{
    TmxItemParser::TmxItemParser(const s3dTiled::Object& obj):
        m_obj(obj)
    {}

    std::shared_ptr<ItemEntity> TmxItemParser::parse() const
    {
        auto typeStr = m_obj.getProperty(U"type").value_or(s3d::String(U"none"));
        auto type = ToType(typeStr);

        return Parse(type, m_obj);
    }
}
