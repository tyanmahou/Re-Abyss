#pragma once
#include <abyss/commons/Fwd.hpp>
#include <Siv3D/Fwd.hpp>

namespace abyss::DecorBuildUtil
{
    /// <summary>
    /// RectFに変換
    /// </summary>
    s3d::RectF ToRect(const decor::DecorEntity& entity);

    /// <summary>
    /// Quadに変換
    /// </summary>
    s3d::Quad ToQuad(const decor::DecorEntity& entity);

    /// <summary>
    /// スクリーンに入っているか
    /// </summary>
    bool IsInScreen(const decor::DecorEntity& entity, const s3d::RectF& screen);
}