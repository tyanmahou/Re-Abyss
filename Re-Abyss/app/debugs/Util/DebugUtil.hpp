#pragma once

#if ABYSS_DEBUG
#include <Siv3D/Fwd.hpp>
#include <abyss/commons/Fwd.hpp>

namespace abyss::Debug::DebugUtil
{
    void DrawShape(const CShape& shape, const s3d::ColorF& color);
}

#endif