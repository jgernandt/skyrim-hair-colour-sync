#pragma once
#include <array>
#include <cstdint>
#include <functional>
#include <utility>
#include <type_traits>

template<typename T, unsigned long long ID, std::uintptr_t DefaultOffset>
struct sse_ptr
{
	using type = T;
	constexpr static unsigned long long kID = ID;
	constexpr static std::uintptr_t kDefaultOffset = DefaultOffset;

	static std::uintptr_t address;

	constexpr static T get() { return reinterpret_cast<T>(address); }

	template<typename... Args> requires std::is_invocable_v<T, Args...>
	static std::invoke_result_t<T, Args...> invoke(Args&&... args)
	{
		return std::invoke(get(), std::forward<Args>(args)...);
	}
};

bool relocate(int version);
