#pragma once
#include <queue>
#include <Siv3D/HashTable.hpp>
#include <abyss/controllers/Event/Talk/base/Serif.hpp>
#include <abyss/controllers/Event/Talk/base/FaceManager.hpp>

namespace abyss::Event::Talk
{
    class FaceManager;

    class CommonTalk
    {
    private:
        std::queue<Serif> m_serifs;
        std::shared_ptr<FaceManager> m_faceManager;
    public:
        void setFaceManager(const std::shared_ptr<FaceManager>& face);
        void addSerif(Serif&& serif);

        void init();
        bool update();
        void draw()const;
    };
}