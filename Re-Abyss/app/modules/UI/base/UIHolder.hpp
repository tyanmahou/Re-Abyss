#pragma once
#include <memory>
#include <Siv3D/Array.hpp>
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/UI/base/UIObj.hpp>

namespace abyss::UI
{
    class UIHolder
    {
    private:
        s3d::Array<std::shared_ptr<UIObj>> m_reserves;
        s3d::Array<std::shared_ptr<UIObj>> m_uis;

        Filter m_filter{};
    public:
        void flush();
        void push(const std::shared_ptr<UIObj>& ui);
        void update();
        void postUpdate();
        void draw() const;

        void erase();

        void clear();

        void setFilter(const Filter& filter)
        {
            m_filter = filter;
        }

        Filter getFilter() const
        {
            return m_filter;
        }
    };
}
