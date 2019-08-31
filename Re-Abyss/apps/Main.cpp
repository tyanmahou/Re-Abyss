#include<application/common/AbyssDream.hpp>

#include<application/util/Visitor.hpp>

struct MyStruct
{
	void operator()(int)const {

	}
};
struct MyStruct2
{
	void operator()(double)const {

	}
};
void Main()
{
	auto f = abyss::overloaded(
		[](int) {}
	);
	// アプリ起動
	abyss::AbyssDream app;
	app.run();
}
