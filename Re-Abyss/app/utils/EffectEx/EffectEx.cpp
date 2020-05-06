#include "EffectEx.hpp"
#include <Siv3D.hpp>

namespace abyss
{
    class EffectEx::Impl
    {
    private:
        Array<std::pair<std::unique_ptr<IEffect>, double>> m_effects;

        double m_speed = 1.0;

        bool m_initialized = false;

        bool m_paused = false;

        uint64 m_previousTimeUs = 0;
        TimeGetFunction_t m_timeGetter;
    public:
        struct Null {};

        Impl(TimeGetFunction_t timeGetter):
            m_timeGetter(timeGetter)
        {}

        bool isInitialized() const noexcept
        {
            return m_initialized;
        }

        void add(std::unique_ptr<IEffect>&& effect)
        {
            if (m_paused) {
                return;
            }

            m_effects.emplace_back(std::move(effect), 0);
        }

        size_t num_effects() const
        {
            return m_effects.size();
        }

        void pause()
        {
            m_paused = true;
        }

        bool isPaused() const noexcept
        {
            return m_paused;
        }

        void resume()
        {
            m_paused = false;
        }

        void setSpeed(double speed)
        {
            m_speed = speed;
        }

        double getSpeed() const noexcept
        {
            return m_speed;
        }

        void update()
        {
            const uint64 currentTimeUs = m_timeGetter().count();
            if (m_previousTimeUs == 0) {
                m_previousTimeUs = currentTimeUs;
            }
            const uint64 currentDeltaTimeUs = currentTimeUs - m_previousTimeUs;
            const int64 deltaUs = m_paused ? 0 : static_cast<int64>(currentDeltaTimeUs * m_speed);
            m_previousTimeUs = currentTimeUs;

            double lastDeltaSec = deltaUs / 1'000'000.0;

            for (auto& effect : m_effects) {
                effect.second += lastDeltaSec;
            }
            for (auto it = m_effects.begin(); it != m_effects.end();) {
                const double timeSec = it->second;

                if (timeSec < 0.0) {
                    ++it;

                    continue;
                } else if (it->first->update(timeSec) == false) {
                    it = m_effects.erase(it);
                } else {
                    ++it;
                }
            }
        }

        void clear()
        {
            m_effects.clear();
        }
    };

    EffectEx::EffectEx(TimeGetFunction_t timeGetter):
        m_pImpl(std::make_shared<Impl>(timeGetter))
    {}
    EffectEx::~EffectEx()
    {}
    bool EffectEx::operator==(const EffectEx& effect) const
    {
        return m_pImpl == effect.m_pImpl;
    }
    bool EffectEx::operator!=(const EffectEx& effect) const
    {
        return m_pImpl != effect.m_pImpl;
    }
    EffectEx::operator bool() const
    {
        return hasEffects();
    }
    bool EffectEx::isEmpty() const
    {
        return !hasEffects();
    }
    bool EffectEx::hasEffects() const
    {
        return num_effects() > 0;
    }
    size_t EffectEx::num_effects() const
    {
        return m_pImpl->num_effects();
    }
    void EffectEx::add(std::unique_ptr<IEffect>&& effect) const
    {
        m_pImpl->add(std::move(effect));
    }
    void EffectEx::add(std::function<bool(double)> f) const
    {
        struct AnonymousEffect : IEffect
        {
            std::function<bool(double)> function;

            explicit AnonymousEffect(std::function<bool(double)> _function)
                : function(_function)
            {}

            bool update(double timeSec) override
            {
                return function(timeSec);
            }
        };

        add(std::make_unique<AnonymousEffect>(f));
    }
    void EffectEx::pause() const
    {
        m_pImpl->pause();
    }
    bool EffectEx::isPaused() const
    {
        return m_pImpl->isPaused();
    }
    void EffectEx::resume() const
    {
        m_pImpl->resume();
    }
    void EffectEx::setSpeed(double speed) const
    {
        m_pImpl->setSpeed(speed);
    }
    double EffectEx::getSpeed() const
    {
        return m_pImpl->getSpeed();
    }
    void EffectEx::update() const
    {
        m_pImpl->update();
    }
    void EffectEx::clear() const
    {
        m_pImpl->clear();
    }
}