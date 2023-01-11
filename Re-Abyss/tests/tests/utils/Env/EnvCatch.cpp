#if ABYSS_DO_TEST
#include <ThirdParty/Catch2/catch.hpp>
#include <abyss/utils/Env/detail/EnvParser.hpp>
#include <abyss/commons/Path.hpp>

namespace
{
    using namespace abyss::detail;

    class TestEnvContainer : public IEnvContainer
    {
    public:
        TestEnvContainer()
        {
            m_container[U"TEST1"] = U"AAA";
        }
        bool set(const s3d::String& key, const s3d::String& value, bool overwrite)
        {
            if (!overwrite && m_container.contains(key)) {
                return false;
            }
            m_container[key] = value;
            return true;
        }
        s3d::Optional<s3d::String> getOpt(const s3d::String& key) const
        {
            if (auto it = m_container.find(key); it != m_container.end()) {
                return it->second;
            }
            return s3d::none;
        }
    private:
        HashTable<String, String> m_container;
    };
}
namespace abyss::tests
{
    TEST_CASE("utils::EnvCatch. Test")
    {
        EnvParser parser(std::make_unique<TestEnvContainer>());
        SECTION("set test")
        {
            REQUIRE_FALSE(parser.getOpt(U"TEST2").has_value());

            parser.set(U"TEST2", U"BBB");
            REQUIRE(parser.getOpt(U"TEST2").has_value());
            REQUIRE(parser.get(U"TEST2") == U"BBB");
        }
        SECTION("set test overwrite")
        {
            REQUIRE(parser.getOpt(U"TEST1").has_value());
            bool result = parser.set(U"TEST1", U"BBB", false);
            REQUIRE_FALSE(result);

            REQUIRE(parser.get(U"TEST1") == U"AAA");

            result = parser.set(U"TEST1", U"BBB", true);
            REQUIRE(result);

            REQUIRE(parser.get(U"TEST1") == U"BBB");
        }

        SECTION("load .env")
        {
            REQUIRE(parser.get(U"TEST1") == U"AAA");
            parser.load(Path::TestDataPath + U"env/test.env");

            REQUIRE(parser.get(U"TEST1") == U"BBB");
            REQUIRE(parser.get(U"TEST2") == U"AAA");

            REQUIRE(parser.get(U"INTERP_TEST1") == U"AAA BBB");
            REQUIRE(parser.get(U"INTERP_TEST2") == U" AAA BBB ");
            REQUIRE(parser.get(U"INTERP_TEST3") == U"${TEST2} ${TEST1}");

            REQUIRE(parser.get(U"QUOT_TEST1") == U"\"AAA\"");
            REQUIRE(parser.get(U"QUOT_TEST2") == U"\"AAA\"");
            REQUIRE(parser.get(U"QUOT_TEST3") == U"'AAA'");
            REQUIRE(parser.get(U"QUOT_TEST4") == U"'AAA'");

            REQUIRE(parser.get(U"MULTILINE_TEST1") == U"AAA BBB\nCCC");
            REQUIRE(parser.get(U"MULTILINE_TEST2") == U"${TEST2} ${TEST1}\nCCC");
        }
    }
}
#endif
