rem Assumes phpDoc is installed in ../PhpDocumentor

rem see http://manual.phpdoc.org/HTMLSmartyConverter/HandS/phpDocumentor/tutorial_phpDocumentor.howto.pkg.html#using.command-line.windows
rem for all options.

pushd ..\PhpDocumentor
call phpdoc.bat                                         ^
        --output HTML:frames:default                    ^
        --directory ..\docs                             ^
        --target mod_mapnik_docs

rmdir /S /Q ..\docs\mod_mapnik_docs
xcopy /E /I mod_mapnik_docs ..\docs\mod_mapnik_docs
popd
