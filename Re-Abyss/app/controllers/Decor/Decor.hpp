#pragma once
#include <Siv3D/Array.hpp>
#include <abyss/commons/Fwd.hpp>
#include <abyss/views/Decor/DecorView.hpp>


namespace abyss
{
    class Decor
    {
        std::shared_ptr<IDecorService> m_decorService;
        std::shared_ptr<DecorGraphicsManager> m_manager;

        DecorView m_view;
    public:
        Decor() = default;
        Decor(
            const std::shared_ptr<IDecorService>& service,
            const std::shared_ptr<DecorGraphicsManager>& manager
        );
        void init(const Camera& camera);

        void update(double time);
        void draw(s3d::int32 order, const s3d::RectF& screen) const;
        void drawBack(const s3d::RectF& screen) const;
        void drawMiddle(const s3d::RectF& screen) const;
        void drawFront(const s3d::RectF& screen) const;

        void regist(s3d::int32 order, const std::shared_ptr<IDecorVM>& decor);
        void clear();
    };

    namespace DecorOrder
    {
        inline constexpr s3d::int32 Back = 0;
        inline constexpr s3d::int32 Middle = 1;
        inline constexpr s3d::int32 Front = 2;
    }
}