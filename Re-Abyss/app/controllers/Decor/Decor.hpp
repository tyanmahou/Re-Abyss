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
        Decor(
            const std::shared_ptr<IDecorService>& service,
            const std::shared_ptr<DecorGraphicsManager>& manager
        );
        void init(const Camera& camera);

        void draw(s3d::int32 order, const s3d::RectF& screen) const;
    };

    namespace DecorOrder
    {
        inline constexpr s3d::int32 Back = 0;
        inline constexpr s3d::int32 Middle = 1;
        inline constexpr s3d::int32 Front = 2;
    }
}