#pragma once
#include <Siv3D/Effect.hpp>
namespace abyss::Actor::Ooparts
{
    class IDrawCallbackView
    {
    public:
        virtual ~IDrawCallbackView() = default;

        template<class EffectType, class... Args>
        void onAddEffect(Args&&... args) const
        {
            onAddEffect(std::make_unique<EffectType>(std::forward<Args>(args)...));
        }
        virtual void onAddEffect(std::unique_ptr<s3d::IEffect>&& effect) const = 0;
    };
}