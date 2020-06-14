#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/models/Actors/Commons/BodyModel.hpp>
#include <abyss/commons/ResourceManager/ResourceManager.hpp>

#include <abyss/controllers/Manager/Manager.hpp>
#include <abyss/controllers/Actors/Player/PlayerActor.hpp>
#include <abyss/controllers/World/World.hpp>
#include <abyss/commons/Constants.hpp>

namespace
{
    using namespace abyss;
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
        public IUpdateModel
    {
    public:
        TemporarySoundEffect(IActor* pActor, const s3d::Audio& audio) :
            m_pActor(pActor),
            m_audio(audio)
        {}

        void setup() override
        {
            m_body = m_pActor->find<BodyModel>();
            m_audio.play();
        }

        void onUpdate([[maybe_unused]] double dt) override
        {
            if (!m_audio.isPlaying()) {
                m_pActor->destroy();
            }
            auto pos = m_body->getPos();
            auto listener = m_pActor->getModule<Player::PlayerActor>()->getPos();

            auto volume = ::CalcVolume(pos, listener);
            m_audio.setVolumeLR(volume.first, volume.second);
        }
    private:
        Ref<BodyModel> m_body;
        IActor* m_pActor;
        Audio m_audio;
    };
}
namespace abyss
{
    template<>
    struct ComponentTree<TemporarySoundEffect>
    {
        using Base = IUpdateModel;
    };
}
namespace abyss
{


    AudioSourceModel::AudioSourceModel(IActor* pActor) :
        m_pActor(pActor)
    {}

    void AudioSourceModel::setup()
    {
        m_body = m_pActor->find<BodyModel>();
    }

    void AudioSourceModel::load(const s3d::FilePath& path)
    {
        m_audioSettingGroup = ResourceManager::Main()->loadAudioSettingGroup(U"se/Actors/" + path);
    }

    void AudioSourceModel::onUpdate([[maybe_unused]] double dt)
    {
        m_audios.remove_if([](const Audio& audio) {
            return !audio.isPlaying();
        });
        auto pos = m_body->getPos();
        auto listener = m_pActor->getModule<Player::PlayerActor>()->getPos();
        for (auto&& audio : m_audios) {
            auto volume = ::CalcVolume(pos, listener);
            audio.setVolumeLR(volume.first, volume.second);
        }

    }

    void AudioSourceModel::play(const s3d::String& key)
    {
        auto as = m_audioSettingGroup(key);
        if (auto baseAudio = ResourceManager::Main()->loadAudio(as.path, Path::Root)) {
            Audio audio(baseAudio.getWave());
            as.apply(audio);
            this->playDirect(audio);
        }
    }

    void AudioSourceModel::playAt(const s3d::String& key) const
    {
        auto pos = m_body->getPos();
        this->playAt(key, pos);
    }

    void AudioSourceModel::playAt(const s3d::String & key, const s3d::Vec2 & pos) const
    {
        auto as = m_audioSettingGroup(key);
        if (auto baseAudio = ResourceManager::Main()->loadAudio(as.path, Path::Root)) {
            Audio audio(baseAudio.getWave());
            as.apply(audio);
            this->playAtDirect(audio, pos);
        }
    }
    void AudioSourceModel::playDirect(s3d::FilePathView path)
    {
        if (auto baseAudio = ResourceManager::Main()->loadAudio(U"se/Actors/" + path)) {
            Audio audio(baseAudio.getWave());
            if (auto loop = baseAudio.getLoop()) {
                audio.setLoop(loop->beginPos, loop->endPos);
            }
            this->playDirect(audio);
        }
    }
    void AudioSourceModel::playDirect(const s3d::Audio& audio)
    {
        auto pos = m_body->getPos();
        auto listener = m_pActor->getModule<Player::PlayerActor>()->getPos();
        auto volume = ::CalcVolume(pos, listener);
        audio.setVolumeLR(volume.first, volume.second);
        audio.play();
        m_audios.push_back(audio);
    }
    void AudioSourceModel::playAtDirect(s3d::FilePathView path) const
    {
        auto pos = m_body->getPos();
        this->playAtDirect(path, pos);
    }
    void AudioSourceModel::playAtDirect(s3d::FilePathView path, const s3d::Vec2 & pos) const
    {
        if (auto baseAudio = ResourceManager::Main()->loadAudio(U"se/Actors/" + path)) {
            Audio audio(baseAudio.getWave());
            if (auto loop = baseAudio.getLoop()) {
                audio.setLoop(loop->beginPos, loop->endPos);
            }
            this->playAtDirect(audio, pos);
        }
    }
    void AudioSourceModel::playAtDirect(const s3d::Audio & audio) const
    {
        auto pos = m_body->getPos();
        this->playAtDirect(audio, pos);
    }
    void AudioSourceModel::playAtDirect(const s3d::Audio & audio, const s3d::Vec2 & pos) const
    {
        class TemporaryActor : public IActor
        {
        public:
            TemporaryActor(const s3d::Audio& audio, const s3d::Vec2& pos)
            {
                this->m_isDontDestoryOnLoad = true;
                this->attach<BodyModel>()->initPos(pos);
                this->attach<TemporarySoundEffect>(this, audio);
            }
        };
        m_pActor->getModule<World>()->create<TemporaryActor>(audio, pos);
    }
}