#pragma once
#include <abyss/concepts/Effect.hpp>
#include <abyss/modules/Effect/base/EffectsHolder.hpp>
#include <abyss/modules/DrawManager/DrawLayer.hpp>
#include <abyss/utils/Ref/Ref.hpp>
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

    public:
        /// <summary>
        /// エフェクトの生成
        /// </summary>
        /// <returns></returns>
        Ref<EffectObj> create(DrawLayer layer);

        /// <summary>
        /// ビルダーからエフェクトの生成
        /// </summary>
        template<class BuilerType, DrawLayer layer, class... Args>
        Ref<EffectObj> create(Args&& ... args)
            requires EffectBuildy<BuilerType, Args...>
        {
            auto obj = this->create(layer);
            BuilerType::Build(obj.get(), std::forward<Args>(args)...);
            return obj;
        }

        /// <summary>
        /// Sivエフェクトの生成
        /// </summary>
        template<class Type, DrawLayer layer, class... Args>
        Ref<EffectObj> create(Args&& ... args)
            requires DerviedFromSivEffect<Type>
        {
            return this->regist(std::make_unique<Type>(std::forward<Args>(args)...), layer);
        }

#define MAKE_LAYER_CREATE(layer) template<class Type, class... Args> \
        Ref<EffectObj> create##layer(Args&& ... args) \
        {\
            return this->create<Type, DrawLayer::layer, Args...>(std::forward<Args>(args)...);\
        }

        MAKE_LAYER_CREATE(DecorBack)
        MAKE_LAYER_CREATE(WorldBack)
        MAKE_LAYER_CREATE(WorldFront)
        MAKE_LAYER_CREATE(DecorFront)

#undef MAKE_LAYER_CREATE

        ///         /// <summary>
        /// エフェクトを登録
        /// </summary>
        Ref<EffectObj> regist(const std::shared_ptr<EffectObj>& effect);

        /// <summary>
        /// Sivエフェクトを登録
        /// </summary>
        Ref<EffectObj> regist(std::unique_ptr<s3d::IEffect>&& effect, DrawLayer layer);
    private:
        EffectsHolder m_effects;
        Manager* m_pManager = nullptr;
    };
}