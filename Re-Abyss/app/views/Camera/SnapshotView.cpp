#include "SnapshotView.hpp"
#include <abyss/commons/Constants.hpp>
#include <Siv3D/Shader.hpp>
#include <Siv3D/TextureRegion.hpp>
#include <Siv3D/ScopedCustomShader2D.hpp>

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
    s3d::ScopedRenderTarget2D SnapshotView::startPostRender()
    {
        m_isSwapPostTexture = !m_isSwapPostTexture;
        const auto& rt = this->getPostTexture();
        rt.clear(s3d::ColorF(0, 1));
        return s3d::ScopedRenderTarget2D(rt);
    }
    SnapshotView& SnapshotView::copySceneToPost()
    {
        s3d::Shader::Copy(m_sceneTexture, m_isSwapPostTexture ? m_postTexture2 : m_postTexture);
        return *this;
    }
    SnapshotView& SnapshotView::apply(std::function<void(const s3d::Texture&)> callback)
    {
        const auto& prev = this->getPostTexture();
        auto postRender = this->startPostRender();
        callback(prev);
        return *this;
    }
    SnapshotView& SnapshotView::apply(std::function<s3d::ScopedCustomShader2D()> callback)
    {
        const auto& prev = this->getPostTexture();
        auto postRender = this->startPostRender();
        auto scoped = callback();
        prev.draw();
        return *this;
    }
    SnapshotView& SnapshotView::apply(bool enable, std::function<s3d::ScopedCustomShader2D()> callback)
    {
        if (!enable) {
            return *this;
        }
        return this->apply(callback);
    }
    void SnapshotView::draw(const s3d::Vec2& offset) const
    {
        if (offset.isZero()) {
            this->getPostTexture().draw(Constants::GameScreenOffset);
        } else {
            this->getPostTexture()(offset, Constants::GameScreenSize).draw(Constants::GameScreenOffset);
        }
    }
    const s3d::RenderTexture& SnapshotView::getPostTexture() const
    {
        return m_isSwapPostTexture ? m_postTexture2 : m_postTexture;
    }
}
