#ifndef METAXXA_TESTTUPLE_H
#define METAXXA_TESTTUPLE_H

#include "TestMetaxxa.h"

struct TestTuple : TestMetaxxa
{
	template <typename Type>
	struct MapArithmeticToInt
	{
		constexpr auto operator()()
		{
			if constexpr (std::is_arithmetic_v<Type>)
				return int();
			else
				return Type();
		}
	};

	template <typename Type>
	struct IsSingleSize
	{
		constexpr bool operator()()
		{
			return sizeof(Type) == 1;
		}
	};

	struct MyOrType {};

	struct MySingleSize {};

	template <typename Type>
	struct IsCharOrString
	{
		constexpr bool operator()()
		{
			return std::is_same_v<Type, char> || std::is_same_v<Type, std::string>; 
		}
	};

	virtual bool test() override
	{
		bool result = true;
		result = result && test_size();
		result = result && test_skip_first();
		result = result && test_map();
		result = result && test_map_types();
		result = result && test_sum();
		result = result && test_tuple_ref();
		result = result && test_find_types();
		result = result && test_filter();
		result = result && test_filter_types();
		result = result && test_wrap();
		result = result && test_wrap_types();
		result = result && test_contains();
		result = result && test_distinct_types();

		return result;
	}

	bool test_size()
	{
		auto tuple_0 = tuple(); 
		auto tuple_1 = tuple(1); 
		auto tuple_2 = tuple(1, 2); 
		auto tuple_3 = tuple(1, 2, 3); 
		auto tuple_4 = tuple(1, 2, 3, 4); 


		static_assert(tuple_0.size() == 0, "class Tuple: size test failed");
		static_assert(tuple_1.size() == 1, "class Tuple: size test failed");
		static_assert(tuple_2.size() == 2, "class Tuple: size test failed");
		static_assert(tuple_3.size() == 3, "class Tuple: size test failed");
		static_assert(tuple_4.size() == 4, "class Tuple: size test failed");

		return true;
	}

	bool test_skip_first()
	{
		int     _1  = 1;
		char    _2  = 'A';
		char   _3[] = "My message";
		double _4   = 3.14;

		auto t = tuple(_1, _2, _3, _4);
		auto result_1 = tuple(_2, _3, _4);
		auto result_2 = tuple(_3, _4);
		auto result_3 = tuple(_4);
		auto result_4 = tuple();

		TEST(t.skip_first<0>() == t,    "class Tuple: skip first test failed");
		TEST(t.skip_first<1>() == result_1, "class Tuple: skip first test failed");
		TEST(t.skip_first<2>() == result_2, "class Tuple: skip first test failed");
		TEST(t.skip_first<3>() == result_3, "class Tuple: skip first test failed");
		TEST(t.skip_first<4>() == result_4, "class Tuple: skip first test failed");

		return true;
	}

	bool test_map()
	{
		auto t = tuple(1, 2, int16_t(-1), size_t(3));
		auto map_result = t.map([](auto const &value) { return value * 10; });

		auto result = tuple(10, 20, int16_t(-10), size_t(30));

		TEST(map_result == result, "class Tuple: map test failed");
		return true;
	}

	bool test_map_types()
	{
		using T = Tuple<int, double, char, std::string, bool>;

		using MappedTuple = decltype(T::map_types<MapArithmeticToInt>());
		static_assert(std::is_same_v<MappedTuple, Tuple<int, int, int, std::string, int>>, "class Tuple: map types test failed");
		return true;
	}

	bool test_sum()
	{
		auto t = tuple(1, 5, 3.14, 5.1f, 'A', 0);

		TEST_FRACTION_NEAR(t.sum(), 79.24, 0.001, "class Tuple: sum test failed");
		return true;
	}

	bool test_tuple_ref()
	{
		int var = 42;
		const int &cr = var;
		int &r = var;
		auto tref = tuple_ref(var, cr, r);
		
		static_assert(std::is_same_v<Tuple<int &, const int &, int &>, decltype(tref)>, "class Tuple: tuple ref test failed");
		return true;
	}

	bool test_find_types()
	{
		Tuple<int, MySingleSize, short, double, std::string> expected_found;
		Tuple<int, double, std::string> expected_not_found;

		{
			using SingleSizeOptional = decltype(expected_found.find_types<IsSingleSize>());

			static_assert(SingleSizeOptional::FOUND,                                          "class Tuple: find types test failed");
			TEST(SingleSizeOptional::INDEX == 1,                                              "class Tuple: find types test failed");
			static_assert(std::is_same_v<SingleSizeOptional::Type, MySingleSize>,             "class Tuple: find types test failed");
			static_assert(std::is_same_v<SingleSizeOptional::TypeOr<MyOrType>, MySingleSize>, "class Tuple: find types test failed");
		} 

		{
			using SingleSizeOptional = decltype(expected_not_found.find_types<IsSingleSize>());

			static_assert(!SingleSizeOptional::FOUND,                                     "class Tuple: find types test failed");
			static_assert(std::is_same_v<SingleSizeOptional::TypeOr<MyOrType>, MyOrType>, "class Tuple: find types test failed");
		}

		return true;	
	}
	
	bool test_filter()
	{
		using namespace std::string_literals;
		Tuple<int, int, short, double, std::string, char, const char *, const char *> t(1, 12, 42, 3.14, "44", char(4), "0", "15");
 
		auto filtered = t.filter([](auto value) 
		{ 
			if constexpr(std::is_same_v<decltype(value), std::string> || std::is_same_v<decltype(value), const char *>)
				return std::stoi(value) > 10;
			else
			{
				return value > 10;
			}
		});

		TEST(!filtered.get<0>(), "class Tuple: filter test failed");
		TEST(filtered.get<1>(),  "class Tuple: filter test failed");
		TEST(filtered.get<2>(),  "class Tuple: filter test failed");
		TEST(!filtered.get<3>(), "class Tuple: filter test failed");
		TEST(filtered.get<4>(),  "class Tuple: filter test failed");
		TEST(!filtered.get<5>(), "class Tuple: filter test failed");
		TEST(!filtered.get<6>(), "class Tuple: filter test failed");
		TEST(filtered.get<7>(),  "class Tuple: filter test failed");

		TEST(filtered.get<1>().value() == 12,    "class Tuple: filter test failed");
		TEST(filtered.get<2>().value() == 42,    "class Tuple: filter test failed");
		TEST(filtered.get<4>().value() == "44"s, "class Tuple: filter test failed");
		TEST(filtered.get<7>().value() == "15"s, "class Tuple: filter test failed");
		
		return true;
	}

	bool test_filter_types()
	{
		using T = Tuple<int, double, char, std::string, bool>;

		using FilteredTuple = decltype(T::filter_types<IsCharOrString>());
		static_assert(std::is_same_v<FilteredTuple, Tuple<char, std::string>>, "class Tuple: filter types test failed");
		return true;
	}

	bool test_wrap()
	{
		Tuple<int, double, std::string> t(42, 3.14, "Hello");
		
		auto wrapped = t.wrap<METAXXA_OPTIONAL>();
		TEST(wrapped.get<0>() && (wrapped.get<0>().value() == 42),      "class Tuple: wrap test failed");
		TEST(wrapped.get<1>() && (wrapped.get<1>().value() == 3.14),    "class Tuple: wrap test failed");
		TEST(wrapped.get<2>() && (wrapped.get<2>().value() == "Hello"), "class Tuple: wrap test failed");

		return true;
	}

	bool test_wrap_types()
	{
		using T = Tuple<int, double, std::string>;

		static_assert
		(
			std::is_same_v
			<
				decltype(T::wrap_types<METAXXA_OPTIONAL>()),
				Tuple<METAXXA_OPTIONAL<int>, METAXXA_OPTIONAL<double>, METAXXA_OPTIONAL<std::string>>
			>, 
			"class Tuple: wrap all test failed"
		);
		return true;
	}

	bool test_contains()
	{
		Tuple<int, double, int, char> tuple(42, 3.14, 500, 11);

		TEST(tuple.contains(500), "class Tuple: contains test failed");
		TEST(!tuple.contains(-1), "class Tuple: contains test failed");


		return true;
	}

	bool test_contains_types()
	{
		using T = Tuple<int, double, std::string, int, char>;

		static_assert(T::contains_types<std::string, char>(), "class Tuple: contains types test failed");
		static_assert(!T::contains_types<float>(),            "class Tuple: contains types test failed");

		return true;
	}

	bool test_distinct_types()
	{
		{
			using T = Tuple<int, double, std::string, int, char>;

			static_assert(std::is_same_v<decltype(T::distinct_types()), Tuple<int, double, std::string, char>>, "class Tuple: distinct types test failed");
		}

		{
			using T = Tuple<int, double, char>;

			static_assert(std::is_same_v<decltype(T::distinct_types()), Tuple<int, double, char>>, "class Tuple: distinct types test failed");
		}

		{
			using T = Tuple<>;

			static_assert(std::is_same_v<decltype(T::distinct_types()), Tuple<>>, "class Tuple: distinct types test failed");
		}

		return true;
	}
};

#endif // METAXXA_TESTTUPLE_H
