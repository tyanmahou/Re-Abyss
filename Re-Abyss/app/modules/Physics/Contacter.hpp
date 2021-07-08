#pragma once
#include <abyss/modules/GameObject/GameObject.hpp>
#include <abyss/modules/Physics/base/IContacter.hpp>

namespace abyss::Physics
{
    class Contacter : public IContacter
    {
    public:
        Contacter(GameObject* pGameObject = nullptr);

        void setId(s3d::uint64 id) final
        {
            m_id = id;
        }

        s3d::uint64 id() const final
        {
            return m_id;
        }

        bool isActive() const override;
        Contacter& setShape(const CShape& shape)
        {
            m_shape = shape;
            return *this;
        }
        const CShape& getShape() const final
        {
            return m_shape;
        }
        void onCollision(const TerrainData& terrain) override;

        Contacter& initPos(const s3d::Vec2& pos)
        {
            m_prevPos = pos;
            m_pos = pos;
            return *this;
        }
        Contacter& setPos(const s3d::Vec2& pos)
        {
            m_prevPos = m_pos;
            m_pos = pos;
            return *this;
        }
        const s3d::Vec2& getPos()
        {
            return m_pos;
        }
        Contacter& setVelocity(const s3d::Vec2& v)
        {
            m_velocity = v;
            return *this;
        }
    private:
        GameObject* m_pGameObject = nullptr;

        s3d::Vec2 m_pos{0, 0};
        s3d::Vec2 m_prevPos{ 0, 0 };

        s3d::Vec2 m_velocity{ 0, 0 };

        s3d::Vec2 m_pivot{ 0, 0 };
        s3d::Vec2 m_size{ 0, 0 };
    private:
        s3d::uint64 m_id;
        bool m_isActive = true;
        CShape m_shape;
    };
}