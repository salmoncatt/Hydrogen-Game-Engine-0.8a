@echo off

if not exist bin mkdir bin
if not exist bin\hfpch mkdir bin\hfpch

echo [HGE] (DEBUG) compiling

echo[

echo [HGE] (DEBUG) compiling hfpch.h

make hfpch_debug

echo[

echo [HGE] (DEBUG) compiling HF
make main



echo[
echo [HGE] (DEBUG) done compiling


pause