#if ABYSS_DO_TEST
#include <ThirdParty/Catch2/catch.hpp>
#include <abyss/controllers/Stage/Stage.hpp>
#include <abyss/repositories/Stage/base/IStageRepository.hpp>
#include <abyss/views/Stage/base/IStageView.hpp>

namespace abyss::tests
{
    class Test_StageRepository : public IStageRepository
    {
    public:
        inline static constexpr s3d::RectF Room1{ 0, 0, 100, 100 };
        inline static constexpr s3d::RectF Room2{ 100, 100, 100, 100 };
    private:
        s3d::Array<RoomEntity> rooms;
        s3d::Array<MapEntity> maps;
        s3d::Array<std::shared_ptr<GimmickEntity>> gimmicks;
        s3d::Array<std::shared_ptr<EnemyEntity>> enemys;
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
        const s3d::Array<MapEntity>& getMaps() const
        {
            return maps;
        }
        const s3d::Array<std::shared_ptr<EnemyEntity>>& getEnemies() const
        {
            return enemys;
        }
        const s3d::Array<std::shared_ptr<GimmickEntity>>& getGimmicks() const
        {
            return gimmicks;
        }
    };

    TEST_CASE("Stage. findRoom Test")
    {
        auto rep = std::make_shared<Test_StageRepository>();
        Stage stage(rep, nullptr, nullptr, nullptr);

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