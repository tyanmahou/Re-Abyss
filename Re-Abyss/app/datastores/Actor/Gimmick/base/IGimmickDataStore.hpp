#pragma once
#include <memory>
#include <Siv3D/Array.hpp>
#include <abyss/entities/Actor/Gimmick/GimmickEntity.hpp>
namespace abyss
{
    class IGimmickDataStore
    {
    public:
        virtual ~IGimmickDataStore() = default;

        virtual s3d::Array<std::shared_ptr<GimmickEntity>> select()const = 0;
    };
}