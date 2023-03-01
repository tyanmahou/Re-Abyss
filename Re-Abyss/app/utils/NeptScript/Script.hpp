#pragma once
#include <memory>
#include <abyss/utils/NeptScript/Evaluator/IEvaluator.hpp>

namespace abyss::Nept
{
    class Script
    {
        class Impl;
    public:
        Script() = default;
        Script(const s3d::FilePath& path);

        void eval(IEvaluator* evaluator);
    private:
        std::shared_ptr<Impl> m_pImpl;
    };
}
