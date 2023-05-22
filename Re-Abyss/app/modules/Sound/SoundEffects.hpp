#pragma once
#include <abyss/commons/Resource/Assets/Assets.hpp>

namespace abyss
{
    class SoundEffects
    {
    public:
        SoundEffects(Resource::Assets* pAssets = Resource::Assets::Norelease());

        /// <summary>
        /// 再生
        /// </summary>
        /// <param name="path"></param>
        void play(const s3d::String& path);

    private:
        Resource::Assets* m_pAssets;
    };
}
