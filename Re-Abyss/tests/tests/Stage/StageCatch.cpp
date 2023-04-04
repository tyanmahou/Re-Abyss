#if ABYSS_DO_TEST
#include <ThirdParty/Catch2/catch.hpp>
#include <abyss/modules/Stage/Stage.hpp>
#include <abyss/modules/Stage/StageData.hpp>
#include <abyss/services/Room/base/IRoomService.hpp>
#include <abyss/entities/Room/RoomEntity.hpp>

namespace 
{
    using namespace abyss;

    class Test_RoomService : public IRoomService
    {
    public:
        inline static constexpr s3d::RectF Room1{ 0, 0, 100, 100 };
        inline static constexpr s3d::RectF Room2{ 100, 100, 100, 100 };
    private:
        s3d::Array<RoomEntity> rooms;
    public:
        Test_RoomService()
        {
            rooms.push_back(RoomEntity{ 0, Room1 , 0 });
            rooms.push_back(RoomEntity{ 1, Room2 , 0 });
        }
        ~Test_RoomService() = default;
        const s3d::Array<RoomEntity>& getRooms() const
        {
            return rooms;
        }
    };
}
namespace abyss::tests
{
    TEST_CASE("Stage. findRoom Test")
    {
        emaject::Injector injector;
        injector.install([](emaject::Container* c) {
            c->bind<IRoomService>().to<Test_RoomService>().asCached();
            c->bind<StageData>().withArgs(StageDef{}).asCached();
        });
        auto stage = injector.instantiate<Stage>();

        SECTION("find border min: pos (0, 0)")
        {
            auto room = stage->findRoom({ 0, 0 });
            REQUIRE(room.has_value());
            REQUIRE(room->getRegion() == Test_RoomService::Room1);
        }
        SECTION("find border max: pos (100, 100)")
        {
            auto room = stage->findRoom({ 100, 100 });
            REQUIRE(room.has_value());
            REQUIRE(room->getRegion() == Test_RoomService::Room2);
        }
        SECTION("find: pos (150, 150)")
        {
            auto room = stage->findRoom({ 150, 150 });
            REQUIRE(room.has_value());
            REQUIRE(room->getRegion() == Test_RoomService::Room2);
        }
        SECTION("not find: pos (-50, -50)")
        {
            auto room = stage->findRoom({ -50, -50 });
            // 見つからない
            REQUIRE(!room.has_value());
        }
    }
}
#endif
