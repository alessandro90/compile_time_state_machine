#include <type_traits>
#include "ctsm/state_machine.hpp"
#include "ctsm/types/typelist.hpp"

using namespace ctsm;
using namespace ctsm::tr;
using namespace ctsm::tl;

struct event_a
{
};
struct event_b
{
};
struct event_c
{
};

struct state_a
{
    int state_value;
};
struct state_b
{
    int state_value;
};
struct state_c
{
    int state_value;
};

consteval auto run_machine()
{
    constexpr auto m = builder_t<state_a>::build(1)
                           .addTransition(transition_v<event_a, state_a>)
                           .addTransition(transition_v<event_b, state_b>)
                           .addTransition(transition_v<event_c, state_c>);

    static_assert(m.state().state_value == 1);
    static_assert(std::is_same_v<std::decay_t<decltype(m.state())>, state_a>);

    constexpr auto m1 = m.on<event_b>(15);
    static_assert(m1.state().state_value == 15);
    static_assert(std::is_same_v<std::decay_t<decltype(m1.state())>, state_b>);

    constexpr auto m2 = m1.on<event_c>(150);
    static_assert(m2.state().state_value == 150);
    static_assert(std::is_same_v<std::decay_t<decltype(m2.state())>, state_c>);
}

int main()
{
    run_machine();
}
