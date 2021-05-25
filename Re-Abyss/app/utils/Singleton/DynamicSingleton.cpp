#include "DynamicSingleton.hpp"
#include <vector>
#include <ranges>

namespace abyss
{
    class DynamicSingletonFinalizer::Impl
    {
    public:
        Impl()
        {
            m_finalizers.reserve(256);
        }
        void addFinalizer(FinalizerFunc func)
        {
            m_finalizers.push_back(func);
        }

        void finalize()
        {
            for (auto&& func : m_finalizers | std::views::reverse) {
                func();
            }
            m_finalizers.clear();
        }
    private:
        std::vector<FinalizerFunc> m_finalizers;
    };
    void DynamicSingletonFinalizer::AddFinalizer(FinalizerFunc func)
    {
        Instance()->m_pImpl->addFinalizer(func);
    }

    void DynamicSingletonFinalizer::Finalize()
    {
        Instance()->m_pImpl->finalize();
    }
    DynamicSingletonFinalizer::DynamicSingletonFinalizer():
        m_pImpl(std::make_unique<Impl>())
    {}
    DynamicSingletonFinalizer::~DynamicSingletonFinalizer()
    {}
}
