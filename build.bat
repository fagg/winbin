@echo off

if not exist .\bin mkdir .\bin

cl.exe monoff.cpp /nologo /EHsc /Os /MD /DNDEBUG /Fe:bin\monoff.exe /link /OPT:REF /OPT:ICF shell32.lib user32.lib ole32.lib oleaut32.lib
del monoff.obj

cl.exe touch.cpp /nologo /EHsc /Os /MD /DNDEBUG /Fe:bin\touch.exe /link /OPT:REF /OPT:ICF shell32.lib user32.lib ole32.lib oleaut32.lib
del touch.obj

cl.exe pwd.cpp /nologo /EHsc /Fe:bin\pwd.exe /MD /DNDEBUG /link /OPT:REF /OPT:ICF shell32.lib user32.lib ole32.lib oleaut32.lib
del pwd.obj
