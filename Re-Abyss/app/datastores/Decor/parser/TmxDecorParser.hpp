#pragma once
#include <memory>
#include <abyss/commons/Fwd.hpp>
#include <S3DTiled.hpp>

namespace abyss::Decor
{
    class TmxDecorParser
    {
        const s3dTiled::Object& m_obj;
    public:
        TmxDecorParser(const s3dTiled::Object& obj);

        std::shared_ptr<DecorEntity> parse() const;
    };
}