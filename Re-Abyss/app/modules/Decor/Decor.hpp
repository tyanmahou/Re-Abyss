#pragma once
#include <unordered_map>
#include <Siv3D/Array.hpp>
#include <abyss/commons/Fwd.hpp>
#include <abyss/concepts/Decor.hpp>
#include <abyss/views/Decor/DecorView.hpp>
#include <abyss/modules/Decor/base/DecorHolder.hpp>

namespace abyss
{
    class Decor
    {
        std::unordered_map<s3d::int32, decor::DecorHolder> m_decors;
        Manager* m_pManager = nullptr;

        std::shared_ptr<DecorGraphicsManager> m_graphicsManager;

        DecorView m_view;
    public:
        Decor();

        Decor& setManager(Manager* pManager)
        {
            m_pManager = pManager;
            return *this;
        }

        void flush();

        void update(double time);
        void draw(s3d::int32 order, const s3d::RectF& screen) const;
        void drawBack(const s3d::RectF& screen) const;
        void drawMiddle(const s3d::RectF& screen) const;
        void drawFront(const s3d::RectF& screen) const;

        void clear();

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

        void regist(s3d::int32 order, const std::shared_ptr<IDecorVM>& decor);

        DecorGraphicsManager* getGraphicsManager() const;
    };

    namespace DecorOrder
    {
        inline constexpr s3d::int32 Back = 0;
        inline constexpr s3d::int32 Middle = 1;
        inline constexpr s3d::int32 Front = 2;
    }
}