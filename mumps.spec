# Spec file to create RPM Package for Mumpsc Compiler
# Remember you need to be root to install this package

Summary: Mumps Compiler

Name: mumps 

Version: 7.02b 

Release:   1

Group: Development/Languages

Copyright: GPL - GNU General Public License

Packager: Madhur S. Mitra <www.iclassic.cjb.net>

URL:   http://math-cs.cns.uni.edu/~okane/cgi-bin/newpres/m.compiler/compiler/index.cgi

Source: http://www.cs.uni.edu/~okane/source/mumpscompiler-7.02b.src.tar.gz

BuildPreReq: pcre > 2 

Requires: pcre > 2

%description  
Mumps (also referred to as 'M') is a general purpose programming language that supports a native hierarchical data base facility. It is supported by a large user community (mainly biomedical), and a diversified installed application software base. The language originated in the mid-60's at the Massachusetts General Hospital and it became widely used in both clinical and commercial settings. Mumps programs are translated to standard C programs and subsequently compiled to binary executables.

%define __check_files	%{nil}

%prep
%setup -n mumpsc -q

%build
./configure prefix=/usr 
make

%install
make install

%files

/usr/bin/mumps2c
/usr/bin/mumpsc
/usr/bin/mumpslib
/usr/bin/mumpsx
/usr/bin/mpp
/usr/lib/libmumps.a
/usr/lib/libmumpsp.a
/usr/lib/libmpsglobal_bdb.a
/usr/lib/libmpsglobal_native.a
/usr/lib/libmpsglobal_udpclient.a
/usr/lib/libmpsglobal_tcpclient.a
/usr/lib/libmpscpp.a
/usr/lib/libmpsrdbms.a
%dir /usr/include/mumpsc
%doc /usr/share/doc/mumpsc/compiler.html
%doc /usr/share/doc/mumpsc/examples/*.mps
%doc /usr/share/man/man1/*.1

%doc /usr/share/doc/mumpsc/mdh.html
%doc /usr/share/doc/mumpsc/tree.jpg
%doc /usr/share/doc/mumpsc/glade*.jpg

%clean
cd ..
rm -rf mumpsc

%changelog
* Sat Dec 16 2003 Spec File 
- No Changes yet !! Because this is Release 1 !!
