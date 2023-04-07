#if ABYSS_DO_TEST
#include <ThirdParty/Catch2/catch.hpp>
#include <abyss/values/StageDef.hpp>
#include <abyss/commons/Path.hpp>

namespace abyss::tests
{
    TEST_CASE("values StageDef Test")
    {
        SECTION("isValid") {
            StageDef stageEmpty{};
            REQUIRE_FALSE(stageEmpty.isValid());

            StageDef stage = StageDef::FromDircet(Path::MapPath + U"Test.tmx");
            REQUIRE(stage.isValid());
        }
        SECTION("mapName") {
            StageDef stage = StageDef::FromDircet(Path::MapPath + U"Test/Test.tmx");
            REQUIRE(stage.mapName() == U"Map/Test/Test");
        }
        SECTION("preloadPath") {
            StageDef stage = StageDef::FromDircet(Path::MapPath + U"Test/Test.tmx");
            REQUIRE(stage.preloadPath() == U"Map/Test/Test");
        }
        SECTION("isTestMap") {
            StageDef stage = StageDef::FromDircet(Path::MapPath + U"Test.tmx");
            REQUIRE_FALSE(stage.isTestMap());

            StageDef stageTest = StageDef::FromDircet(Path::TestMapPath + U"Test.tmx");
            REQUIRE(stageTest.isTestMap());
        }
        SECTION("link") {
            StageDef stage0 = StageDef::FromDircet(Path::MapPath + U"Test0.tmx");
            StageDef stage1 = StageDef::FromDircet(Path::MapPath + U"Test1.tmx");
            REQUIRE(stage0.link(U"Test1") == stage1);
        }
    }
}
#endif ABYSS_DO_TEST
