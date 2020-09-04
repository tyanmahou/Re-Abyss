#pragma once
#include <memory>
#include <functional>
#include <Siv3D/String.hpp>
#include <abyss/components/base/IComponent.hpp>
#include <abyss/models/Actors/base/IDrawModel.hpp>

namespace abyss
{
    /// <summary>
    /// 汎用描画
    /// </summary>
    class CustomDrawModel :
        public IComponent,
        public IDrawModel
    {
    public:
        class IImpl
        {
        public:
            virtual ~IImpl() = default;

            virtual void setup() = 0;
            virtual void onDraw(const s3d::String& motion)const = 0;
        };
    private:
        s3d::String m_motion;
        std::unique_ptr<IImpl> m_pImpl;
    public:
        void setup() override;
        void onDraw() const override;

        /// <summary>
        /// モーションリクエスト
        /// </summary>
        CustomDrawModel& request(const s3d::String& motion)
        {
            m_motion = motion;
            return *this;
        }

        CustomDrawModel& setDrawer(std::unique_ptr<IImpl>&& drawer);

        template<class Impl, class... Args>
        CustomDrawModel& setDrawer(Args&&... args)
        {
            return setDrawer(std::make_unique<Impl>(std::forward<Args>(args)...));
        }
        CustomDrawModel& setDrawer(const std::function<void()>& drawer);

        CustomDrawModel& setDrawer(const std::function<void(const s3d::String&)>& drawer);
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<CustomDrawModel>
    {
        using Base = IDrawModel;
    };
}