#pragma once
#include <functional>
#include <array>
#include <abyss/modules/DrawManager/DrawLayer.hpp>
#include <Siv3D/Array.hpp>

namespace abyss
{
    /// <summary>
    /// 描画単位
    /// </summary>
    struct DrawTarget
    {
        double order = 1.0;
        std::function<void()> drawer;

        auto operator <=> (const DrawTarget& other) const
        {
            return order <=> other.order;
        }
    };

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
        /// <param name="order"></param>
        void add(DrawLayer layer, std::function<void()> drawer, double order = 1.0);

        /// <summary>
        /// 描画
        /// </summary>
        /// <param name="layer"></param>
        void draw(DrawLayer layer);

        /// <summary>
        /// ターゲットの数を取得
        /// </summary>
        /// <param name="layer"></param>
        /// <returns></returns>
        size_t size(DrawLayer layer)const;
    private:
        std::array<s3d::Array<DrawTarget>, DrawLayerSize> m_drawers;
    };
}