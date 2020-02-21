# Makefile to generate pattern-matcher test coverage figures
# Caution: Relative paths in use; do not try to invoke make on this
#          Makefile from a different directory

pm.c.gcov: pmtest
	./pmtest
	gcov ../pm.c

pmtest: pmtest.c
	$(CC) -c -fprofile-arcs -ftest-coverage ../pm.c
	$(CC) -c ../bstring.c
	$(CC) -o pmtest pmtest.c pm.o bstring.o -lpcre

clean:
	$(RM) *.[oas] *~ *.bb* *.da *.gcov pmtest
