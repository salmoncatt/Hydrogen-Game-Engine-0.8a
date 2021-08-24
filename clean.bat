@echo off

if exist bin (
	pushd bin
	del "goober.exe"
	popd
)