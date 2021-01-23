#pragma once
#include <Siv3D/String.hpp>

namespace abyss::Tips
{
    class TipsView
    {
    public:
        static void DrawFooter(s3d::StringView message);
    };
}