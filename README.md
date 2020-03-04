# Open MUMPS Interpreter

This repository improves on the MUMPS interpreter by Professor Kevin C. O'Kane
at the University of Northern Iowa. It can use a native B-tree implementation
for the storage, or it can use a MySQL or PostgreSQL database. Visit [Professor
O'Kane's staff website](https://www.cs.uni.edu/~okane/) for more information.

As a student at New York University, I made some improvements to the codebase
for CS-GY 6513 Big Data, taught by Professor Raman Kannan. I tested building on
an AMD64 platform and in an IBM Cloud environment, which uses PowerPC. For this
class, I used MySQL as the underlying storage engine.

I fixed a few minor bugs, but the main addition that I made was the ability to
prompt the user for the database username and password when using a SQL DB as
the underlying storage engine instead of the native B-tree implementation. You
can see this code in [dbcreds.cpp](dbcreds.cpp). To facilitate bounds checking,
I added two variables:

- `$zsqldatasize` is the maximum length of a string that can be stored as a
  value in a MUMPS global.
- `$zsqlindexsize` is the maximum length of a string that can be used as a
  subscript with a MUMPS global.

## Installation

Please see [the original manual](doc/ReadMe.pdf) for full instructions. The
following instructions are for building Open MUMPS with database credential
prompts, with MySQL as the underlying storage engine, and without GNU
Multiple Precision.

First, install required packages:

    sudo apt install libmysqlclient-dev

If you are using a different package manager, substitute its command in the
place of the one with `apt`.

There are various `*.script` files that help install the interpreter, but I did
not use them. To install for your user only:

    ./configure --with-hardware-math --with-mysqldb --with-mysql-host=127.0.0.1 --with-db-cred-prompt
    make && make install

This will install MUMPS to `~/mumps_compiler/bin/`. You may want to edit
`~/.profile` to include this in your path environment variable.

To install for all users:

    ./configure prefix=/usr --with-hardware-math --with-mysqldb --with-mysql-host=127.0.0.1 --with-db-cred-prompt
    make && sudo make install

If your MySQL server is not at `127.0.0.1`, substitute its IP address in your
command. You can also change the port number with `--with-mysql-port=[number]`.
