#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/models/Actors/Commons/BodyModel.hpp>
#include <abyss/commons/ResourceManager/ResourceManager.hpp>

#include <abyss/controllers/ActionSystem/ActManager.hpp>
#include <abyss/controllers/Actors/Player/PlayerActor.hpp>
#include <abyss/controllers/World/World.hpp>
#include <abyss/commons/Constants.hpp>

namespace
{
    using namespace abyss;
    std::pair<double, double> CalcVolume(const s3d::Vec2& pos, const s3d::Vec2& listener)
    {
        const Vec3 listenerPos(listener, 200);
        const double volume = Pow(1 / Vec3(pos, 0).distanceFrom(listenerPos) * 160, 2);

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
        TemporarySoundEffect(IActor* pActor, s3d::FilePathView path) :
            m_pActor(pActor),
            m_audio(ResourceManager::Main()->loadAudio(U"se/Actors/" + path).getWave())
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

    void AudioSourceModel::play(s3d::FilePathView path)
    {
        if (auto baseAudio = ResourceManager::Main()->loadAudio(U"se/Actors/" + path)) {
            auto pos = m_body->getPos();
            auto listener = m_pActor->getModule<Player::PlayerActor>()->getPos();
            Audio audio(baseAudio.getWave());
            auto volume = ::CalcVolume(pos, listener);
            audio.setVolumeLR(volume.first, volume.second);
            audio.play();
            m_audios.push_back(audio);
        }
    }

    void AudioSourceModel::playAt(s3d::FilePathView path) const
    {
        auto pos = m_body->getPos();
        this->playAt(path, pos);
    }

    void AudioSourceModel::playAt(s3d::FilePathView path, const s3d::Vec2& pos) const
    {

        class TemporaryActor : public IActor
        {
        public:
            TemporaryActor(s3d::FilePathView path, const s3d::Vec2& pos)
            {
                this->attach<BodyModel>()->initPos(pos);
                this->attach<TemporarySoundEffect>(this, path);
            }
        };
        m_pActor->getModule<World>()->create<TemporaryActor>(path, pos);
    }
}