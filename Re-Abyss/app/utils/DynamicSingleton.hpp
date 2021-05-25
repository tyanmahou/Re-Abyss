#pragma once
#include <memory>
#include <functional>

namespace abyss
{
	/// <summary>
	/// 動的シングルトンファイナライザ
	/// </summary>
	class DynamicSingletonFinalizer
	{
	public:
		using FinalizerFunc = void(*)();
	private:
		class Impl;
	private:
		static DynamicSingletonFinalizer* Instance()
		{
			static DynamicSingletonFinalizer instance;
			return &instance;
		}
	public:
		static void AddFinalizer(FinalizerFunc func);
		static void Finalize();

	private:
		DynamicSingletonFinalizer();
		~DynamicSingletonFinalizer();
		DynamicSingletonFinalizer(const DynamicSingletonFinalizer& other) = delete;
		DynamicSingletonFinalizer& operator=(const DynamicSingletonFinalizer& other) = delete;
	private:
		std::unique_ptr<Impl> m_pImpl;
	};

	/// <summary>
	/// 動的シングルトン
	/// </summary>
	template<class Type>
	class DynamicSingleton
	{
	public:

		static Type* Instance()
		{
			static Type* instance = [] {
				Type* ret = new Type;
				DynamicSingletonFinalizer::AddFinalizer([] {delete instance; instance = nullptr; });
				return ret;
			}();
			return instance;
		}
	protected:
		DynamicSingleton() {}
		virtual ~DynamicSingleton() {}
	private:
		DynamicSingleton(const DynamicSingleton& other) = delete;
		DynamicSingleton& operator=(const DynamicSingleton& other) = delete;
	};
}