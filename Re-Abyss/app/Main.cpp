
#include <abyss/commons/Application/MainApp.hpp>
#include "StaticLibs.hpp"

#include <thread>
void RunTest();

void Main()
{
#if ABYSS_DO_TEST
    std::thread test(RunTest);
#endif

    using ReAbyss = abyss::MainApp;

    ReAbyss app;
    app.run();

#if ABYSS_DO_TEST
    test.join();
#endif
}