#pragma once
#include <Siv3D/String.hpp>
#include <abyss/utils/Mns/Evaluator/IEvalImpl.hpp>

namespace Mns
{
    class Script
    {
        class Impl;
    public:
        Script() = default;

        Script(const s3d::FilePath& path);

        void eval(IEvalImpl* evaluator);

    private:
        std::shared_ptr<Impl> m_pImpl;
    };
}