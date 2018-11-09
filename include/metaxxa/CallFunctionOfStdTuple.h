#ifndef METAXXA_CALLFUNCTIONOFSTDTUPLE_H
#define METAXXA_CALLFUNCTIONOFSTDTUPLE_H

#include <tuple>

namespace metaxxa
{
	namespace detail
	{
		template <typename Tuple, typename Callable, size_t INDEX, size_t... INDICES>
		auto call_function(Tuple &tuple, Callable &callable)
		{
			if constexpr(INDEX < std::tuple_size_v<Tuple>)
				return call_function<Tuple, Callable, INDEX + 1, INDICES..., INDEX>(tuple, callable);
			else
				return callable(std::get<INDICES>(tuple)...);
		}
	}

	template <typename Tuple, typename Callable>
	auto call_function(Tuple &tuple, Callable &callable)
	{
		return detail::call_function<Tuple, Callable, 0>(tuple, callable);
	}
}

#endif // METAXXA_CALLFUNCTIONOFSTDTUPLE_H