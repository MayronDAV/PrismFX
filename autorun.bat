@echo off

call scripts\setup.bat

cmake --build build --target clean

cmake -S . -B build

cmake --build ./build --config Debug

PAUSE

.\sandbox\Bin\Debug\Sandbox.exe

