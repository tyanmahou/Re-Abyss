#include "AudioSource.hpp"
#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <abyss/modules/Actor/base/ActorObj.hpp>

#include <abyss/components/Actor/base/IUpdate.hpp>
#include <abyss/components/Actor/Common/Body.hpp>
#include <abyss/components/Actor/utils/ActorUtils.hpp>

#include <abyss/modules/Manager/Manager.hpp>
#include <abyss/modules/World/World.hpp>
#include <abyss/commons/Constants.hpp>

#include <Siv3D.hpp>

namespace
{
    using namespace abyss;
    using namespace abyss::Actor;
    std::pair<double, double> CalcVolume(const s3d::Vec2& pos, const s3d::Vec2& listener)
    {
        const Vec3 listenerPos(listener, 333);
        const double volume = Pow(1 / Vec3(pos, 0).distanceFrom(listenerPos) * 300, 2);

        // 左右で音量を変える
        auto xDiff = pos.x - listener.x;
        auto rate = 1 - Min(1.0, Abs(xDiff) / (Constants::GameScreenSize.x * 0.9));
        return {
            volume * (xDiff > 0 ? rate : 1.0),
            volume * (xDiff < 0 ? rate : 1.0)
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
            m_body = m_pActor->find<Body>();
            m_audio.play();
        }

        void onUpdate() override
        {
            if (!m_audio.isPlaying()) {
                m_pActor->destroy();
            }
            const auto& pos = m_body->getPos();
            const auto& listener = ActorUtils::PlayerPos(*m_pActor);

            auto volume = ::CalcVolume(pos, listener);
            // TODO 後で確認
            //m_audio.setVolumeLR(volume.first, volume.second);
        }
    private:
        Ref<Body> m_body;
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
        m_body = m_pActor->find<Body>();
    }

    void AudioSource::load(const s3d::FilePath& path)
    {
        m_audioSettingGroup = Resource::Assets::Main()->load(U"se/Actors/" + path);
    }

    void AudioSource::onUpdate()
    {
        m_audios.remove_if([](const Audio& audio) {
            return !audio.isPlaying();
        });
        const auto& pos = m_body->getPos();
        const auto& listener = ActorUtils::PlayerPos(*m_pActor);

        for (auto&& audio : m_audios) {
            auto volume = ::CalcVolume(pos, listener);
            // TODO 後で確認
            // audio.setVolumeLR(volume.first, volume.second);
        }

    }

    void AudioSource::play(const s3d::String& key)
    {
        // TODO 後で確認
        //auto as = m_audioSettingGroup(key);
        //if (Audio baseAudio = Resource::Assets::Main()->load(as.path, Path::Root)) {
        //    Audio audio(baseAudio.getWave());
        //    as.apply(audio);
        //    this->playDirect(audio);
        //}
    }

    void AudioSource::playAt(const s3d::String& key) const
    {
        const auto& pos = m_body->getPos();
        this->playAt(key, pos);
    }

    void AudioSource::playAt(const s3d::String & key, const s3d::Vec2 & pos) const
    {
        // TODO 後で確認
        //auto as = m_audioSettingGroup(key);
        //if (Audio baseAudio = Resource::Assets::Main()->load(as.path, Path::Root)) {
        //    Audio audio(baseAudio.getWave());
        //    as.apply(audio);
        //    this->playAtDirect(audio, pos);
        //}
    }
    void AudioSource::playDirect(s3d::FilePathView path)
    {
        // TODO 後で確認
        //if (Audio baseAudio = Resource::Assets::Main()->load(U"se/Actors/" + path)) {
        //    Audio audio(baseAudio.getWave());
        //    if (auto loop = baseAudio.getLoop()) {
        //        audio.setLoop(loop->beginPos, loop->endPos);
        //    }
        //    this->playDirect(audio);
        //}
    }
    void AudioSource::playDirect(const s3d::Audio& audio)
    {
        const auto& pos = m_body->getPos();
        const auto& listener = ActorUtils::PlayerPos(*m_pActor);

        auto volume = ::CalcVolume(pos, listener);
        // TODO 後で確認
        // audio.setVolumeLR(volume.first, volume.second);
        audio.play();
        m_audios.push_back(audio);
    }
    void AudioSource::playAtDirect(s3d::FilePathView path) const
    {
        const auto& pos = m_body->getPos();
        this->playAtDirect(path, pos);
    }
    void AudioSource::playAtDirect(s3d::FilePathView path, const s3d::Vec2 & pos) const
    {
        // TODO 後で確認
        //if (Audio baseAudio = Resource::Assets::Main()->load(U"se/Actors/" + path)) {
        //    Audio audio(baseAudio.getWave());
        //    if (auto loop = baseAudio.getLoop()) {
        //        audio.setLoop(loop->beginPos, loop->endPos);
        //    }
        //    this->playAtDirect(audio, pos);
        //}
    }
    void AudioSource::playAtDirect(const s3d::Audio & audio) const
    {
        const auto& pos = m_body->getPos();
        this->playAtDirect(audio, pos);
    }
    void AudioSource::playAtDirect(const s3d::Audio & audio, const s3d::Vec2 & pos) const
    {
        auto pActor = m_pActor->getModule<World>()->create().get();
        pActor->setDestoryTiming(DestoryTiming::Never);
        pActor->attach<Body>(pActor)->initPos(pos);
        pActor->attach<TemporarySoundEffect>(pActor, audio);
    }
}