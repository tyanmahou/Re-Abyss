#pragma once
#include <Siv3D/Array.hpp>
#include <abyss/commons/Fwd.hpp>

namespace abyss::Actor::Gimmick
{
    class IGimmickService
    {
    public:
        virtual ~IGimmickService() = default;
        virtual const s3d::Array<std::shared_ptr<GimmickEntity>>& getGimmicks() const = 0;
    };
}