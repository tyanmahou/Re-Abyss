#include <abyss/components/Actor/Ooparts/KiraKiraAlgorithm.hpp>

#include <abyss/modules/Effect/Effects.hpp>
#include <abyss/components/Effect/Actor/Ooparts/Common/KiraKira/Builder.hpp>
#include <Siv3D.hpp>
namespace abyss::Actor::Ooparts
{
    KiraKiraAlgorithm::KiraKiraAlgorithm(Effects* effects, DrawLayer layer):
        m_effects(effects),
        m_layer(layer),
        m_intervalTimer(0.05)
    {}
    void KiraKiraAlgorithm::update(const s3d::Vec2 & pos, double dt, std::function<void(Effect::EffectObj*)> callback)
    {
        using namespace Effect::Actor::Ooparts;

        m_intervalTimer.update(dt).each([&](double) {
            auto obj = m_effects->create(m_layer);
            if (RandomBool(0.7)) {
                KiraKira::Builder::Build(obj.get(), pos + RandomVec2({ -15, 15 }, { 0, 20 }));
            } else {
                KiraKira::Builder::Build(obj.get(), pos + RandomVec2(17), KiraKira::Type::Type2);
            }
            if (callback) {
                callback(obj.get());
            }
        });
    }
}
