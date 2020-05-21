#pragma once
#include <Siv3D/Vector2D.hpp>
#include <abyss/types/Forward.hpp>
namespace abyss::Ooparts
{
    class OopartsVM
    {
    protected:
        s3d::Vec2 m_pos{0, 0};
        Forward m_forward{Forward::Right};
        virtual void drawCharacter(const s3d::Vec2& pos, const s3d::ColorF& color, double time) const = 0;
    public:
        OopartsVM() = default;
        virtual ~OopartsVM() = default;

        OopartsVM& setPos(const s3d::Vec2& pos)
        {
            m_pos = pos;
            return *this;
        }
        OopartsVM& setForward(Forward forward)
        {
            m_forward = forward;
            return *this;
        }
        void draw() const;
    };
}