#!/bin/sh

# Listing
rm -f .listing*
find . > .listing-orig

echo "Regenerating build system"

export WANT_AUTOCONF_2_5="1"
export WANT_AUTOMAKE_1_7="1"

echo "aclocal..."
aclocal

echo "libtoolize..."
libtoolize --automake --force --copy

echo "autoheader..."
autoheader

echo "automake..."
automake -a -c

echo "autoconf..."
autoconf

echo "Done"


# Listing
find . > .listing-after
diff .listing-orig .listing-after | grep -v listing > .listing
rm -f .listing-*

