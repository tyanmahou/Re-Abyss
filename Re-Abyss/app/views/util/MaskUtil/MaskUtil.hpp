#pragma once
#include <functional>
#include <memory>
#include <Siv3D.hpp>

namespace abyss
{
    enum class MaskFunc
    {
        Equal,
        NotEqual,
    };

    class MaskShader
    {
        class Impl;

        class ScopedMask
        {
            std::shared_ptr<Impl> m_parentImpl;
            MaskFunc m_func;
            std::function<void()> m_mask;

            s3d::BlendState m_oldBlend;
            s3d::Optional<s3d::RenderTexture> m_oldTarget;
            s3d::Optional <s3d::Rect> m_oldViewport;
        public:
            ScopedMask(const std::shared_ptr<Impl>& parentImpl, MaskFunc func, const std::function<void()>& mask);
            ~ScopedMask();
        };
    private:

        std::shared_ptr<Impl> m_pImpl;

    public:
        MaskShader(const Size& size);
        MaskShader(uint32 width, uint32 height);

        ScopedMask equal(const std::function<void()>& mask)const;
        ScopedMask notEqual(const std::function<void()>& mask)const;

    };

    /// <summary>
    /// マスク処理ユーティリティ
    /// </summary>
    class MaskUtil
    {
    public:
        static MaskShader& Instance();
    };
}