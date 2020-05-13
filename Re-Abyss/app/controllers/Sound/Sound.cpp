#include "Sound.hpp"
#include <abyss/commons/ResourceManager/ResourceManager.hpp>

#include <abyss/controllers/ActionSystem/ActManager.hpp>
#include <abyss/controllers/Actors/Player/PlayerActor.hpp>

namespace abyss
{
    void Sound::playSe(const s3d::FilePath& path, const s3d::Vec2& pos) const
    {
        auto player = m_pManager->getModule<Player::PlayerActor>();
        if(auto audio = ResourceManager::Main()->loadAudio(U"se/Actors/" + path))
        {
            const Vec3 speakerPos(player->getPos(), 100);
            const double volume = Pow(1 / Vec3(pos, 0).distanceFrom(speakerPos) * 100, 2);

            // TODO 左右で音量を変える
            auto xDiff = pos.x - player->getPos().x;
            auto rate = 1 - Min(1.0, Abs(xDiff) / 480.0);
            audio.setVolumeLR(
                volume * (xDiff > 0 ? rate : 1.0),
                volume * (xDiff < 0 ? rate : 1.0)
            );
            audio.play();

            //audio.setVolumeLR(1, 0);
            //audio.playOneShot(volume);
        }
    }

}
