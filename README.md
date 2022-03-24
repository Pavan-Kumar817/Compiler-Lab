# Compiler Lab
FIRST and FOLLOW programs are written from the following algorithms:

## FIRST
>To compute FIRST(X) for all grammar symbols X, apply the following rules until no more terminals or ε can be added to any FIRST set.
>1. If X is a terminal, then FIRST(X) = {X}.
>2. If X is a nonterminal and X ! Y1Y2 ... Yk is a production for some k >= 1, then place a in FIRST(X) if for some i, a is in FIRST(Yi), and  is in all of FIRST(Y1); : : : ; FIRST(Yi�-1); that is, Y1    Yi􀀀1 )  . If  is in FIRST(Yj ) for all j = 1; 2; : : : ; k, then add  to FIRST(X). For example, everything in FIRST(Y1) is surely in FIRST(X). If Y1 does not derive , then we add nothing more to FIRST(X), but if Y1 )  , then we add FIRST(Y2), and
so on.
>3. If X !  is a production, then add  to FIRST(X).
