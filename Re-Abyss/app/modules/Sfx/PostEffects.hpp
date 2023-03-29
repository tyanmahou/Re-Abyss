#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/Sfx/Moisture/Moisture.hpp>
#include <abyss/modules/Sfx/Bloom/Bloom.hpp>
#include <abyss/modules/Sfx/Blur/Blur.hpp>
#include <abyss/modules/Sfx/DecorFar/DecorFar.hpp>
#include <abyss/modules/Sfx/DeadEffect/DeadEffect.hpp>
#include <abyss/modules/Sfx/NegaPosiInv/NegaPosiInv.hpp>
#include <abyss/modules/Sfx/Scanline/Scanline.hpp>

namespace abyss::Sfx
{
    struct PostEffectsDesc
    {
        constexpr static PostEffectsDesc CreateDefault()
        {
            return {
                .useScanline = true
            };
        }
        constexpr static PostEffectsDesc CreateTitle()
        {
            return {
                .useDecorFar = true,
                .useScanline = true
            };
        }
        constexpr static PostEffectsDesc CreateStage()
        {
            return {
                .useDecorFar = true,
                .useBloom = true,
                .useMoisture = true,
                .useBlur = true,
                .useDeadEffect = true,
                .useNegaPosiInv = true,
                .useScanline = true
            };
        }
        bool useDecorFar = false;
        bool useBloom = false;
        bool useMoisture = false;
        bool useBlur = false;
        bool useDeadEffect = false;
        bool useNegaPosiInv = false;
        bool useScanline = false;
    };

    /// <summary>
    /// ポストエフェクト
    /// </summary>
    class PostEffects
    {
    public:
        PostEffects(const PostEffectsDesc& desc);
        void setManager(Manager* pManager);
        void update(double dt);

        DecorFar* getDecorFar() const;
        Bloom* getBloom() const;
        Moisture* getMoisture() const;
        Blur* getBlur() const;
        DeadEffect* getDeadEffect() const;
        NegaPosiInv* getNegaPosiInv() const;
        Scanline* getScanline() const;
    private:
        Manager* m_pManager;
        std::unique_ptr<DecorFar> m_decorFar;
        std::unique_ptr<Bloom> m_bloom;
        std::unique_ptr<Moisture> m_moisture;
        std::unique_ptr<Blur> m_blur;
        std::unique_ptr<DeadEffect> m_deadEffect;
        std::unique_ptr<NegaPosiInv> m_negaPosiInv;
        std::unique_ptr<Scanline> m_scanline;
    };
}
