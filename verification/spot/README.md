# SPOT VERIFICATION

## THEORY

suppose simple sanity-check LTL formula for stack:

```
G(push -> F(pop)) # assert use
```

we can dump trace for our stack in order to check it against this formula. check is performed using automata generated by spot from given temporal formula

## USAGE

run

```
verify_trace.sh /path/to/trace
```

this script generates automata from LTL formula using spot cli tool `ltl2tgba` and proceeds to check given trace against this automaton

## TRACE

for example, trace is generated by running tests in `src` folder