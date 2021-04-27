#pragma once
#include <unordered_map>
#include <Siv3D/Array.hpp>
#include <abyss/commons/Fwd.hpp>
#include <abyss/concepts/Decor.hpp>
#include <abyss/modules/Decor/base/DecorHolder.hpp>

namespace abyss
{
    class DecorGraphics;

    class Decors
    {
        std::unordered_map<s3d::int32, decor::DecorHolder> m_decors;
        std::shared_ptr<DecorGraphics> m_graphics;

        decor::BufferLayer m_bufferLayer = decor::BufferLayer::Front;
        Manager* m_pManager = nullptr;
    public:
        Decors();

        Decors& setManager(Manager* pManager)
        {
            m_pManager = pManager;
            return *this;
        }

        void flush();

        void update();
        void draw(s3d::int32 order) const;
        void drawBack() const;
        void drawMiddle() const;
        void drawFront() const;

        /// <summary>
        /// チェックアウト時の処理
        /// </summary>
        void onCheckOut();

        /// <summary>
        /// チェックイン時の処理
        /// </summary>
        void onCheckIn();

        /// <summary>
        /// 装飾の生成
        /// </summary>
        /// <returns></returns>
        Ref<decor::DecorObj> create(s3d::int32 order);

        /// <summary>
        /// ビルダーから装飾の生成
        /// </summary>
        template<class BuilerType, class... Args>
        Ref<decor::DecorObj> create(s3d::int32 order, Args&& ... args)
            requires DecorBuildy<BuilerType, Args...>
        {
            auto decor = this->create(order);
            BuilerType::Build(decor.get(), std::forward<Args>(args)...);
            return decor;
        }

        /// <summary>
        /// 装飾を登録
        /// </summary>
        Ref<decor::DecorObj> regist(s3d::int32 order, const std::shared_ptr<decor::DecorObj>& decor);

        Decors& setGraphics(const std::shared_ptr<DecorGraphics>& graphics)
        {
            m_graphics = graphics;
            return *this;
        }

        /// <summary>
        /// アニメーションしたグラフィックId
        /// </summary>
        s3d::uint32 getAnimGId(s3d::uint32 gId, double time) const;

        /// <summary>
        /// 装飾グラフィックを取得
        /// </summary>
        s3d::TextureRegion getTexture(s3d::uint32 gId, double time) const;

        /// <summary>
        /// 装飾数
        /// </summary>
        /// <returns></returns>
        size_t size() const;

        decor::BufferLayer getBufferLayer() const
        {
            return m_bufferLayer;
        }
        decor::DecorIdTable getIdTable() const;
    };

    namespace DecorOrder
    {
        inline constexpr s3d::int32 Back = 0;
        inline constexpr s3d::int32 Middle = 1;
        inline constexpr s3d::int32 Front = 2;
    }
}