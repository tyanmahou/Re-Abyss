#pragma once

namespace abyss::Scene::Boot
{
    class Initializer
    {
    public:
        static void LoadAsset();

        static void ReloadParamAll();
        static void ReloadMsg();
        static void ReloadNoRelease();
    };
}
