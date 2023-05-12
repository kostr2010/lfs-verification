import spot
import sys

# use: python3 verify_trace.py /path/to/trace/ /path/to/automata


def check_transition(automata, prev: int, next: int) -> bool:
    for s in range(automata.num_states()):
        for t in automata.out(s):
            if int(t.src) == int(prev) and int(t.dst) == int(next):
                return True
    return False


def check_trace(trace_path: str, automata_path: str) -> bool:
    automata = spot.automaton(automata_path)

    trace = []
    with open(trace_path) as trace:
        trace = trace.readline()

    # 0 - push, 1 - pop
    count_push_pops = [0, 0]

    count_push_pops[int(trace[0])] += 1

    for i in range(1, len(trace)):
        count_push_pops[int(trace[i])] += 1

        assert check_transition(automata, int(trace[i - 1]), int(trace[i]))

    assert count_push_pops[0] == count_push_pops[1]


def main():
    assert len(sys.argv) == 3

    trace_path = sys.argv[1]
    automata_path = sys.argv[2]

    check_trace(trace_path, automata_path)


if __name__ == "__main__":
    main()
