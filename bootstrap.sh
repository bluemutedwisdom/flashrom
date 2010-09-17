#!/bin/sh
aclocal --force
/usr/bin/autoconf --force
automake --add-missing --copy --force-missing
