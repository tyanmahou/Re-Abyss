#pragma once
#include <memory>
#include <abyss/commons/Fwd.hpp>
#include <S3DTiled.hpp>

namespace abyss::Decor
{
    class TmxDecorParser
    {
        const s3dTiled::TiledObject& m_obj;
    public:
        TmxDecorParser(const s3dTiled::TiledObject& obj);

        std::shared_ptr<DecorEntity> parse() const;
    };
}