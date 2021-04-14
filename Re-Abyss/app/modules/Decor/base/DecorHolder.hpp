#pragma once
#include <memory>
#include <Siv3D/Array.hpp>
#include <abyss/commons/Fwd.hpp>

namespace abyss::decor
{
    class DecorHolder
    {
    public:
        void flush();
        void push(const std::shared_ptr<DecorObj>& decor);
        void update();
        void draw() const;

        void erase();

        void clear();

        size_t size() const;
    private:
        s3d::Array<std::shared_ptr<DecorObj>> m_reserves;
        s3d::Array<std::shared_ptr<DecorObj>> m_decors;
    };
}