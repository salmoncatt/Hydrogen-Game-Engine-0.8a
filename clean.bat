@echo off

if exist bin (
	pushd bin
	del "goober.exe"

	if exist hfpch (
		pushd hfpch
		del "hfpch.h.gch"
	)

	popd
)