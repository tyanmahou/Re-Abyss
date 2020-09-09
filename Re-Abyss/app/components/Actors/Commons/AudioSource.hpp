#pragma once
#include <Siv3D/Fwd.hpp>
#include <Siv3D/Array.hpp>
#include <Siv3D/Audio.hpp>

#include <abyss/commons/Fwd.hpp>
#include <abyss/components/base/IComponent.hpp>
#include <abyss/models/Actors/base/IUpdateModel.hpp>
#include <abyss/utils/Ref/Ref.hpp>
#include <abyss/utils/AudioSetting/AudioSettingGroup.hpp>

namespace abyss::Actor
{
    class AudioSource: 
        public IComponent,
        public IUpdateModel
    {
    private:
        IActor* m_pActor;
        Ref<BodyModel> m_body;
        s3d::Array<s3d::Audio> m_audios;
        AudioSettingGroup m_audioSettingGroup;
    public:
        AudioSource(IActor* pActor);
        void setup() override;

        void load(const s3d::FilePath& path);
        void onUpdate(double dt) override;

        void play(const s3d::String& key);

        void playAt(const s3d::String& key) const;
        void playAt(const s3d::String& key, const s3d::Vec2& pos) const;

        void playDirect(s3d::FilePathView path);
        void playDirect(const s3d::Audio& audio);

        void playAtDirect(s3d::FilePathView path) const;
        void playAtDirect(s3d::FilePathView path, const s3d::Vec2& pos) const;

        void playAtDirect(const s3d::Audio& audio) const;
        void playAtDirect(const s3d::Audio& audio, const s3d::Vec2& pos) const;

    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::AudioSource>
    {
        using Base = IUpdateModel;
    };
}