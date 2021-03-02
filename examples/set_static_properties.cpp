#include <type_traits>
#include "ctsm/state_machine.hpp"
#include "ctsm/types/typelist.hpp"

using namespace ctsm;
using namespace ctsm::tr;
using namespace ctsm::tl;

constexpr bool branch{false};

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
    static constexpr int update(auto const &machine)
    {
        if constexpr (branch)
        {
            return 1;
        }
        else
        {
            return machine.template on<event_b>().update();
        }
    }
};
struct state_b
{
    static constexpr int update(auto const &machine)
    {
        if constexpr (branch)
        {
            return 100;
        }
        else
        {
            return machine.template on<event_c>().update();
        }
    }
};

struct state_c
{
    static constexpr int update(auto const &)
    {
        if constexpr (branch)
        {
            return 1000;
        }
        else
        {
            return 10000;
        }
    }
};

static constexpr auto machine = builder_t<state_a>::build()
                                    .addTransition(transition_v<event_a, state_a>)
                                    .addTransition(transition_v<event_b, state_b>)
                                    .addTransition(transition_v<event_c, state_c>);

struct data
{
    inline static constexpr int value = machine.update();
};

int main()
{
    static_assert(data::value == 10000);
}