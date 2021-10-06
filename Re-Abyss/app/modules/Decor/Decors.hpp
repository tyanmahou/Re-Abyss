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
        Decor::DecorHolder m_decors;
        std::shared_ptr<DecorGraphics> m_graphics;

        Decor::BufferLayer m_bufferLayer = Decor::BufferLayer::Front;
        Manager* m_pManager = nullptr;
    public:
        Decors();

        Decors& setManager(Manager* pManager)
        {
            m_pManager = pManager;
            return *this;
        }
        Manager* getManager() const
        {
            return m_pManager;
        }
        void flush();

        void update();
        void draw() const;

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
        Ref<Decor::DecorObj> create();

        /// <summary>
        /// ビルダーから装飾の生成
        /// </summary>
        template<class BuilerType, class... Args>
        Ref<Decor::DecorObj> create(Args&& ... args)
            requires DecorBuildy<BuilerType, Args...>
        {
            auto decor = this->create();
            BuilerType::Build(decor.get(), std::forward<Args>(args)...);
            return decor;
        }

        /// <summary>
        /// 装飾を登録
        /// </summary>
        Ref<Decor::DecorObj> regist(const std::shared_ptr<Decor::DecorObj>& decor);

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

        Decor::BufferLayer getBufferLayer() const
        {
            return m_bufferLayer;
        }
        Decor::DecorIdTable getIdTable() const;
    };
}