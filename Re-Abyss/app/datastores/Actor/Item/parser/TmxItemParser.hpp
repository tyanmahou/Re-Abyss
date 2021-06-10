#pragma once
#include <memory>
#include <abyss/commons/Fwd.hpp>
#include <S3DTiled.hpp>

namespace abyss::Actor::Item
{
    class TmxItemParser
    {
        const s3dTiled::Object& m_obj;
    public:
        TmxItemParser(const s3dTiled::Object& obj);

        std::shared_ptr<ItemEntity> parse() const;
    };
}