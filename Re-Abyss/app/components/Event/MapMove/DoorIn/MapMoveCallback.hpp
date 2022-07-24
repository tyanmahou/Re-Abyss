#pragma once
#include <abyss/components/Event/MapMove/MapMoveCtrl.hpp>
#include <abyss/components/Event/Common/FadeIrisOut.hpp>

namespace abyss::Event::MapMove::DoorIn
{
    class MapMoveCallback : public IMapMoveCallback
    {
    public:
        MapMoveCallback(
            EventObj* pEvent,
            const s3d::Vec2& cameraMove,
            const s3d::Vec2& playerMove,
            const s3d::Vec2& origin
        );

        void onMoveStart() override;
        void onMoveUpdate(double t) override;
        void onMoveEnd() override;

        s3d::Vec2 calcCameraPos() const override;
        s3d::Vec2 calcPlayerPos() const override;

    private:
        EventObj* m_pEvent;
        s3d::Vec2 m_cameraMove;
        s3d::Vec2 m_playerMove;
        s3d::Vec2 m_origin;

        double m_elapsed = 0.0;
        Ref<FadeIrisOut> m_fade;
    };
}
