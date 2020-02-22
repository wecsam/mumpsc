AC_INIT([mumps.c.in])
echo
echo =================================================================
echo "Mumps Configuration Module Oct 27, 2015"
echo
echo "- perl compatible regular expression library required"
echo "  to be installed in /usr/include and /usr/lib"
echo "- bash required to be installed in /bin"
echo
echo "Copyright (c) 2013, 2015 Kevin C. O'Kane, All Rights Reserved"
echo "GNU GPL License Applies"
echo `date`
echo =================================================================
echo "Configure Line Options: [default]"
echo "--with-mysql-user=user  IP number of remote host [mumps]"
echo "--with-mysql-host=nbr   IP number of remote host [localhost]"
echo "--with-mysqldb          Enable MySQL data base for globals"
echo "--with-mysql            Enable MySQL access - globals are native"
echo "--with-mysql-passwd=val Select mysql user passwd [\"\"]"
echo "--with-mysql-port=nbr   Select mysql port [\"\"]"
echo "--with-mysql-socket=nbr Select mysql socket [\"\"]"
echo "--with-db-cred-prompt   Ask user on command line for DB credentials"

echo "--with-pgsql-user=user  posgresql user [mumps]"
echo "--with-pgsql-passwd=val Select pgsql user passwd [\"\"]"
echo "--with-pgsql=DIR      enables PostgreSQL [NO]"
echo "--with-pgsql-host     select host IP number"
echo "--with-pgdb           build using PostgreSQL database [NO]"
echo "--with-pgsql          programs will have access to postgreSQL"

echo "--with-dbname=name    SQL data base name [mumps]"
echo "--with-table=name     SQL table name for Mumps globals [mumps]"
echo "--with-indexsize=val  SQL DB index max [64]"
echo "--with-datasize=val   SQL DB max data storage item length [512]"
echo "--with-tabsize=nbr    number of columns in SQL table [10]"

echo "--with-client-server  client or server build"
echo "--with-client         build native btree client data base code"
echo "--with-standalone	    build standalone interpreter with database sharing"

echo "--with-slice=500      native btree file exclusive slice"
echo "--with-float-bits	    number of bits in a float mantissa"
echo "--with-float-digits   number of digits in float number"
echo "--with-hardware-math  use hardware arithmetic"
echo "--with-int-32"        use 32 bit integers
echo "--with-long-double"   use long double

echo "--with-includes=DIR   to identify header dirs (Apple)"
echo "--with-libraries=DIR  to identify libs (Apple)"
echo "--with-cache=VAL      native globals cache size [65537]"
echo "--with-ibuf=VAL       max size interpreted program [20000]"
echo "--with-strmax=VAL     max internal string size 4096"
echo "--with-block=VAL      native btree block size 2048"
echo "--with-readonly       native database ire read only"
echo "--with-server-dir     native btree server home directory"
echo "--with-server-buf     server exchange buffer size"
echo "--with-locale=locale  locale information"
echo "--with-terminate-on-error"

echo "--with-no-inline      disable inline functions"
echo "--with-profile        turn on profiler"
echo =================================================================

AC_COPYRIGHT([Kevin O'Kane])
AC_REVISION([17.23])
AC_HEADER_STDC
AC_CONFIG_HEADERS([include/mumpsc/config.h])

AC_CHECK_SIZEOF([long])

CPU64="no"

version=`cat VERSION`

if test $ac_cv_sizeof_long != 4
        then 
        CPU64="yes"
        fi

AC_PROG_CC([gcc])

if test $CC != "gcc" 
	then
        AC_MSG_ERROR([Missing gcc/g++ compiler])
	fi

INCLUDEDIR=""
IFS_COPY="$IFS"
IFS=":$IFS"
host="localhost";
user="mumps";
passwd="";
port="0";
socket="";
terminate_on_error="";
gbllib=mpsglobal_native
log2="log2"
client_server=""
intSize="long long"

#--------------------------------------------------------------

AC_ARG_WITH(profile,
   [ --with-profile],
   [ profile=" -pg ";  ],
   [ profile=""  ])

AC_ARG_WITH(long-double,
   [ --with-long-double],
   [ floatSize="#define BIGFLOAT";  ],
   [ floatSize=""  ])

AC_ARG_WITH(no-inline,
   [ --with-no-inline],
   [ inline=""; inlineDef="#define NO_INLINE"; ],
   [ inline="static inline"  ])

# AC_ARG_WITH(int-32,
#    [ --with-int-32],
#    [ intSize="long"; intFmt="ld"; intLong="#define intLong"; ],
#    [ intSize="long long"; intFmt="lld"  ])

AC_ARG_WITH(int-32,
   [ --with-int-32],
   [ intSize="int"; intFmt="d"; intLong="#define intLong"; ],
   [ intSize="long long"; intFmt="lld"  ])


AC_ARG_WITH(hardware-math,
   [ --with-hardware-math],
   [ hardwareMath="yes"; ],
   [ hardwareMath="no" ])

AC_ARG_WITH(slice,
   [ --with-slice number of native DB exclusive ops],
   [ slice="$withval" ],
   [ slice="500"])

AC_ARG_WITH(float-bits,
   [ --with-float-bits size of floating pt mantissa (72)],
   [ fp_bits="$withval" ],
   [ fp_bits="72"])

AC_ARG_WITH(float-digits,
   [ --with-float-digits nbr of digits in flt pt nbr],
   [ fp_digits="$withval" ],
   [ fp_digits="8"])

AC_ARG_WITH(pgsql-host,
   [ --with-pgsql-host elect host IP number],
   [ remotehost="$withval" ],
   [ remotehost="127.0.0.1"])

AC_ARG_WITH(pgsql-user,
   [ --with-pgsql-user elect pgsql user],
   [ user="$withval" ],
   [ user="mumps"])

AC_ARG_WITH(pgsql-passwd,
   [ --with-mysql-passwd elect pgsql passwd],
   [ passwd="$withval" ],
   [ passwd=""])

AC_ARG_WITH(pgsql, 
   [ --with-pgsql programs will have access to postgreSQL],
   [ PGSQL=yes; pginclude=$withval ],
   [ PGSQL=no ])

AC_ARG_WITH(pgdb,
   [ --with-pgdb builds PostgreSQL database],
   [ PGDB="yes"; PGSQL=yes; pginclude=$withval ],
   [ PGDB="no"  ])

AC_ARG_WITH(mysqldb,
   [ --with-mysqldb glbals in MySQL],
   [ MYSQLDB="yes"; MYSQL="yes"; ],
   [ MYSQLDB="no"  ])

# alternative value set above

AC_ARG_WITH(mysql-host,
   [ --with-mysql-host elect host IP number],
   [ remotehost="$withval" ],
   [ remotehost="$remotehost"])

# alternative value set above

AC_ARG_WITH(mysql-user,
   [ --with-mysql-user elect mysql user],
   [ user="$withval" ],
   [ user="$user" ])

# alternative value set above

AC_ARG_WITH(mysql-passwd,
   [ --with-mysql-passwd elect mysql passwd],
   [ passwd="$withval" ],
   [ passwd="$passwd"])

AC_ARG_WITH(mysql-port,
   [ --with-mysql-port elect mysql port],
   [ port="$withval" ],
   [ port="0" ])

AC_ARG_WITH(mysql-socket,
   [ --with-mysql-socket elect mysql socket],
   [ socket="$withval" ],
   [ socket=""])

AC_ARG_WITH(db-cred-prompt,
   [ --with-db-cred-prompt elect db cred prompt],
   [ db_cred_prompt="#define DBCREDPROMPT" ],
   [ db_cred_prompt="" ])

AC_ARG_WITH(datasize, 
   [ --with-datasize datasize for mumps globals],
   [ datasize=$withval],
   [ datasize="512"])

AC_ARG_WITH(dbname, 
   [ --with-dbname dbname for mumps globals],
   [ dbname=$withval],
   [ dbname="mumps"])

AC_ARG_WITH(tablename, 
   [ --with-table table name for mumps globals],
   [ tablename=$withval],
   [ tablename="mumps"])

AC_ARG_WITH(index_size,
   [ --with-indexsize SQL index max],
   [ index_size="$withval" ],
   [ index_size="64"])

#--------------------------------------------------------------

AC_ARG_WITH(readonly,
   [ --with-readonly],
   [ readonly="#define READ_ONLY"; ],
   [ readonly=""  ])

AC_ARG_WITH(terminate_on_error,
   [ --with-terminate-on-error halt on error],
   [ terminate_on_error="#define TERMINATE_ON_ERROR"; ],
   [ terminate_on_error=""  ])

AC_ARG_WITH(locale,
   [ --with-locale locale information],
   [ locale="$withval" ],
   [ locale="en_US.UTF-8"])

AC_ARG_WITH(server-buf,
   [ --with-server-buf elect alt server buf],
   [ serverbuf="#define SERVERBUF $withval" ],
   [ serverbuf="#define SERVERBUF 1024" ])

AC_ARG_WITH(server-dir,
   [ --with-server-dir elect alt sever dir],
   [ serverdir="$withval" ],
   [ serverdir="/etc/mumps" ])

AC_ARG_WITH(client,
   [ --with-client builds client],
   [ client="#define CLIENT" ],
   [ client=""  ])

AC_ARG_WITH(client_server,
   [ --with-client-server client server build],
   [ client_server="#define NATIVE_CLIENT_SERVER" ],
   [ client_server=""  ])

if test "$client" = ""; 
	then
	client1="0"
	else
	client1="1"
	fi

AC_ARG_WITH(standalone,
   [ --with-standalone client server build],
   [ standalone="#define NATIVE_STANDALONE" ],
   [ standalone=""  ])

AC_ARG_WITH(tabsize, 
   [ --with-tabsize PostgreSQL table size for mumps globals],
   [ tabsize=$withval],
   [ tabsize="10"])

AC_ARG_WITH(block, 
   [ --with-block=VAL size of btree block for native globals],
   [ block=$withval],
   [ block="2048"])

AC_ARG_WITH(strmax, 
   [ --with-strmax=VAL max size internal string],
   [ str_max=$withval],
   [ str_max="10000"])

AC_ARG_WITH(ibuf, 
   [ --with-buf=VAL size of cache for interpreter],
   [ ibuf=$withval],
   [ ibuf="32000"])

AC_ARG_WITH(cache, 
   [ --with-cache=VAL size of cache for native globals],
   [ cache=$withval],
   [ cache="65537"])

AC_ARG_WITH(file64, 
   [ --with-file64 programs will use 64 bit file addressing],
   [ file64="-D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE"],
   [ file64="-D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE"])

AC_ARG_WITH(includes,
   [  --with-includes=DIR     colon-separated list of header directories],
   [  for dir in $withval
      do
         CPPFLAGS="-I$dir $CPPFLAGS"
      done ])

AC_ARG_WITH(libraries,
   [  --with-libraries=DIR    colon-separated list of library directories],
   [  for dir in $withval
      do
         LDFLAGS="-L$dir $LDFLAGS"
      done])

IFS="$IFS_COPY"

AC_CHECK_FUNC(gcvt,[AC_DEFINE(HAVE_GCVT,YES)])

# check if Cygwin is present

CYGWIN="no"
AC_CHECK_HEADER([sys/cygwin.h],[AC_DEFINE(HAVE_CYGWIN,YES) CYGWIN=yes],[])

if test $PGDB = "yes"; then
        AC_CHECK_HEADER([$pginclude/libpq-fe.h],[AC_DEFINE(HAVE_POSTGRES_H,YES)],
	[AC_MSG_ERROR([Missing x POSTGRESQL headers])])
        fi

# check for extended precision headers

if test $hardwareMath = "no"; 
	then
	AC_CHECK_HEADER([gmp.h],[AC_DEFINE(HAVE_GMP,YES) gmp="yes" ],
	[AC_MSG_WARN([Missing GNU Multiprecision arithmetic library development headers]); hardwareMath="yes"; gmp="no"])

	AC_CHECK_HEADER([mpfr.h],[AC_DEFINE(HAVE_MPFR,YES) mpfr="yes" ],
	[AC_MSG_WARN([Missing GNU Multiple precision floating point computation headers]); hardwareMath="yes"; mpfr="no"])
	fi

AC_CHECK_HEADER([readline/readline.h],[AC_DEFINE(HAVE_UNISTD_H,YES)],[AC_MSG_ERROR([Missing readline.h headers])])

AC_CHECK_HEADER([unistd.h],[AC_DEFINE(HAVE_UNISTD_H,YES)],[AC_MSG_ERROR([Missing unistd.h headers])])

if test "$CYGWIN" = "no"
	then
	AC_CHECK_HEADER([pcre.h],[AC_DEFINE(HAVE_PCRE_H,YES)],[AC_MSG_ERROR([Missing pcre.h headers])])
	AC_CHECK_LIB(pcre,pcre_exec,[AC_DEFINE([HAVE_PCRE])],[AC_MSG_ERROR([Missing Perl Compatible Regular Expression Library])])
	fi

# if test $PGSQL = "yes"; then
# PGSQL="no";
# AC_CHECK_HEADER([libpq-fe.h],[AC_DEFINE(HAVE_PGSQL_H,YES) PGSQL=yes],[AC_MSG_WARN([libpq-fe.h not found])])
# AC_MSG_RESULT([PostgreSQL headers found: $PGSQL])
# AC_CHECK_LIB(pq,PQsetdbLogin,[AC_DEFINE([HAVE_POSTGRESQL])],[AC_MSG_WARN([Missing PostgreSQL - PostgreSQL functions unavailable])])
# fi

ftello="ftell"
AC_CHECK_LIB(c,ftello,[AC_DEFINE([HAVE_ftello]) ftello=ftello],[AC_MSG_WARN([Missing ftello - ftello functions unavailable])])

fseeko="fseek"
AC_CHECK_LIB(c,fseeko,[AC_DEFINE([HAVE_fseeko]) fseeko=fseeko],[AC_MSG_WARN([Missing fseeko - fseeko functions unavailable])])

log2="log"
AC_CHECK_LIB(m,log2,[AC_DEFINE([HAVE_log2]) log2=log2],[AC_MSG_WARN([Missing log2 - using log])])

if test "$prefix" = "NONE"; then
	# where to place the software if prefix= not specified
	prefix="$HOME/mumps_compiler"
	fi

# switch to hardware math if either library is missing

if test $hardwareMath = "no"; then
	if test $mpfr = "no"; then
		hardwareMath="yes"
		fi
	if test $gmp = "no"; then
		hardwaremath="yes"
		fi
	fi

if test $hardwareMath = "yes"; then
	AC_DEFINE([HAVE_HARDWARE_MATH])
	fi

mathLink=""
if test $hardwareMath = "no"; then
	# link libraries to extended precision package
	mathLink="-lgmp -Lx86-64-linux-gnu -lmpfr"
	fi

echo
echo ============== summary ========================

AC_MSG_RESULT([prefix defined as: $prefix])

use_postgres="";
use_mysql=""
mysql_cflags=""
mysql_cppflags=""
allow_pgsql=0


if test "$MYSQLDB" = "yes"; then
	echo "MySQL globals enabled"
	use_mysql="-DMYSQLDB"
	else
	echo "MYSQL not enabled"
	fi

if test "$PGSQL" = "yes"; then
	echo "postgreSQL enabled"
	use_postgres="-DPOSTGRES"
	postgresdb="-lpq"
	allow_pgsql=1
	else
	echo "postgreSQL not enabled"
	fi

dbtype="#define NATIVE"

if test $PGDB = "yes"; then
	postgresdb="-lpq"
	dbtype="#define POSTGRESSDB"
	fi

if test $MYSQLDB = "yes"; then
   mysql_cppflags="-DBIG_JOINS=1 -fno-strict-aliasing -g -DNDEBUG -I/usr/include/mysql/ \
	-Iinclude/ -L/usr/lib/x86_64-linux-gnu -lmysqlclient -lpthread -lz -lm -ldl"

   mysql_cflags="-DBIG_JOINS=1 -fno-strict-aliasing -g -DNDEBUG -I/usr/include/mysql/ \
	-Iinclude/ -L/usr/lib/x86_64-linux-gnu -lmysqlclient -lpthread -lz -lm -ldl"

   dbtype="#define MYSQLDB"
   fi

LONG="long"
LIB="lib"

if test $CPU64 = "yes"; then
	LONG="int"
	LIB="lib"
	file64="-D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE"
	fi

if test "$file64" = "" ;
	then
	echo "64 bit file addressing not in effect"
	adsize=4
	else
	echo "64 bit file addressing in effect"
	adsize=8
	fi

f=0
for x in 9 17 33 65 129 257 513 1025 2049 4197 8193 16385 32769 65537 131073 262145 524289 1048577
      do
      if test $cache = $x
            then
            f=1
            fi
      done

if test $f = 0 
then
      echo "Cache Error - bad size for cache - $cache"
      echo "Cache Error - cache must be 9 17 33 65 129 257 513 1025 2049 4197 8193 16385 32769 65537 131073 262145 524289 1048577"
      echo "Cache Error - cache reset to 1025"
      cache=1025
      fi

f=0
for x in 1024 2048 4096 8192 16384 32768 65536 131072 262144 524288 1048576 2097152
      do
      if test $block = $x
            then
            f=1
            fi
      done

if test $f = 0 
then
      echo "Block Error - bad size for block - $block"
      echo "Block Error - block must be 1024 2048 4096 8192 16384 32768 65536 131072 262144 524288 1048576 2097152"
      echo "Block Error - block reset to 1024"
      block=1024
      fi

if test $ibuf -lt 4096
then
      echo "Ibuf Error - ibuf too small - $ibuf"
      echo "Ibuf Error - ibuf reset to 4096"
      ibuf=4096
      fi

bin_install="-s"

cygwin=""
interpmod="mumps.cpp"
cygwinrename=""
mode="-m 755"

if test "$CYGWIN" = "yes"
      then
      cygwin="#define CYGWIN"
      cygext=".exe"
      bin_install=""
      interpmod="dosmumps.mps"
      cygwinrename="mv dosmumps.exe mumps.exe"
      mode=""
      echo "Cygwin found"
      fi


iomod=""
mumps2c="mumps2c"
dosprefix="c:\mumpsc"

echo "Hardware Math: $hardwareMath"
echo "MPFR headers $mpfr"
echo "GMP headers $gmp"
echo "Native globals cache size=$cache"
echo "Max interpreter program=$ibuf"
echo "Max internal string size=$str_max"
echo "Native globals btree block size=$block"
echo "Global array integer type=$LONG"
echo "CPU64 = $CPU64"
echo "Table size (RDBMS only) $tabsize"
echo "======================================================="
echo $user

echo ===============================================
echo

AC_SUBST(hardwareMath)
AC_SUBST(mathLink)
AC_SUBST(fp_bits)
AC_SUBST(fp_digits)
AC_SUBST(client)
AC_SUBST(client_server)
AC_SUBST(standalone)
AC_SUBST(client1)
AC_SUBST(db_cred_prompt)
AC_SUBST(use_postgres)
AC_SUBST(use_mysql)
AC_SUBST(mysql_cflags)
AC_SUBST(mysql_cppflags)
AC_SUBST(prefix)
AC_SUBST(CPPFLAGS)
AC_SUBST(LDFLAGS)
AC_SUBST(gbllib)
AC_SUBST(file64)
AC_SUBST(adsize)
AC_SUBST(slice)
AC_SUBST(cache)
AC_SUBST(ibuf)
AC_SUBST(allow_pgsql)
AC_SUBST(str_max)
AC_SUBST(block)
AC_SUBST(cygwin)
AC_SUBST(iomod)
AC_SUBST(bin_install)
AC_SUBST(mumps2c)
AC_SUBST(pcre_install)
AC_SUBST(dosprefix)
AC_SUBST(ftello)
AC_SUBST(fseeko)
AC_SUBST(log2)
AC_SUBST(LONG)
AC_SUBST(LIB)
AC_SUBST(cygext)
AC_SUBST(dbtype)
AC_SUBST(postgresdb)
AC_SUBST(pginclude)
AC_SUBST(dbname)
AC_SUBST(tablename)
AC_SUBST(tabsize)
AC_SUBST(indexsize)
AC_SUBST([serverdir])
AC_SUBST([serverbuf])
AC_SUBST([interpmod])
AC_SUBST([locale])
AC_SUBST([cygwinrename])
AC_SUBST([mode])
AC_SUBST([remotehost])
AC_SUBST([index_size])
AC_SUBST([datasize])
AC_SUBST([host])
AC_SUBST([user])
AC_SUBST([passwd])
AC_SUBST([port])
AC_SUBST([socket])
AC_SUBST([log2])
AC_SUBST([terminate_on_error])
AC_SUBST([readonly])
AC_SUBST([intSize])
AC_SUBST([intFmt])
AC_SUBST([intLong])
AC_SUBST([floatSize])
AC_SUBST([inline])
AC_SUBST([inlineDef])
AC_SUBST([profile])
AC_SUBST([version])

AC_CONFIG_FILES([mumps.c])
AC_CONFIG_FILES([rmPipes])
AC_CONFIG_FILES([makePipes])
AC_CONFIG_FILES([server.cpp])
AC_CONFIG_FILES([sys1.c])
AC_CONFIG_FILES([sym.cpp])
AC_CONFIG_FILES([arith.cpp])
AC_CONFIG_FILES([globalb.cpp])
AC_CONFIG_FILES([libmpscpp.cpp])
AC_CONFIG_FILES([sysfunc.cpp])
AC_CONFIG_FILES([Makefile])
AC_CONFIG_FILES([mumpsc])
AC_CONFIG_FILES([mumpslib])
AC_CONFIG_FILES([interp.cpp])
AC_CONFIG_FILES([btree.cpp])
AC_CONFIG_FILES([mdh.bat])
AC_CONFIG_FILES([mumpsc.bat])
AC_CONFIG_FILES([bifs.cpp])
AC_CONFIG_FILES([mumps.cpp])
AC_CONFIG_FILES([include/mumpsc/numSetup.h])
AC_CONFIG_FILES([include/mumpsc/btree.h])
AC_CONFIG_FILES([include/mumpsc/sysparms.h])
AC_CONFIG_FILES([include/mumpsc/strmax.h])
AC_CONFIG_FILES([include/mumpsc/memsize.h])
AC_CONFIG_FILES([include/mumpsc/arith.h])
AC_CONFIG_FILES([include/mumpsc/libmpscpp.h])
AC_CONFIG_FILES([include/mumpsc/stateVector.h])
AC_CONFIG_FILES([include/mumpsc/strmove.h])
AC_CONFIG_FILES([include/mumpsc/globalOrder.h])
AC_CONFIG_FILES([include/mumpsc/keyfix.h])
AC_CONFIG_FILES([include/mumpsc/defines.h])
AC_OUTPUT
chmod u+x *.script
echo "Now run \"make\" followed by \"make install\""

