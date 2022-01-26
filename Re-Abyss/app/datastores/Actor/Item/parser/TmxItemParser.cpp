#include <abyss/datastores/Actor/Item/parser/TmxItemParser.hpp>

#include <abyss/entities/Actor/Item/ItemEntity.hpp>
#include <abyss/entities/Actor/Item/RecoveryEntity.hpp>
#include <abyss/utils/Enum/EnumTraits.hpp>

namespace
{
	using namespace s3d;
	using namespace s3dTiled;
	using namespace abyss;
	using namespace abyss::Actor::Item;

	std::shared_ptr<ItemEntity> ParseCommon(const std::shared_ptr<ItemEntity>& entity, const s3dTiled::Object& obj)
	{
		if (entity) {
			entity->id = obj.id;

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
				it->kind = Enum::Parse<RecoveryKind>(obj.getProperty(U"kind").value_or(U"Small"));
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
        auto type = Enum::Parse<ItemType>(m_obj.getProperty(U"type").value_or(s3d::String(U"None")));

        return Parse(type, m_obj);
    }
}
