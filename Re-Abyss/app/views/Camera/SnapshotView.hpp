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
        s3d::ScopedRenderTarget2D startWorldRender() const;

        const s3d::Texture& getSceneTexture() const
        {
            return m_sceneTexture;
        }
        s3d::ScopedRenderTarget2D startPostRender();
        const s3d::RenderTexture& getPostTexture() const;

        SnapshotView& copySceneToPost();
        SnapshotView& copyWorldToPost();

        SnapshotView& apply(std::function<void(const s3d::Texture&)> callback);

        template<class ScopedMaterialType>
        SnapshotView& apply(ScopedMaterialType&& callback)
        {
            const auto& prev = this->getPostTexture();
            auto postRender = this->startPostRender();
            auto scoped = callback();
            prev.draw();
            return *this;
        }

        template<class ScopedMaterialType>
        SnapshotView& apply(bool enable, ScopedMaterialType&& callback)
        {
            if (!enable) {
                return *this;
            }
            return this->apply(std::forward<ScopedMaterialType>(callback));
        }

        void drawWorld(const s3d::Vec2& offset = s3d::Vec2::Zero()) const;
        void drawScene() const;
    private:
        s3d::RenderTexture m_sceneTexture;
        s3d::RenderTexture m_worldTexture;

        s3d::RenderTexture m_postTexture;
        s3d::RenderTexture m_postTexture2;
        bool m_isSwapPostTexture = false;
    };
}