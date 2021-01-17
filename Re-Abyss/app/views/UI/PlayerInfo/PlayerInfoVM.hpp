#pragma once
#include <abyss/utils/TexturePacker/TexturePacker.hpp>
#include <Siv3D/TextureRegion.hpp>

namespace abyss::ui::PlayerInfo
{
    class PlayerInfoVM
    {
    private:
        TexturePacker m_texture;

        // 座標
        s3d::Vec2 m_pos;

        // HP
        s3d::int32 m_hp = 1;
        s3d::int32 m_maxHp = 1;

        // 顔
        s3d::TextureRegion m_face;

        // オーパーツ
        s3d::TextureRegion m_ooparts;
        s3d::String m_oopartsName;
    public:
        PlayerInfoVM();

        PlayerInfoVM& setPos(const s3d::Vec2& pos)
        {
            m_pos = pos;
            return *this;
        }

        PlayerInfoVM& setHp(s3d::int32 hp)
        {
            m_hp = hp;
            return *this;
        }
        PlayerInfoVM& setMaxHp(s3d::int32 maxHp)
        {
            m_maxHp = maxHp;
            return *this;
        }

        PlayerInfoVM& setFace(const s3d::TextureRegion& region)
        {
            m_face = region;
            return *this;
        }
        PlayerInfoVM& setOoparts(const s3d::TextureRegion& region, const s3d::String& name)
        {
            m_ooparts = region;
            m_oopartsName = name;
            return *this;
        }

        void draw() const;
    };
}