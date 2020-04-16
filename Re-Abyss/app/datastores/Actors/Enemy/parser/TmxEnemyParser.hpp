#pragma once
#include <memory>
#include <abyss/commons/Fwd.hpp>
#include <S3DTiled.hpp>

namespace abyss
{
    class TmxEnemyParser
    {
        const s3dTiled::TiledObject& m_obj;
    public:
        TmxEnemyParser(const s3dTiled::TiledObject&);

        std::shared_ptr<EnemyEntity> parse() const;
    };
}