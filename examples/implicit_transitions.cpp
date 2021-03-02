#include <type_traits>
#include "ctsm/state_machine.hpp"
#include "ctsm/types/typelist.hpp"

using namespace ctsm;
using namespace ctsm::tr;
using namespace ctsm::tl;

constexpr bool branch{true};

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
    static constexpr int update(auto const &state_machine)
    {
        if constexpr (branch)
        {
            return state_machine.template on<event_b>().update();
        }
        else
        {
            return state_machine.template on<event_c>().update();
        }
    }
};
struct state_b
{
    static constexpr int update(auto const &)
    {
        if constexpr (branch)
        {
            return -1;
        }
        else
        {
            return 1;
        }
    }
};
struct state_c
{
    static constexpr int update(auto const &)
    {
        if constexpr (branch)
        {
            return -10;
        }
        else
        {
            return 10;
        }
    }
};

consteval auto run_machine()
{
    return builder_t<state_a>::build()
        .addTransition(transition_v<event_b, state_b>)
        .addTransition(transition_v<event_c, state_c>)
        .update();
}

int main()
{
    static_assert(run_machine() == -1);
}