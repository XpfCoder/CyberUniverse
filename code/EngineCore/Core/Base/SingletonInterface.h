#ifndef CYBER_SINGLETONINTERFACE
#define CYBER_SINGLETONINTERFACE
#include <type_traits>


namespace EngineCore
{
	template<typename T>
	class _declspec(dllexport) ISingleton
	{
	protected:
		ISingleton() = default;

	public:
		static T& getInstance() noexcept(std::is_nothrow_constructible<T>::value)
		{
			static T instance;
			return instance;
		}
		virtual ~ISingleton() noexcept = default;
		ISingleton(const ISingleton&) = delete;
		ISingleton& operator=(const ISingleton&) = delete;
	};
}









#endif // !CYBER_SINGLETONINTERFACE