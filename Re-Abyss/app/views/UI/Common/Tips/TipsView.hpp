#pragma once
#include <Siv3D/String.hpp>

namespace abyss::UI
{
    class TipsView
    {
    public:
        static void DrawFooter(s3d::StringView message, double rate = 1.0);
    };
}
