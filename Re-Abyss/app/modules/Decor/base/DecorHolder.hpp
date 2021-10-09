#pragma once
#include <memory>
#include <Siv3D/Array.hpp>
#include <Siv3D/HashTable.hpp>
#include <abyss/commons/Fwd.hpp>
#include <abyss/entities/Decor/DecorType.hpp>
#include <abyss/modules/Decor/base/BufferLayer.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Decor
{
    using DeployIds = s3d::HashTable<s3d::uint32, Ref<DecorObj>>;

    class DecorHolder
    {
    public:
        void flush();
        void push(const std::shared_ptr<DecorObj>& decor);
        void update();
        void draw() const;

        void erase();

        void clear();
        void clear(BufferLayer layer);

        size_t size() const;

        DeployIds getDeployIds() const;
    private:
        s3d::Array<std::shared_ptr<DecorObj>> m_reserves;
        s3d::Array<std::shared_ptr<DecorObj>> m_decors;
    };
}