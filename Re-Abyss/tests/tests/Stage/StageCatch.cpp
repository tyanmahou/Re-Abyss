#if ABYSS_DO_TEST
#include <ThirdParty/Catch2/catch.hpp>
#include <abyss/modules/Stage/Stage.hpp>
#include <abyss/modules/Stage/StageData.hpp>
#include <abyss/services/Stage/base/IStageService.hpp>
#include <abyss/entities/Room/RoomEntity.hpp>

namespace abyss::tests
{
    class Test_StageRepository : public IStageService
    {
    public:
        inline static constexpr s3d::RectF Room1{ 0, 0, 100, 100 };
        inline static constexpr s3d::RectF Room2{ 100, 100, 100, 100 };
    private:
        s3d::Array<RoomEntity> rooms;
    public:
        Test_StageRepository()
        {
            rooms.push_back(RoomEntity{ 0, Room1 , 0});
            rooms.push_back(RoomEntity{ 1, Room2 , 0 });
        }
        ~Test_StageRepository() = default;
        const s3d::Array<RoomEntity>& getRooms() const
        {
            return rooms;
        }
    };

    TEST_CASE("Stage. findRoom Test")
    {
        emaject::Injector injector;
        injector.install([](emaject::Container* c) {
            c->bind<IStageService>().to<Test_StageRepository>().asCache();
        });
        Stage stage;
        stage.setStageData(injector.resolve<StageData>());

        SECTION("find border min: pos (0, 0)")
        {
            auto room = stage.findRoom({ 0, 0 });
            REQUIRE(room.has_value());
            REQUIRE(room->getRegion() == Test_StageRepository::Room1);
        }
        SECTION("find border max: pos (100, 100)")
        {
            auto room = stage.findRoom({ 100, 100 });
            REQUIRE(room.has_value());
            REQUIRE(room->getRegion() == Test_StageRepository::Room2);
        }
        SECTION("find: pos (150, 150)")
        {
            auto room = stage.findRoom({ 150, 150 });
            REQUIRE(room.has_value());
            REQUIRE(room->getRegion() == Test_StageRepository::Room2);
        }
        SECTION("not find: pos (-50, -50)")
        {
            auto room = stage.findRoom({ -50, -50 });
            // 見つからない
            REQUIRE(!room.has_value());
        }
    }
}
#endif