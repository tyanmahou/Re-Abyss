#pragma once

namespace abyss
{
    class NoConstruct
    {
    private:
        NoConstruct() = delete;

        ~NoConstruct() = delete;

        NoConstruct(const NoConstruct&) = delete;

        NoConstruct& operator =(const NoConstruct&) = delete;
    };
}