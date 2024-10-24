@echo off

if not exist .\bin mkdir .\bin

cl.exe monoff.cpp /nologo /EHsc /Fe:bin\monoff.exe /link shell32.lib user32.lib ole32.lib oleaut32.lib
del monoff.obj

cl.exe touch.cpp /nologo /EHsc /Fe:bin\touch.exe /link shell32.lib user32.lib ole32.lib oleaut32.lib
del touch.obj
