@echo off

REM Create the bin directory if it doesn't exist
if not exist "..\bin" mkdir "..\bin"

REM Create the output directory if it doesn't exist
if not exist "..\output" mkdir "..\output"

echo Compiling.
g++ -std=c++20 -fmodules-ts -c utils.cpp
g++ -std=c++20 -fmodules-ts -c UJImage.cpp
g++ -std=c++20 -fmodules-ts -c Transformer.cpp
g++ -std=c++20 -fmodules-ts -c VerticalTransformer.cpp
g++ -std=c++20 -fmodules-ts -c HorizontalTransformer.cpp
g++ -std=c++20 -fmodules-ts -c TransformerManager.cpp
g++ -std=c++20 -fmodules-ts -c main.cpp
g++ -std=c++20 -fmodules-ts utils.o UJImage.o Transformer.o VerticalTransformer.o HorizontalTransformer.o TransformerManager.o main.o -o app.exe

echo Cleaning up.
REM The following command deletes the gcm.cache directory and all its contents
REM or subdirectories (/s) quietly (/q)
rmdir /s /q gcm.cache
del *.o
del *.bak

echo Running.
app.exe > UJImage.ppm

echo Opening PPM Image.
UJImage.ppm

pause