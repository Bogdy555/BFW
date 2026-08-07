#!/bin/bash

if [ -z "$SolutionDir" ]; then
	source "../../Solution Items/Cmd Batches/BFW_LINUX_Path.sh"
fi

pushd "$SolutionDir"

source "./BFW/Cmd Batches/BFW_LINUX_STATIC_Build.sh"

Compiler=g++
Linker=g++
Files="BFW_LINUX_EntryPoint BFW_LINUX_RunTime_Application BFW_LINUX_RunTime_MainMenu"
CompileFlags="-Wall -Wno-unused-variable -std=c++20 -static-libstdc++ -static-libgcc -I./BFW/Headers/ -DBFW_LINUX_PLATFORM -DBFW_LITTLE_ENDIAN -DBFW_LINK_STATIC"
LinkFlags="-static-libstdc++ -static-libgcc -L./Binaries/BFW_STATIC/Linux/$Configuration/$Platform/ -lBFW_STATIC"

if [ "$Configuration" == "Debug" ]; then
	CompileFlags="$CompileFlags -g -O0 -DBFW_DEBUG"
	LinkFlags="$LinkFlags -g"
fi

if [ "$Configuration" == "Release" ]; then
	CompileFlags="$CompileFlags -O2"
	LinkFlags="$LinkFlags"
fi

if [ "$Platform" == "x64" ]; then
	CompileFlags="$CompileFlags -DBFW_X64"
	LinkFlags="$LinkFlags"
fi

if [ "$Platform" == "x86" ]; then
	CompileFlags="$CompileFlags -m32 -DBFW_X86"
	LinkFlags="$LinkFlags -m32"
fi

mkdir -p "./Binaries/BFW_LINUX_STATIC/$Configuration/$Platform/"
mkdir -p "./Objects/BFW_LINUX_STATIC/$Configuration/$Platform/"

for File in $Files; do
	$Compiler $CompileFlags -c "./BFW_LINUX/Sources/$File.cpp" -o "./Objects/BFW_LINUX_STATIC/$Configuration/$Platform/$File.o" & Jobs+=($!)
done

for Pid in "${Jobs[@]}"; do
	wait "$Pid"
done

for File in $Files; do
	AllObj+=" ./Objects/BFW_LINUX_STATIC/$Configuration/$Platform/$File.o"
done

$Linker $AllObj $LinkFlags -o "./Binaries/BFW_LINUX_STATIC/$Configuration/$Platform/BFW_LINUX_STATIC"

if [ -d "./BFW_LINUX/Files" ]; then
	cp -r "./BFW_LINUX/Files/." "./Binaries/BFW_LINUX_STATIC/$Configuration/$Platform/"
fi

Jobs=
AllObj=
Compiler=
Linker=
Files=
CompileFlags=
LinkFlags=

popd
