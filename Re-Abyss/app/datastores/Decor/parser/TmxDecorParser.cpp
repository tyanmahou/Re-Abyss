#include "TmxDecorParser.hpp"
#include <abyss/entities/Decor/DecorEntity.hpp>
#include <abyss/entities/Decor/General/CommonEntity.hpp>
#include <abyss/entities/Decor/City/StreetLightEntity.hpp>
#include <abyss/entities/Decor/Gimmick/DoorEntity.hpp>
#include <abyss/entities/Decor/Map/CommonEntity.hpp>
#include <abyss/utils/Overloaded.hpp>
#include <Siv3D.hpp>

namespace
{
    using namespace abyss::Decor;

    DecorType ToType(const String& category, const String& type)
    {
        if (category == U"general") {
            static const std::unordered_map<String, DecorType> toTypeMap{
                {U"none", DecorType::General::None},
                {U"common", DecorType::General::Common},
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
        }
        return DecorType::General::None;
    };

    std::shared_ptr<DecorEntity> ParseCommon(const std::shared_ptr<DecorEntity>& entity, const s3dTiled::Object& obj)
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
            using namespace abyss::Decor::##category;\
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

    std::shared_ptr<DecorEntity> Parse(const DecorType& type, const s3dTiled::Object& obj)
    {
        auto general = PARSE_CAREGORY(General,
            PARSE_TYPE(Common);
        );

        auto city = PARSE_CAREGORY(City,
            PARSE_TYPE(StreetLight);
        );

        auto visiter = abyss::overloaded{
            general,
            city,
            [](auto) -> std::shared_ptr<DecorEntity>{
                return nullptr;
            }
        };
        return type.visit(visiter);
    }
#undef PARSE_TYPE
#undef PARSE_CATEGORY
}
namespace abyss::Decor
{
    TmxDecorParser::TmxDecorParser(const s3dTiled::Object& obj) :
        m_obj(obj)
    {}

    std::shared_ptr<DecorEntity> TmxDecorParser::parse() const
    {
        auto categoryStr = m_obj.getProperty(U"category").value_or(s3d::String(U"general"));
        auto typeStr = m_obj.getProperty(U"type").value_or(s3d::String(U"common"));
        auto type = ToType(categoryStr, typeStr);

        return Parse(type, m_obj);
    }
}
