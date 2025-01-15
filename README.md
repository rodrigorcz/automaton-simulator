# Automaton Simulator

Simulator for Deterministic (DFA) and Non-deterministic (NFA) Finite Automata.

## Input File Instructions

### Format:

1. **First Line**:  
   Number of states (`n`), named `q0` to `qn−1`. \(1 \leq n \leq 10\). `q0` is the initial state for a DFA.

2. **Second Line**:  
   Terminal symbols (`Σ`): Enter the count followed by symbols (max 10).

3. **Third Line**:  
   Number of initial states (e.g., `q0` for DFA, `q0 q1` for NFA; max 10).

4. **Fourth Line**:  
   Accepting states (`F`): Count followed by states (0-9).

5. **Fifth Line**:  
   Number of transitions (`δ`, max 50).

6. **From Sixth Line**:  
   Transitions in the format: q x q' , Where `x ∈ Σ ∪ {λ}`. Use `-` for `λ`.

7. **Line After Transitions**:  
   Number of input strings (max 10).

8. **Next Lines**:  
   Input strings: One per line, up to 20 symbols each.

## Example

![Screenshot From 2025-01-03 19-34-22](https://github.com/user-attachments/assets/d3712073-7bd4-4f16-aee8-8285b414c320)

Input File:

```
3
2 a b
1
1 2
6
0 a 1
0 b 1
1 a 1
1 b 2
2 a 0
2 b 2
10
abbbba
aabbbb
bbabbabbabbb
bbbbbbbbbbb
-
abababababab
bbbbaabbbb
abba
a
aaa
```

Output:

```
reject
accepted
accepted
accepted
reject
reject
accepted
reject
reject
reject
```


