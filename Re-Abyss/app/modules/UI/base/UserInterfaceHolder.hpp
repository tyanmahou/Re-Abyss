#pragma once
#include <memory>
#include <Siv3D/Array.hpp>
#include <abyss/commons/Fwd.hpp>
#include <abyss/concepts/UI.hpp>
#include <abyss/modules/UI/base/IUserInterface.hpp>

namespace abyss::ui
{
    class UserInterfaceHolder
    {
    private:
        s3d::Array<std::shared_ptr<IUserInterface>> m_reserves;
        s3d::Array<std::shared_ptr<IUserInterface>> m_uis;

    public:
        void flush();
        void push(const std::shared_ptr<IUserInterface>& ui);
        void update();
        void draw() const;

        void erase();

        void clear();

        void setActiveAll(bool isActive);
    };
}