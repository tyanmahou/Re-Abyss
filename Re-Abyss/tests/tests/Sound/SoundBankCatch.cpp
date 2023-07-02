#if ABYSS_DO_TEST
#include <ThirdParty/Catch2/catch.hpp>
#include <abyss/services/Sound/SoundBankService.hpp>
#include <abyss/datastores/Sound/CSVSoundBankDataStore.hpp>
#include <abyss/utils/Math/Math.hpp>

namespace abyss::tests
{
    TEST_CASE("SoundBank Test")
    {
        using namespace abyss::Sound;

        emaject::Injector injector;
        Resource::Assets* assets = Resource::Assets::Temporray();

        injector.install<CSVSoundBankDataStoreInstaller>(Path::TestDataPath + U"sounds/soundbank.csv", assets);
        injector.install<SoundBankServiceInstaller>();
        auto service = injector.resolve<ISoundBankService>();
        assets->release();

        SECTION("Test1") {
            auto test = service->setting(SoundLabel(U"Test1"));
            REQUIRE(test.path == Path::SoundPath + U"test1.mp3");
            REQUIRE(std::get<s3d::Loop>(test.loop).getBool() == s3d::Loop{true}.getBool());
            REQUIRE(test.samplingRate == 44100);
            REQUIRE(test.streaming == true);
        }
        SECTION("Test2") {
            auto test = service->setting(SoundLabel(U"Test2"));
            REQUIRE(test.path == Path::SoundPath + U"test2.mp3");
            REQUIRE(abyss::Math::IsEqualLoose(std::get<s3d::Duration>(test.loop), 12.3s));
            REQUIRE(test.samplingRate == 48000);
            REQUIRE(test.streaming == true);
        }
        SECTION("Test3") {
            auto test = service->setting(SoundLabel(U"Test3"));
            REQUIRE(test.path == Path::SoundPath + U"test3.mp3");
            REQUIRE(abyss::Math::IsEqualLoose(std::get<s3d::Vector2D<s3d::Duration>>(test.loop), s3d::Vector2D<s3d::Duration> { 12.3s, 45.6s }));
            REQUIRE(test.samplingRate == 44100);
            REQUIRE(test.streaming == false);
        }
    }
}
#endif
