#pragma once
#include <S3DTiled.hpp>

namespace abyss
{
    class TmxParseUtil
    {
    public:
        template<class ParserFunc>
        static void ParseForGroup(const s3dTiled::Layer& layer, ParserFunc func)
        {
            if (layer.then([&](const s3dTiled::GroupLayer& layer) {
                for (auto&& l : layer.getLayers()) {
                    ParseForGroup(l, func);
                }
            })) {
                return;
            }
            layer.then(func);
        }
    };

}