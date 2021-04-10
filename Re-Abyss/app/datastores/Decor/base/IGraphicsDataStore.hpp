#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/entities/Decor/GraphicsEntity.hpp>
#include <Siv3D/Array.hpp>
#include <Siv3D/HashTable.hpp>
namespace abyss::decor
{
    class IGraphicsDataStore
    {
    public:
        virtual ~IGraphicsDataStore() = default;

        virtual s3d::Array<GraphicsEntity> select()const = 0;
        s3d::HashTable<s3d::uint32, GraphicsEntity> selectWithKey() const;
    };
}