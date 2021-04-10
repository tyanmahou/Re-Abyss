#include "TmxDecorParser.hpp"
#include <abyss/entities/Decor/DecorEntity.hpp>
#include <abyss/entities/Decor/Common/CommonEntity.hpp>
#include <abyss/entities/Decor/City/StreetLightEntity.hpp>
#include <abyss/entities/Decor/Gimmick/DoorEntity.hpp>
#include <abyss/entities/Decor/Map/CommonEntity.hpp>
#include <abyss/utils/Overloaded.hpp>
#include <Siv3D.hpp>

namespace
{
    using namespace abyss::decor;

    DecorType ToType(const String& category, const String& type)
    {
        if (category == U"common") {
            static const std::unordered_map<String, DecorType> toTypeMap{
                {U"none", DecorType::Common::None},
                {U"common", DecorType::Common::Common},
            };
            if (toTypeMap.find(type) != toTypeMap.end()) {
                return toTypeMap.at(type);
            }
        } else if (category == U"city") {
            static const std::unordered_map<String, DecorType> toTypeMap{
                {U"street_light", DecorType::City::StreetLight},
            };
            if (toTypeMap.find(type) != toTypeMap.end()) {
                return toTypeMap.at(type);
            }
        } else if (category == U"gimmick") {
            static const std::unordered_map<String, DecorType> toTypeMap{
                {U"door", DecorType::Gimmick::Door},
            };
            if (toTypeMap.find(type) != toTypeMap.end()) {
                return toTypeMap.at(type);
            }
        } else if (category == U"map") {
            static const std::unordered_map<String, DecorType> toTypeMap{
                {U"common", DecorType::Map::Common},
            };
            if (toTypeMap.find(type) != toTypeMap.end()) {
                return toTypeMap.at(type);
            }
        }
        return DecorType::Common::None;
    };

    std::shared_ptr<DecorEntity> ParseCommon(const std::shared_ptr<DecorEntity>& entity, const s3dTiled::TiledObject& obj)
    {
        if (entity) {
            auto size = obj.toRectF().size;
            auto pos = obj.pos + s3d::Vec2{ size.x / 2, -size.y / 2 };

            entity->id = obj.id;
            entity->gId = obj.gId.value_or(0);
            entity->pos = pos;
            entity->size = size;
            entity->rotation = obj.rotation;
            entity->isMirrored = obj.isMirrored;
            entity->isFlipped = obj.isFliped;
        }
        return entity;
    }

#define PARSE_CAREGORY(category, ...) [&](DecorType::##category c) -> std::shared_ptr<DecorEntity> {\
            using enum DecorType::##category;\
            using namespace abyss::decor::##category;\
            switch(c){\
            __VA_ARGS__ \
            default: \
                break; \
            }\
            return nullptr;\
        }
#define PARSE_TYPE(Name, ...) case Name :\
{\
    auto it = std::make_shared<Name##Entity>();\
    it->type = type;\
    __VA_ARGS__\
	return ParseCommon(it, obj);\
}

    std::shared_ptr<DecorEntity> Parse(const DecorType& type, const s3dTiled::TiledObject& obj)
    {
        auto common = PARSE_CAREGORY(Common,
            PARSE_TYPE(Common);
        );

        auto city = PARSE_CAREGORY(City,
            PARSE_TYPE(StreetLight);
        );
        auto gimmick = PARSE_CAREGORY(Gimmick,
            PARSE_TYPE(Door);
        );
        auto map = PARSE_CAREGORY(Map,
            PARSE_TYPE(Common);
        );

        auto visiter = abyss::overloaded{
            common,
            city,
            gimmick,
            map,
            [](auto) -> std::shared_ptr<DecorEntity>{
                return nullptr;
            }
        };
        return type.visit(visiter);
    }
#undef PARSE_TYPE
#undef PARSE_CATEGORY
}
namespace abyss::decor
{
    TmxDecorParser::TmxDecorParser(const s3dTiled::TiledObject& obj) :
        m_obj(obj)
    {}

    std::shared_ptr<DecorEntity> TmxDecorParser::parse() const
    {
        auto categoryStr = m_obj.getProperty(U"category").value_or(s3d::String(U"common"));
        auto typeStr = m_obj.getProperty(U"type").value_or(s3d::String(U"none"));
        auto type = ToType(categoryStr, typeStr);

        return Parse(type, m_obj);
    }
}
