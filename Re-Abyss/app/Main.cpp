
#include <abyss/commons/Application/MainApp.hpp>
#include "StaticLibs.hpp"

import abyss.tests;

void Main()
{
#if ABYSS_DO_TEST
    abyss::tests::RunTest();
#endif

    using ReAbyss = abyss::MainApp;

    ReAbyss app;
    app.run();
}