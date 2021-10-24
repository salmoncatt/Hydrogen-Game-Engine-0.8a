@echo off

if exist bin (
	pushd bin
	del "goober.exe"
	del "goober_debug.exe"

	if exist hfpch (
		pushd hfpch
		del "hfpch.h.gch"
	)

	popd
)