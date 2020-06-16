set N := {read "n.txt" as "<1n>"};
set R := {read "r.txt" as "<1n>"};

param XS[N] := read "finalx.txt" as "<1n> 2n";
param YS[N] := read "finaly.txt" as "<1n> 2n";
param a := read "R_rr.txt" as "1n";

var XR[R] real;
var YR[R] real;
var X[N*R] binary;
var Z[R] binary;
var temp01[N] binary;

maximize f: sum <n> in N: sum <r> in R: X[n,r];

subto const1: forall <r> in R: forall <n> in N: X[n,r] <= Z[r];
subto const2: forall <n> in N: forall <r> in R: XS[n] - XR[r] <= a + (1-X[n,r])*100000;
subto const3: forall <n> in N: forall <r> in R: XR[r] - XS[n] <= a + (1-X[n,r])*100000;
subto const4: forall <n> in N: forall <r> in R: YS[n] - YR[r] <= a + (1-X[n,r])*100000;				
subto const5: forall <n> in N: forall <r> in R: YR[r] - YS[n] <= a + (1-X[n,r])*100000;
subto const6: forall <r> in R: XR[r] <= Z[r]*100000;
subto const7: forall <r> in R: YR[r] <= Z[r]*100000;
subto const8: sum <r> in R: Z[r]==1;	










