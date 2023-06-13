#pragma once
#include <Siv3D/Fwd.hpp>
#include <Siv3D/Array.hpp>
#include <Siv3D/Audio.hpp>

#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/modules/Actor/base/IUpdate.hpp>
#include <abyss/components/Actor/Common/ILocator.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Actor
{
    class AudioSource: 
        public IComponent,
        public IUpdate
    {
    public:
        AudioSource(ActorObj* pActor);
        void onStart() override;

        void load(const s3d::FilePath& path);
        void onUpdate() override;

        void play(const s3d::String& key);

        void playAt(const s3d::String& key) const;
        void playAt(const s3d::String& key, const s3d::Vec2& pos) const;

        void playDirect(s3d::FilePathView path);
        void playDirect(const s3d::Audio& audio);

        void playAtDirect(s3d::FilePathView path) const;
        void playAtDirect(s3d::FilePathView path, const s3d::Vec2& pos) const;

        void playAtDirect(const s3d::Audio& audio) const;
        void playAtDirect(const s3d::Audio& audio, const s3d::Vec2& pos) const;

    private:
        ActorObj* m_pActor;
        Ref<ILocator> m_locator;
        s3d::Array<s3d::Audio> m_audios;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::AudioSource>
    {
        using Base = Actor::IUpdate;
    };
}
