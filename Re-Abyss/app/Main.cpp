
#include <abyss/commons/Application/MainApp.hpp>
#include "StaticLibs.hpp"

void RunTest();

void Main()
{
#if ABYSS_DO_TEST
    RunTest();
#endif

    using ReAbyss = abyss::MainApp;

    ReAbyss app;
    app.run();
}