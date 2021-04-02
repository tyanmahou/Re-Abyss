#pragma once
#include <unordered_map>
#include <Siv3D/Array.hpp>
#include <abyss/commons/Fwd.hpp>
#include <abyss/concepts/Decor.hpp>
#include <abyss/modules/Decor/base/DecorHolder.hpp>

namespace abyss
{
    class Decor
    {
        std::unordered_map<s3d::int32, decor::DecorHolder> m_decors;
        Manager* m_pManager = nullptr;
    public:
        Decor();

        Decor& setManager(Manager* pManager)
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
    };

    namespace DecorOrder
    {
        inline constexpr s3d::int32 Back = 0;
        inline constexpr s3d::int32 Middle = 1;
        inline constexpr s3d::int32 Front = 2;
    }
}