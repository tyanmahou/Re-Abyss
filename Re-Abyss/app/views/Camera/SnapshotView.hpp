#pragma once
#include <Siv3D/RenderTexture.hpp>
#include <Siv3D/ScopedRenderTarget2D.hpp>

namespace abyss
{
    class SnapshotView
    {
    public:
        SnapshotView();

        s3d::ScopedRenderTarget2D startSceneRender() const;
        const s3d::Texture& getSceneTexture() const
        {
            return m_sceneTexture;
        }
        s3d::ScopedRenderTarget2D startPostRender() const;
        const s3d::Texture& getPostTexture() const
        {
            return m_postTexture;
        }
    private:
        s3d::RenderTexture m_sceneTexture;
        s3d::RenderTexture m_postTexture;
    };
}