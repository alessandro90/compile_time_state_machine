#ifndef MACHINE_CONCEPTS_HPP
#define MACHINE_CONCEPTS_HPP

#include <type_traits>

namespace ctsm
{
    template <typename State, typename Machine>
    concept MachineState = requires(State state, Machine machine)
    {
        {state.update(machine)};
    };

    template <typename State, typename... Args>
    concept ConstructibleWith = std::is_constructible_v<State, Args...>;
}
#endif