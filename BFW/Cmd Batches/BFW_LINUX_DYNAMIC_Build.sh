#!/bin/bash

if [ -z "$SolutionDir" ]; then
	source "../../Solution Items/Cmd Batches/BFW_LINUX_Path.sh"
fi

pushd "$SolutionDir"

Compiler=g++
Linker=g++
Files="BFW_Assets BFW_Cryptography BFW_Debug BFW_GUI BFW_GUID BFW_EntryPoint BFW_FileSystem BFW_Input BFW_Log BFW_Math BFW_Math_Matrix BFW_Math_Quaternion BFW_Math_Random BFW_Math_Vector BFW_Math BFW_MultiProcessing BFW_RunTime BFW_String BFW_Time"
CompileFlags="-Wall -Wno-unused-variable -std=c++20 -fPIC -DBFW_LINUX_PLATFORM -DBFW_LITTLE_ENDIAN -DBFW_BUILD_DYNAMIC"
LinkFlags="-shared"

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

mkdir -p "./Binaries/BFW_DYNAMIC/Linux/$Configuration/$Platform/"
mkdir -p "./Objects/BFW_DYNAMIC/Linux/$Configuration/$Platform/"

for File in $Files; do
	$Compiler $CompileFlags -c "./BFW/Sources/$File.cpp" -o "./Objects/BFW_DYNAMIC/Linux/$Configuration/$Platform/$File.o" & Jobs+=($!)
done

for Pid in "${Jobs[@]}"; do
	wait "$Pid"
done

for File in $Files; do
	AllObj+=" ./Objects/BFW_DYNAMIC/Linux/$Configuration/$Platform/$File.o"
done

$Linker $AllObj $LinkFlags -o "./Binaries/BFW_DYNAMIC/Linux/$Configuration/$Platform/libBFW_DYNAMIC.so"

if [ -f "./Binaries/BFW_LINUX_DYNAMIC/$Configuration/$Platform/libBFW_DYNAMIC.so" ]; then
	cp "./Binaries/BFW_DYNAMIC/Linux/$Configuration/$Platform/libBFW_DYNAMIC.so" "./Binaries/BFW_LINUX_DYNAMIC/$Configuration/$Platform/"
fi

unset Jobs
unset AllObj
unset Compiler
unset Linker
unset Files
unset CompileFlags
unset LinkFlags

popd
