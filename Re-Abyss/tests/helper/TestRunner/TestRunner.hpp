#pragma once

namespace abyss::tests
{
    class TestRunner
    {
    public:
        bool run() const;
        void waitKey() const;
    };
}

#define RunTest Main