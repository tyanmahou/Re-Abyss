#pragma once
#include <Siv3D/Rectangle.hpp>

namespace abyss
{
    enum class DecorType
    {
        Common,
        Map,
    };
    class IDecorModel
    {
        DecorType m_type;
    public:
        void setType(const DecorType& type)
        {
            m_type = type;
        }
        DecorType getType() const
        {
            return m_type;
        }
        virtual bool isInScreen(const s3d::RectF& screen)const = 0;
    };
}