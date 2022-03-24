# Compiler Lab
FIRST and FOLLOW programs are written from the following algorithms:

## FIRST
>To compute FIRST(X) for all grammar symbols X, apply the following rules until no more terminals or ε can be added to any FIRST set.
>1. If X is a terminal, then FIRST(X) = {X}.
>2. If X is a nonterminal and X → Y<sub>1</sub>Y<sub>2</sub> ... Y<sub>k</sub> is a production for some k ≥ 1, then place *a* in FIRST(X) if for some i, *a* is in FIRST(Y<sub>i</sub>), and  is in all of FIRST(Y<sub>1</sub>) , . . . . , FIRST(Y<sub>i-1</sub>); that is, Y<sub>1</sub> . . . Y<sub>i-1</sub> ⇒ ε. If ε is in FIRST(Y<sub>j</sub>) for all j = 1, 2, . . . , k, then add ε to FIRST(X). For example, everything in FIRST(Y<sub>1</sub>) is surely in FIRST(X). If Y<sub>1</sub> does not derive ε, then we add nothing more to FIRST(X), but if Y<sub>1</sub> ⇒ ε, then we add FIRST(Y2), and
so on.
>3. If X → ε is a production, then add ε to FIRST(X).

## FOLLOW
>To compute FOLLOW(A) for all nonterminals A, apply the following rules until nothing can be added to any FOLLOW set.
>1. Place $ in FOLLOW(S), where S is the start symbol, and $ is the input
right endmarker.
>2. If there is a production A → αBβ, then everything in FIRST(β) except ε is in FOLLOW(B).
>3. If there is a production A → αB, or a production A → αBβ, where FIRST(β) contains ε, then everything in FOLLOW(A) is in FOLLOW(B).

These algorithms are taken from **Compilers: Principles, Techniques, & Tools by Alfred V. Aho, Monica S. Lam, Ravi Sethi, Jeffrey D. Ullman**, *Second Edition*
