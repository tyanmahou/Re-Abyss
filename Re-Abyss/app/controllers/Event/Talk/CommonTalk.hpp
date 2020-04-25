#pragma once
#include <Siv3D/HashTable.hpp>
#include <Siv3D/Stopwatch.hpp>
#include <abyss/controllers/Event/Talk/base/Serif.hpp>
#include <abyss/utils/TexturePacker/TexturePacker.hpp>
namespace abyss::Event::Talk
{
    class CommonTalk
    {
    private:
        s3d::Array<Serif> m_serifs;
        s3d::HashTable<s3d::String, TexturePacker> m_actors;
        size_t m_serifIndex = 0;
    public:
        void init();
        bool update();
        void draw()const;
    };
}