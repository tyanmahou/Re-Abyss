#include "TmxDecorParser.hpp"
#include <abyss/entities/Decor/DecorEntity.hpp>
#include <abyss/entities/Decor/General/CommonEntity.hpp>
#include <abyss/entities/Decor/General/SchoolOfFishEntity.hpp>
#include <abyss/entities/Decor/City/StreetLightEntity.hpp>
#include <abyss/entities/Decor/Gimmick/DoorEntity.hpp>
#include <abyss/entities/Decor/Map/CommonEntity.hpp>
#include <abyss/utils/Overloaded.hpp>
#include <Siv3D.hpp>

namespace
{
    using namespace abyss::Decor;

    DecorType ToType(DecorType::Motif motif, const String& type)
    {
        return DecorType::IndexVisit([&] <class MotifType>()->DecorType
        {
            if constexpr (!std::is_void_v<MotifType>) {
                if (auto kind = Enum::Parse<MotifType>(type); kind != MotifType::None) {
                    return kind;
                }
            }
            return DecorType::General::None;
        }, static_cast<size_t>(motif));
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

#define PARSE_MOTIF(motif, ...) [&](DecorType::##motif c) -> std::shared_ptr<DecorEntity> {\
            using enum DecorType::##motif;\
            using namespace abyss::Decor::##motif;\
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
    ParseCommon(it, obj);\
    it->type = type;\
    __VA_ARGS__\
	return it;\
}

    std::shared_ptr<DecorEntity> Parse(const DecorType& type, const s3dTiled::Object& obj)
    {
        auto general = PARSE_MOTIF(General,
            PARSE_TYPE(Common);
            PARSE_TYPE(SchoolOfFish, {
                it->matrixSize = s3d::Size{
                    obj.getProperty(U"column").value_or(64).toInt(),
                    obj.getProperty(U"row").value_or(8).toInt()
                };
                it->speed = obj.getProperty(U"speed").value_or(175.0);
                it->heightOffset = obj.getProperty(U"height_offset").value_or(180.0);
                it->amplitude = obj.getProperty(U"amplitude").value_or(40.0);
                it->scale = obj.getProperty(U"scale").value_or(1.0);
                it->size.x = 90.0 * it->matrixSize.x + 100.0;
                it->size.y = 9.0 * it->matrixSize.y + it->heightOffset + it->amplitude * 2 + 100.0;
                it->size *= it->scale;
            });
        );

        auto city = PARSE_MOTIF(City,
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
#undef PARSE_MOTIF
}
namespace abyss::Decor
{
    TmxDecorParser::TmxDecorParser(const s3dTiled::Object& obj) :
        m_obj(obj)
    {}

    std::shared_ptr<DecorEntity> TmxDecorParser::parse() const
    {
        auto motif = Enum::Parse<DecorType::Motif>(m_obj.getProperty(U"motif").value_or(s3d::String(U"General")));
        auto typeStr = m_obj.getProperty(U"type").value_or(s3d::String(U"Common"));
        auto type = ToType(motif, typeStr);

        return Parse(type, m_obj);
    }
}
