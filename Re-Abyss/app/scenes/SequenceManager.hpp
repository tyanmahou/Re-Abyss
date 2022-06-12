#pragma once
#include <abyss/scenes/Sequence/ISequence.hpp>
#include <abyss/scenes/base/ISceneBase.hpp>

namespace abyss
{
    class SequenceManager
    {
    public:
        SequenceManager();

        bool update();
    private:
        AppScene m_scene;
    };
}
