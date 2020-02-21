#include <mumpsc/builtinTable.h>

struct MSV;

void Getenv(unsigned char *, unsigned char *);
char * Cosine (struct MSV *, char *, char *, char *);
char * Sim1 (struct MSV *, char *, char *, char *);
char * Dice (struct MSV *, char *, char *, char *);
char * Jaccard (struct MSV *, char *, char *, char *);
char * Avg (struct MSV *, char *, char *);
char * Count (struct MSV *, char *, char *);
char * Scan(struct MSV *, char *);
// char * ScanAlnum(struct MSV *, char *);
char * ScanAlnum(struct MSV *, char *, char * = NULL );
char * Max (struct MSV *, char *, char *);
char * Input (struct MSV *, char *, char *);
char * Min (struct MSV *, char *, char *);
char * Multiply (struct MSV *, char *, char *, char *, char *);
char * Sum (struct MSV *, char *, char *);
char * Transpose (struct MSV *, char *, char *, char *);
char * SmithWaterman (struct MSV *, char *, char * s1, char *t1 , 
      char *sa, char *sm, char *gap, char *mm, char *ma);
char * IDF (struct MSV *, char *, char *, char *);
char * TermCorrelate (struct MSV *, char *, char *, char *);
char * DocCorrelate (struct MSV *, char *, char *, char *, char *, char *);
char * StopInit (struct MSV *, char *, char *);
void   StopInit (char *);
char * StopLookup (struct MSV *, char *, char *);
int    StopLookup (char *);
char * SynInit (struct MSV *, char *, char *);
char * SynLookup (struct MSV *, char *, char *);
char * Centroid (struct MSV *, char *, char *, char *);
char * BMGSearch (struct MSV *, char *, char *, char *);
char * Shred (struct MSV*, char * ep, char *arg1, char *arg2);
char * ShredQuery (struct MSV*, char * ep, char *arg1, char *arg2);
char * Replace(struct MSV*, char * ep, char *arg1, char * arg2, char *arg3);

