#pragma once
#include <memory>
#include <abyss/commons/Fwd.hpp>
#include <S3DTiled.hpp>

namespace abyss::Actor::Enemy
{
    class TmxEnemyParser
    {
        const s3dTiled::Object& m_obj;
    public:
        TmxEnemyParser(const s3dTiled::Object&);

        std::shared_ptr<EnemyEntity> parse() const;
    };
}