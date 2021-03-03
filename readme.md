# Compile-Time State Machine

A quite short implementation of a compile-time state machine.
Transitions can be triggered externally via the `on` method or internally,
via the `update` method (see the examples in the `examples` folder).

---

*NOTE*: Requires C++20.

---

An example of usage taken from `examples/explicit_transitions.cpp`

```cpp
    constexpr auto m = builder_t<state_a>::build(1) // Utility builder. Initialize specified state with 1
                           .addTransition(transition_v<event_a, state_a>) // Each call return a new state machine
                           .addTransition(transition_v<event_b, state_b>)
                           .addTransition(transition_v<event_c, state_c>);
    constexpr auto m1 = m.on<event_b>(15); // Return a new state machine with a state initialized with 15
    static_assert(std::is_same_v<std::decay_t<delctype(m1.state())>, state_b>); // Will pass
```
