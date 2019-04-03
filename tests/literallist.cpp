#include "tests.h"

TEST_CASE("LiteralList head/tail", "[metaxxa::LiteralList]")
{
    SECTION("Empty list")
    {
        static_assert(is_same_v<typename LiteralList<>::Head, LiteralNil>, "Invalid Head of empty LiteralList");
        static_assert(is_same_v<typename LiteralList<>::HeadType, LiteralNilT>, "Invalid HeadType of empty LiteralList");
        static_assert(is_same_v<typename LiteralList<>::Tail, LiteralNil>, "Invalid Tail of empty LiteralList");

        static_assert(LiteralList<>::head() == NIL, "Invalid head() of empty LiteralList");
    }

    SECTION("LiteralNil")
    {
        static_assert(is_same_v<typename LiteralNil::Head, LiteralNil>, "Invalid Head of LiteralNil");
        static_assert(is_same_v<typename LiteralNil::HeadType, LiteralNilT>, "Invalid HeadType of LiteralNil");
        static_assert(is_same_v<typename LiteralNil::Tail, LiteralNil>, "Invalid Tail of LiteralNil");

        static_assert(LiteralNil::head() == NIL, "Invalid head() of LiteralNil");
    }

    SECTION("LiteralNil mupltiple Head/Tail")
    {
        static_assert(is_same_v<typename LiteralNil::Head::Head, LiteralNil>, "Invalid Head::Head of LiteralNil");
        static_assert(is_same_v<typename LiteralNil::Tail::Tail, LiteralNil>, "Invalid Tail::Tail of LiteralNil");

        static_assert(is_same_v<typename LiteralNil::Head::Tail, LiteralNil>, "Invalid Head::Head of LiteralNil");
        static_assert(is_same_v<typename LiteralNil::Tail::Head, LiteralNil>, "Invalid Tail::Tail of LiteralNil");

        static_assert(is_same_v<typename LiteralNil::Head::Head::Head, LiteralNil>, "Invalid Head::Head::Head of LiteralNil");
        static_assert(is_same_v<typename LiteralNil::Tail::Tail::Tail, LiteralNil>, "Invalid Tail::Tail::Tail of LiteralNil");
    }

    SECTION("LiteralList with size == 1")
    {
        static_assert(is_same_v<typename LiteralList<char, 'a'>::Head, Literal<char, 'a'>>, "Invalid Head of LiteralList with size == 1");
        static_assert(is_same_v<typename LiteralList<char, 'a'>::HeadType, char>, "Invalid HeadType of LiteralList with size == 1");
        static_assert(is_same_v<typename LiteralList<char, 'a'>::Tail, LiteralNil>, "Invalid Tail of LiteralList with size == 1");

        static_assert(LiteralList<char, 'a'>::head() == 'a', "Invalid head() of LiteralList with size == 1");
    }

    SECTION("LiteralList with size == 2")
    {
        using L = LiteralList<int, 1, 2>;

        static_assert(is_same_v<typename L::Head, Literal<int, 1>>, "Invalid Head of LiteralList with size == 2");
        static_assert(is_same_v<typename L::HeadType, int>, "Invalid HeadType of LiteralList with size == 2");
        static_assert(is_same_v<typename L::Tail, LiteralList<int, 2>>, "Invalid Tail of LiteralList with size == 2");

        static_assert(L::head() == 1, "Invalid head() of LiteralList with size == 2");

        using LTail = typename L::Tail;

        static_assert(is_same_v<typename LTail::Head, Literal<int, 2>>, "Invalid Head of LiteralList with size == 2");
        static_assert(is_same_v<typename LTail::HeadType, int>, "Invalid HeadType of LiteralList with size == 2");
        static_assert(is_same_v<typename LTail::Tail, LiteralNil>, "Invalid Tail of LiteralList with size == 2");

        static_assert(LTail::head() == 2, "Invalid head() of LiteralList with size == 2");
    }
}