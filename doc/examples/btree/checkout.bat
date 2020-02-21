del key.dat
del data.dat
rem "generate and retrieve NBR_ITERATIONS keys"
call mdh btest1
btest1
rem "retrieve NBR_ITERATIONS keys stored by prior step"
call mdh btest2
btest2
del key.dat
del data.dat
rem "generate and retrieve NBR_ITERATIONS random keys"
call mdh btest3
btest3
del key.dat
del data.dat
rem "generate and XNEXT thru NBR_ITERATIONS random keys"
rem "number of unique keys depends on rand() and may be less than"
rem "NBR_ITERATIONS"
call mdh btest4
btest4
del key.dat
del data.dat
rem "same as prior but PREVIOUS operation"
call mdh btest5
btest5
del key.dat
del data.dat
rem "same as prior but count keys operation"
call mdh btest6
btest6
del key.dat
del data.dat
rem "same as prior but XNEXT and count keys operation"
call mdh btest7
btest7
del key.dat
del data.dat
rem "kill a key and recount"
call mdh btest8
btest8
