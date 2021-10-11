#pragma once
#include <abyss/components/base/IComponent.hpp>
#include <Siv3D/Optional.hpp>

namespace abyss::UI::Dialog
{
    template<class Type>
    class DialogResult : public IComponent
    {
    public:
        using value_type = Type;
    public:
        DialogResult()
        {}

        void set(const Type& result)
        {
            m_result = result;
        }

        const s3d::Optional<Type>& get() const
        {
            return m_result;
        }
    private:
        s3d::Optional<Type> m_result;
    };
}