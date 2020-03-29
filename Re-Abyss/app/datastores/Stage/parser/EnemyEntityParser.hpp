#pragma once
#include <memory>
#include <abyss/commons/Fwd.hpp>
#include <S3DTiled.hpp>

namespace abyss
{
    class IEnemyEntityParser
    {
    public:
        virtual std::shared_ptr<EnemyEntity> parse() const = 0;
    };

    class TiledEnemyEntityParser : public IEnemyEntityParser
    {
        const s3dTiled::TiledObject& m_obj;
    public:
        TiledEnemyEntityParser(const s3dTiled::TiledObject&);

        std::shared_ptr<EnemyEntity> parse() const override;
    };
}