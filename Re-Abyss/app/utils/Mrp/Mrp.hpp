#pragma once
#include <Siv3D/Array.hpp>
#include <Siv3D/HashTable.hpp>
#include <Siv3D/String.hpp>

namespace Mrp
{
    using MrpGroup = s3d::Array<std::pair<s3d::String, s3d::String>>;

    class Mrp
    {
        class Impl;
    public:
        using container_type = s3d::HashTable<s3d::String, MrpGroup>;
    public:
        Mrp() = default;

        Mrp(s3d::FilePathView path);

        explicit operator bool() const;

        container_type::const_iterator begin() const;
        container_type::const_iterator end() const;
    private:
        std::shared_ptr<Impl> m_pImpl;
    };
}