#include <type_traits>
#include <utility>

#include "types/typelist.hpp"
#include "types/transition.hpp"
#include "types/utilities.hpp"
#include "types/machne_concepts.hpp"

namespace ctsm
{
    template <typename...>
    class state_machine_t;

    template <typename CurrentState, typename... Events, typename... States>
    class state_machine_t<CurrentState, tr::transition_t<Events, States>...>
    {

        static_assert(std::conjunction_v<utils::is_unqualified<Events>...>, "Only unqualified types allowed");
        static_assert(std::conjunction_v<utils::is_unqualified<States>...>, "Only unqualified types allowed");
        static_assert(utils::unique_t<Events...>::value, "Events must be unique");

    public:
        using transition_map_t = tl::typelist_t<tr::transition_t<Events, States>...>;

        template <typename... Args>
        constexpr explicit state_machine_t(Args... args) requires ConstructibleWith<CurrentState, Args...>
            : m_state{std::forward<Args>(args)...} {}

        template <typename Event, typename State>
        constexpr auto addTransition(tr::transition_t<Event, State>) const &&
        {
            return state_machine_t<CurrentState,
                                   tr::transition_t<Events, States>...,
                                   tr::transition_t<Event, State>>{std::move(m_state)};
        }

        template <typename Event, typename... Args>
        static constexpr auto on(Args &&...args)
        {
            using state_t = typename tr::get_by_event_t<Event, transition_map_t>::typelist::type::state_t;
            static_assert(std::is_constructible_v<state_t, Args...>, "Invalid construction parameters");
            return state_machine_t<state_t, tr::transition_t<Events, States>...>{std::forward<Args>(args)...};
        }

        constexpr decltype(auto) update() const requires MachineState<CurrentState, state_machine_t>
        {
            return m_state.update(*this);
        }

        constexpr auto &state() noexcept { return m_state; }
        constexpr auto const &state() const noexcept { return m_state; }

    private:
        CurrentState m_state;
    };

    template <typename...>
    struct builder_t;

    template <typename CurrentState, typename... Events, typename... States>
    struct builder_t<CurrentState, tr::transition_t<Events, States>...>
    {
        template <typename... Args>
        static constexpr auto build(Args... args) requires ConstructibleWith<CurrentState, Args...>
        {
            return state_machine_t<CurrentState, tr::transition_t<Events, States>...>{std::forward<Args>(args)...};
        }
    };
}
