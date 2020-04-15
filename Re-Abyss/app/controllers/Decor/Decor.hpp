#pragma once
#include <Siv3D/Array.hpp>
#include <abyss/commons/Fwd.hpp>
#include <map>

namespace abyss
{
    class Decor
    {
        std::map<s3d::int32, s3d::Array<IDecorView>> m_decors;
    public:
        void init(Camera& camera);
    };

    namespace DecorOrder
    {
        inline constexpr s3d::int32 Back = 0;
        inline constexpr s3d::int32 Middle = 1;
        inline constexpr s3d::int32 Front = 2;
    }
}