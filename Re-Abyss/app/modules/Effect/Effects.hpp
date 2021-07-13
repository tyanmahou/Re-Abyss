#pragma once
#include <abyss/modules/Effect/base/EffectsHolder.hpp>
#include <Siv3D/Effect.hpp>

namespace abyss::Effect
{
    /// <summary>
    /// エフェクト
    /// </summary>
    class Effects
    {
    public:
        Effects() = default;

        Effects& setManager(Manager* pManager)
        {
            m_pManager = pManager;
            return *this;
        }
        
        /// <summary>
        /// 更新
        /// </summary>
        void updateAll(double dt);

        /// <summary>
        /// 描画
        /// </summary>
        void draw() const;

        /// <summary>
        /// エフェクト数
        /// </summary>
        /// <returns></returns>
        size_t size() const;

        void clear();
    private:
        EffectsHolder m_effects;
        Manager* m_pManager = nullptr;
    };
}