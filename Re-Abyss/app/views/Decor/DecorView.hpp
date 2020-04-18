#pragma once
#include <memory>
#include <Siv3D/Array.hpp>
#include <Siv3D/HashTable.hpp>
#include <abyss/commons/Fwd.hpp>

namespace abyss
{
    class DecorView
    {
        s3d::HashTable<s3d::int32, s3d::Array<std::shared_ptr<IDecorVM>>> m_decors;
    public:
        void add(s3d::int32 order, const std::shared_ptr<IDecorVM>& vm);
        void clear();

        void draw(s3d::int32 order, const s3d::RectF& screen) const;
    };
}