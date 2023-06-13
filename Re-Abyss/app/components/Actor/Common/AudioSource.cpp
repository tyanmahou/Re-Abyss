#include <abyss/components/Actor/Common/AudioSource.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <abyss/modules/Actor/base/ActorObj.hpp>

#include <abyss/modules/Actor/base/IUpdate.hpp>
#include <abyss/components/Actor/Common/Body.hpp>
#include <abyss/components/Actor/Common/Locator.hpp>
#include <abyss/components/Actor/utils/ActorUtils.hpp>

#include <abyss/modules/Manager/Manager.hpp>
#include <abyss/modules/Actor/Actors.hpp>
#include <abyss/modules/Sound/MixBus.hpp>
#include <abyss/commons/Constants.hpp>

#include <Siv3D.hpp>
namespace
{
    constexpr s3d::FilePathView ActorSePathPrefix = U"se/Actor/";

    using namespace abyss;
    using namespace abyss::Actor;
    std::pair<double, double> CalcVolume(const s3d::Vec2& pos, const s3d::Vec2& listener)
    {
        const Vec3 listenerPos(listener, 333);
        const double volume = Pow(1 / Vec3(pos, 0).distanceFrom(listenerPos) * 300, 2);

        // 左右で音量を変える
        auto xDiff = pos.x - listener.x;
        auto panRate = Min(1.0, Abs(xDiff) / (Constants::GameScreenSize.x * 0.9));
        panRate *= s3d::Math::Sign(xDiff);
        return {
            volume,
            panRate
        };
    }

    class TemporarySoundEffect :
        public IComponent,
        public IUpdate
    {
    public:
        TemporarySoundEffect(ActorObj* pActor, const s3d::Audio& audio) :
            m_pActor(pActor),
            m_audio(audio)
        {}

        void onStart() override
        {
            m_locator = m_pActor->find<Locator>();
            m_audio.play(Sound::MixBusKind::Se);
        }

        void onUpdate() override
        {
            if (!m_audio.isPlaying()) {
                m_pActor->destroy();
            }
            const auto& pos = m_locator->getPos();
            const auto& listener = ActorUtils::PlayerPos(*m_pActor);

            auto [volume, pan] = ::CalcVolume(pos, listener);
            m_audio.setVolume(volume);
            m_audio.setPan(pan);
        }
    private:
        Ref<Locator> m_locator;
        ActorObj* m_pActor;
        Audio m_audio;
    };
}
namespace abyss
{
    template<>
    struct ComponentTree<TemporarySoundEffect>
    {
        using Base = IUpdate;
    };
}
namespace abyss::Actor
{
    AudioSource::AudioSource(ActorObj* pActor) :
        m_pActor(pActor)
    {}

    void AudioSource::onStart()
    {
        if (auto body = m_pActor->find<Body>()) {
            m_locator = RefCast<ILocator>(body);
        } else {
            m_locator = m_pActor->find<ILocator>();
        }
    }
    void AudioSource::onUpdate()
    {
        m_audios.remove_if([](const Audio& audio) {
            return !audio.isPlaying();
        });
        const auto pos = m_locator->getCenterPos();
        const auto& listener = ActorUtils::PlayerPos(*m_pActor);

        for (auto&& audio : m_audios) {
            auto [volume, pan] = ::CalcVolume(pos, listener);
            audio.setVolume(volume);
            audio.setPan(pan);
        }

    }

    void AudioSource::play(const s3d::String& key)
    {
        // TODO Bank経由にする
        //auto as = m_audioSettingGroup(key);
        //if (Audio audio = Resource::Assets::Main()->loadAudio(as)) {
        //    this->playDirect(audio);
        //}
    }

    void AudioSource::playAt(const s3d::String& key) const
    {
        const auto pos = m_locator->getCenterPos();
        this->playAt(key, pos);
    }

    void AudioSource::playAt(const s3d::String & key, const s3d::Vec2 & pos) const
    {
        // TODO Bank経由にする
        //auto as = m_audioSettingGroup(key);
        //if (Audio audio = Resource::Assets::Main()->loadAudio(as)) {
        //    this->playAtDirect(audio, pos);
        //}
    }
    void AudioSource::playDirect(s3d::FilePathView path)
    {
        if (Audio audio = Resource::Assets::Main()->load(ActorSePathPrefix + path)) {
            this->playDirect(audio);
        }
    }
    void AudioSource::playDirect(const s3d::Audio& audio)
    {
        const auto pos = m_locator->getCenterPos();
        const auto& listener = ActorUtils::PlayerPos(*m_pActor);

        auto [volume, pan] = ::CalcVolume(pos, listener);
        audio.setVolume(volume);
        audio.setPan(pan);
        audio.play(Sound::MixBusKind::Se);
        m_audios.push_back(audio);
    }
    void AudioSource::playAtDirect(s3d::FilePathView path) const
    {
        const auto pos = m_locator->getCenterPos();
        this->playAtDirect(path, pos);
    }
    void AudioSource::playAtDirect(s3d::FilePathView path, const s3d::Vec2 & pos) const
    {
        if (Audio audio = Resource::Assets::Main()->load(ActorSePathPrefix + path)) {
            this->playAtDirect(audio, pos);
        }
    }
    void AudioSource::playAtDirect(const s3d::Audio & audio) const
    {
        const auto pos = m_locator->getCenterPos();
        this->playAtDirect(audio, pos);
    }
    void AudioSource::playAtDirect(const s3d::Audio & audio, const s3d::Vec2 & pos) const
    {
        auto pActor = m_pActor->getModule<Actors>()->create();
        auto raw = pActor.get();
        raw->setDestoryTiming(DestoryTiming::Never);
        raw->attach<Locator>()->setPos(pos);
        raw->attach<TemporarySoundEffect>(raw, audio);
    }
}
