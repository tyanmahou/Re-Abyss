#pragma once
#include <abyss/modules/Physics/base/IContacter.hpp>

namespace abyss::Physics
{
    class Contacter : public IContacter
    {
    public:
        void setId(s3d::uint64 id) final
        {
            m_id = id;
        }

        s3d::uint64 id() const final
        {
            return m_id;
        }

        bool isActive() const override
        {
            return m_isActive;
        }
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
    private:
        s3d::Vec2 m_pos;
        s3d::Vec2 m_velocity;

    private:
        s3d::uint64 m_id;
        bool m_isActive = true;
        CShape m_shape;
    };
}