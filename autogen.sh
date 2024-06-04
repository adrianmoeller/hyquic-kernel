GEN="compile config.guess config.sub depcomp install-sh missing aclocal.m4 \
     configure config.h.in autom4te.cache ltmain.sh ar-lib INSTALL \
     Makefile.in libquic/Makefile.in modules/Makefile.in tests/Makefile.in"

rm -rf $GEN

[ "$1" = "clean" ] && exit 0

libtoolize --force --copy
aclocal
autoheader
automake --add-missing --copy --gnu
autoconf

exit 0
