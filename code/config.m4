PHP_ARG_ENABLE(mapnik,
    [Whether to enable the mapnik php extension],
    [    --enable-mapnik    Enable mapnik extension support])

if test $PHP_MAPNIK != "no"; then
    PHP_SUBST(MAPNIK_SHARED_LIBADD)
    PHP_NEW_EXTENSION(mapnik, mapnik.c, $ext_shared)
fi
