#pragma once
#include <memory>
#include <abyss/commons/Fwd.hpp>
#include <S3DTiled.hpp>

namespace abyss::Actor::Gimmick
{
    class TmxGimmickParser
    {
        const s3dTiled::Object& m_obj;
    public:
        TmxGimmickParser(const s3dTiled::Object&);

        std::shared_ptr<GimmickEntity> parse() const;
    };
}