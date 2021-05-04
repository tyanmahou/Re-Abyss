#include "SnapshotView.hpp"
#include <abyss/commons/Constants.hpp>

namespace abyss
{
    SnapshotView::SnapshotView():
        m_sceneTexture(Constants::GameScreenSize.asPoint()),
        m_postTexture(Constants::GameScreenSize.asPoint()),
        m_postTexture2(Constants::GameScreenSize.asPoint())
    {}
    s3d::ScopedRenderTarget2D SnapshotView::startSceneRender() const
    {
        m_sceneTexture.clear(s3d::ColorF(0, 1));
        return s3d::ScopedRenderTarget2D(m_sceneTexture);
    }
    s3d::ScopedRenderTarget2D SnapshotView::startPostRender() const
    {
        m_postTexture.clear(s3d::ColorF(0, 1));
        return s3d::ScopedRenderTarget2D(m_postTexture);
    }
}
