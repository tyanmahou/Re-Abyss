#pragma once
#include <memory>
#include <abyss/commons/Fwd.hpp>
#include <S3DTiled.hpp>

namespace abyss
{
    class IGimmickEntityParser
    {
    public:
        virtual std::shared_ptr<GimmickEntity> parse() const = 0;
    };

    class TiledGimmickEntityParser : public IGimmickEntityParser
    {
        const s3dTiled::TiledObject& m_obj;
    public:
        TiledGimmickEntityParser(const s3dTiled::TiledObject&);

        std::shared_ptr<GimmickEntity> parse() const override;
    };
}