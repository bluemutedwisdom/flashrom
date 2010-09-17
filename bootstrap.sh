#!/bin/sh
aclocal --force
/usr/bin/autoconf --force
/usr/bin/autoheader --force
automake --add-missing --copy --force-missing
