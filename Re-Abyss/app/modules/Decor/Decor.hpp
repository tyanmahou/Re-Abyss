#pragma once
#include <Siv3D/Array.hpp>
#include <abyss/commons/Fwd.hpp>
#include <abyss/views/Decor/DecorView.hpp>


namespace abyss
{
    class Decor
    {
        std::shared_ptr<DecorGraphicsManager> m_graphicsManager;

        DecorView m_view;
    public:
        Decor();

        void update(double time);
        void draw(s3d::int32 order, const s3d::RectF& screen) const;
        void drawBack(const s3d::RectF& screen) const;
        void drawMiddle(const s3d::RectF& screen) const;
        void drawFront(const s3d::RectF& screen) const;

        void regist(s3d::int32 order, const std::shared_ptr<IDecorVM>& decor);
        void clear();

        DecorGraphicsManager* getGraphicsManager() const;
    };

    namespace DecorOrder
    {
        inline constexpr s3d::int32 Back = 0;
        inline constexpr s3d::int32 Middle = 1;
        inline constexpr s3d::int32 Front = 2;
    }
}