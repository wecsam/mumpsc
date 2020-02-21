//#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//#+    Mumps Compiler Run-Time Support Functions
//#+    Copyright (c) A.D. 2001, 2002 by Kevin C. O'Kane
//#+    okane@cs.uni.edu
//#+
//#+    This library is free software; you can redistribute it and/or
//#+    modify it under the terms of the GNU Lesser General Public
//#+    License as published by the Free Software Foundation; either
//#+    version 2.1 of the License, or (at your option) any later version.
//#+
//#+    This library is distributed in the hope that it will be useful,
//#+    but WITHOUT ANY WARRANTY; without even the implied warranty of
//#+    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//#+    Lesser General Public License for more details.
//#+
//#+   You should have received a copy of the GNU Lesser General Public
//#+    License along with this library; if not, write to the Free Software
//#+    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//#+
//#+    http://www.cs.uni.edu/~okane
//#+
//#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/* rdbms.c - Mumps Runtime Library
 *
 * Mumps Relational DataBase Management System InterFace
 * -----------------------------------------------------
 * This portion of the runtime implements extensions in this Mumps
 * compiler to interface to PostgreSQL and ODBC.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <mumpsc/config.h>
#include <mumpsc/fcns.h>
#include <mumpsc/global.h>

#ifdef SQL
#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#endif

/* HAVE_PGSQL_H is created by autoconfigure and contains the
 * name of the include subdirectory containing the psql code */

#if ALLOW_POSTGRES==0
#undef POSTGRES
#endif

#if HAVE_PGSQL_H!=NO&&ALLOW_POSTGRES==1
      #ifndef POSTGRES
            #define POSTGRES
            #endif
      #endif

#ifdef POSTGRES
	#if HAVE_PGSQL_H == POSTGRESQL
		#include <postgresql/libpq-fe.h>
		#endif
	#if HAVE_PGSQL_H==PGSQL
		#include <pgsql/libpq-fe.h>
		#endif
	#endif


#define _XOPEN_SOURCE

#ifndef _MSC_VER
#include <unistd.h>
#endif

/* The only wonderful global...*/
extern int ierr;

/*===========================================================================*
 *                                    sql                                    *
 *===========================================================================*/
int sql(char *DataSourceName,
        char *User, char *Password, char *Command, char *MumpsArray)
{

#ifdef SQL

/*#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 *#+ WindowsXX SQL ODBC Section -
 *#+ See below for PostgreSQL Interface.
 *#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

    HENV env;
    HDBC dbc;
    HSTMT stmt;
    UCHAR *x[90];
    SWORD cb1;
    UCHAR err[160];
    SWORD cols = 0;

    int r, i, j, tpl;
    unsigned char gbl[512];

    SQLAllocEnv(&env);

    i = SQLAllocConnect(env, &dbc);

    if (i != SQL_SUCCESS) {

        printf("\n*** SQLAllocConnect error in or near line %d\n",
               LineNumber);

        if (i == SQL_ERROR) {
            SQLError(env, dbc, SQL_NULL_HSTMT, NULL, NULL, err,
                     sizeof(err), NULL);
            printf("\n*** Error: %s\n", err);
        }

        return -1;
    }

    i = SQLConnect(dbc,
                   DataSourceName, SQL_NTS,
                   User, SQL_NTS, Password, SQL_NTS);

    if (i != SQL_SUCCESS) {
        printf("\n*** SQLConnect Error in or near line %d\n", LineNumber);
        printf("\n*** DataSourceName %s\n", DataSourceName);
        printf("\n*** User %s\n", User);
        printf("\n*** Password %s\n", Password);

        if (i == SQL_ERROR) {
            SQLError(env, dbc, SQL_NULL_HSTMT, NULL, NULL, err,
                     sizeof(err), NULL);
            printf("\n*** Error: %s\n", err);
        }
        return -1;
    }

    i = SQLSetConnectOption(dbc, SQL_AUTOCOMMIT, FALSE);

    if (i != SQL_SUCCESS) {
        printf("\n*** SQLSetConnect Error in or near line %d\n",
               LineNumber);
        if (i == SQL_ERROR) {
            SQLError(env, dbc, SQL_NULL_HSTMT, NULL, NULL, err,
                     sizeof(err), NULL);
            printf("\n*** Error: %s\n", err);
        }
        return -1;
    }

    i = SQLAllocStmt(dbc, &stmt);

    if (i != SQL_SUCCESS) {
        printf("\n*** SQLAllocStmt Error in or near line %d\n",
               LineNumber);
        if (i == SQL_ERROR) {
            SQLError(env, dbc, SQL_NULL_HSTMT, NULL, NULL, err,
                     sizeof(err), NULL);
            printf("\n*** Error: %s\n", err);
        }
        return -1;
    }

    i = SQLExecDirect(stmt, Command, SQL_NTS);

    if (i != SQL_SUCCESS && i != SQL_SUCCESS_WITH_INFO) {
        unsigned char err1[128];
        SDWORD err2;
        printf("\n*** SQLExecDirect Error");
        SQLError(env, dbc, stmt, err1, &err2, err, sizeof(err), NULL);
        printf("\n*** Error: %s\n", err);
        return -1;
    }

    if (strlen(MumpsArray) == 0) {      //#+ No array name passed
        i = SQLTransact(env, dbc, SQL_COMMIT);
        if (i != SQL_SUCCESS) {
            printf("\n*** SQLExecDirect Error in or near line %d\n",
                   LineNumber);
            if (i == SQL_ERROR) {
                SQLError(env, dbc, SQL_NULL_HSTMT, NULL, NULL, err,
                         sizeof(err), NULL);
                printf("\n*** Error: %s\n", err);
            }
            return -1;
        }
        goto exit;
    }

/*#+++++++++++++++++++++++++++++
 *#+ Retrieve number of colomns
 *#+++++++++++++++++++++++++++*/

    i = SQLNumResultCols(stmt, &cols);

    if (i != SQL_SUCCESS) {
        printf("\n*** SQLNumResultCols Error\n");
        if (i == SQL_ERROR) {
            SQLError(env, dbc, SQL_NULL_HSTMT, NULL, NULL, err,
                     sizeof(err), NULL);
            printf("\n*** Error: %s\n", err);
        }
        return -1;
    }

/*#+++++++++++++++++++++++++++++++++++++++++++
 *#+ Allocate and bind memory for column data
 *#+++++++++++++++++++++++++++++++++++++++++*/

    for (j = 0; j < cols; j++) {
        x[j] = (UCHAR *) malloc(512);
        i = SQLBindCol(stmt, j + 1, SQL_C_CHAR, x[j], 50, &cb1);

        if (i != SQL_SUCCESS) {
            printf("\n*** SQLBindCol Error\n");
            if (i == SQL_ERROR) {
                SQLError(env, dbc, SQL_NULL_HSTMT, NULL, NULL, err,
                         sizeof(err), NULL);
                printf("\n*** Error: %s\n", err);
            }
            return -1;
        }
    }

/*#++++++++++++++++++++++++++++++++++++
 *#+ Retrieve rows and store in global
 *#++++++++++++++++++++++++++++++++++*/

    r = 0;
    tpl = 0;
    while (1) {

        char ct[32];
        char val[STR_MAX];
        unsigned char *item;
        int ii;

/*#++++++++++++++++++++++++++
 *#+ Build global array name
 *#++++++++++++++++++++++++*/

        strmove(gbl, MumpsArray);
        tpl++;
        sprintf(ct, "%d\x00", tpl);
        for (ii = 0; gbl[ii] != 0; ii++);
        gbl[ii] = 1;
        gbl[ii + 1] = 0;        /*#+ Coded delimiters */
        strcat(gbl, ct);
        for (ii = 0; gbl[ii] != 0; ii++);
        gbl[ii] = 1;
        gbl[ii + 1] = 0;        /*#+ Coded delimiters */

/*#+++++++++++++++++
 *#+ Fetch next row
 *#+++++++++++++++*/

        i = SQLFetch(stmt);
        if (i != SQL_SUCCESS)
            break;
        i = 0;

        for (j = 0; j < cols; j++)
            i = strlen(x[j]) + i;

        if (i + strlen(gbl + j) > 500) {
            printf("\n*** SQL Overflow\n");
            printf("\n*** Row too long\n");
            return -1;
        }

        strmove(val, "");

        for (j = 0; j < cols; j++) {
            strcat(val, x[j]);
            strcat(val, DELIM);
        }

        r++;
        Mglobal (1, gbl, val, svPtr);
    }

/* SQLTransact( env, dbc, SQL_ROLLBACK ); */
/* SQLTransact( env, dbc, SQL_COMMIT ); */

  exit:

    SQLFreeStmt(stmt, SQL_DROP);
    SQLDisconnect(dbc);
    SQLFreeConnect(dbc);
    SQLFreeEnv(env);

    if (cols > 0)
        for (j = 0; j < cols; j++)
            free(x[j]);

    bd[1] = 0;
    return r;                   //#+ Number of rows

/*#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 *#+++++++++++++ End of ODBC Interface ++++++++++++++++++++++++++++++++++
 *#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#endif
#ifdef POSTGRES

/*#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 *#+ PostgreSQL Interface Section
 *#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

    unsigned char gbl[512];
    PGconn *p1;
    PGresult *p2;
    int i, j, nt = 0, nf = 0;

    p1 = PQsetdbLogin(NULL,     /* pghost */
                      NULL,     /* pgport */
                      NULL,     /* pgoptions */
                      NULL,     /* pgtty */
                      DataSourceName,   /* dbname */
                      NULL,     /* login */
                      NULL);    /* pwd */

    if (p1 == NULL) {
        printf("*** Null connect\n");
        return -1;
    }

    p2 = PQexec(p1, Command);

    if (p2 == NULL) {
        printf("*** Null result\n");
        printf("%s\n", PQerrorMessage(p1));
        return -1;
    }

    if (strlen(MumpsArray) > 0 && PQresultStatus(p2) == PGRES_TUPLES_OK) {

/*#+===================================================================
 *#+ The following section copies the PostgreSQL results to a Mumps
 *#+ global array (MumspArray).  By default, it places successive
 *#+ rows retrieved from the server into successive array elements.
 *#+ Thus, if MumpsArray="Test", the results will be in ^Test(1),
 *#+ ^Test(2), ... ^Test(n) where "n" is the returned value from
 *#+ $zodbc.  Columns form the server concatenated with one another
 *#+ with an intervening delimiter.  Use $piece to separate.
 *#+=================================================================*/

        nt = PQntuples(p2);
        nf = PQnfields(p2);

        for (i = 0; i < nt; i++) {
            char ct[32];
            char val[STR_MAX];
            unsigned char *item;
            int ii;
            strmove(gbl, (unsigned char *) MumpsArray);
            sprintf(ct, "%d\x00", i + 1);
            for (ii = 0; gbl[ii] != 0; ii++);
            gbl[ii] = 1;
            gbl[ii + 1] = 0;
            strcat((char *) gbl, ct);
            for (ii = 0; gbl[ii] != 0; ii++);
            gbl[ii] = 1;
            gbl[ii + 1] = 0;

            strmove((unsigned char *) val, (unsigned char *) "");

            for (j = 0; j < nf; j++) {
                item = (unsigned char *) PQgetvalue(p2, i, j);
                strcat(val, (char *) item);
                strcat(val, DELIM);
            }
            Mglobal (1, gbl, (unsigned char *) val, svPtr);
        }
    }

    PQfinish(p1);
    ierr = 0;
    return nt;

/*#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 *#++++++++++++ End of PostgreSQL Interface +++++++++++++++++++++++++++++
 *#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#else
    return 0;                   /* Function is empty and returns 0 if both SQL and POSTGRES are 0 */
#endif
}
