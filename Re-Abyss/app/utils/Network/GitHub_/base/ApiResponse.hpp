#pragma once
#include <expected>
#include <Siv3D/Types.hpp>

namespace abyss::Network::GitHub
{
    template<class T>
    using ApiResponse = std::expected<T, s3d::int32>;
}
