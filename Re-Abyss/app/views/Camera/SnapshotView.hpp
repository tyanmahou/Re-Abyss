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
        s3d::ScopedRenderTarget2D startPostRender();
        const s3d::RenderTexture& getPostTexture() const;

        SnapshotView& copySceneToPost();

        SnapshotView& apply(std::function<void(const s3d::Texture&)> callback);
        SnapshotView& apply(std::function<s3d::ScopedCustomShader2D()> callback);
        SnapshotView& apply(bool enable, std::function<s3d::ScopedCustomShader2D()> callback);

    private:
        s3d::RenderTexture m_sceneTexture;

        s3d::RenderTexture m_postTexture;
        s3d::RenderTexture m_postTexture2;
        bool m_isSwapPostTexture = false;
    };
}