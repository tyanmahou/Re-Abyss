#pragma once
#include <functional>
#include <array>
#include <abyss/modules/DrawManager/DrawLayer.hpp>
#include <Siv3D/Array.hpp>

namespace abyss
{
    /// <summary>
    /// 描画マネージャー
    /// 描画順の制御用
    /// </summary>
    class DrawManager
    {
    public:
        /// <summary>
        /// クリアする
        /// </summary>
        void clear();

        /// <summary>
        /// 描画ターゲットを追加する
        /// </summary>
        /// <param name="layer"></param>
        /// <param name="drawer"></param>
        void add(DrawLayer layer, std::function<void()> drawer);

        /// <summary>
        /// 描画
        /// </summary>
        /// <param name="layer"></param>
        void draw(DrawLayer layer) const;
    private:
        std::array<s3d::Array<std::function<void()>>, DrawLayerSize> m_drawers;
    };
}