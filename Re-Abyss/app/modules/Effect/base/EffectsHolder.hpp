#pragma once
#include <memory>

#include <Siv3D/Array.hpp>
#include <Siv3D/Fwd.hpp>

#include <abyss/commons/Fwd.hpp>

namespace abyss::Effect
{
    class EffectsHolder
    {
    public:
        void flush();
        void push(const std::shared_ptr<EffectObj>& effect);
        void updateDeltaTime(double dt);
        void update();
        void draw() const;

        void erase();

        void clear();

        size_t size() const;
    private:
        s3d::Array<std::shared_ptr<EffectObj>> m_reserves;
        s3d::Array<std::shared_ptr<EffectObj>> m_effects;
    };
}