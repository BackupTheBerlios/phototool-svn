#!/bin/sh

echo "Regenerating build system"

export WANT_AUTOCONF_2_5="1"
export WANT_AUTOMAKE_1_7="1"

echo "aclocal..."
aclocal

echo "libtoolize..."
libtoolize --automake --force --copy

echo "automake..."
automake -a -c

#echo "autoheader..."
#autoheader

echo "autoconf..."
autoconf

echo "Done"

