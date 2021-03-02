#ifndef CTSM_TRANSITION_HPP
#define CTSM_TRANSITION_HPP

#include "typelist.hpp"

namespace ctsm::tr
{
    template <typename Event, typename State>
    struct transition_t
    {
        using event_t = Event;
        using state_t = State;
    };

    template <typename Event, typename State>
    inline constexpr transition_t<Event, State> transition_v{};

    template <typename...>
    struct get_by_event_t;

    template <typename Event, typename... Events, typename... States>
    struct get_by_event_t<Event, tl::typelist_t<transition_t<Events, States>...>>
    {
    private:
        using head_list_t = typename tl::head_t<tl::typelist_t<transition_t<Events, States>...>>::typelist;
        using tail_list_t = typename tl::tail_t<tl::typelist_t<transition_t<Events, States>...>>::typelist;

    public:
        using typelist = std::conditional_t<std::is_same_v<Event,
                                                           typename head_list_t::type::event_t>,
                                            head_list_t,
                                            typename get_by_event_t<Event, tail_list_t>::typelist>;
    };

    template <typename Event>
    struct get_by_event_t<Event, tl::typelist_t<>>
    {
        using typelist = tl::typelist_t<>;
    };
}
#endif
