#pragma once
#include <memory>
#include <Siv3D/Array.hpp>
#include <abyss/commons/Fwd.hpp>
#include <abyss/concepts/UI.hpp>
#include <abyss/modules/UI/base/UIObj.hpp>

namespace abyss::UI
{
    class UIHolder
    {
    private:
        s3d::Array<std::shared_ptr<UIObj>> m_reserves;
        s3d::Array<std::shared_ptr<UIObj>> m_uis;

    public:
        void flush();
        void push(const std::shared_ptr<UIObj>& ui);
        void update();
        void draw() const;

        void erase();

        void clear();

        void setActiveAll(bool isActive);
    };
}