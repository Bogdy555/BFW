#!/bin/bash

if [ -z "$SolutionDir" ]; then
	source "../../Solution Items/Cmd Batches/BFW_LINUX_Path.sh"
fi

pushd "$SolutionDir"

Compiler=g++
Linker=ar
Files="BFW_Assets BFW_Cryptography BFW_Debug BFW_GUI BFW_GUID BFW_EntryPoint BFW_FileSystem BFW_Input BFW_Log BFW_Math_Matrix BFW_Math_Quaternion BFW_Math_Vector BFW_Math BFW_MultiProcessing BFW_RunTime BFW_String BFW_Time"
CompileFlags="-Wall -Wno-unused-variable -std=c++20 -static-libstdc++ -static-libgcc -DBFW_LINUX_PLATFORM -DBFW_LITTLE_ENDIAN -DBFW_BUILD_STATIC"

if [ "$Configuration" == "Debug" ]; then
	CompileFlags="$CompileFlags -g -O0 -DBFW_DEBUG"
fi

if [ "$Configuration" == "Release" ]; then
	CompileFlags="$CompileFlags -O2"
fi

if [ "$Platform" == "x64" ]; then
	CompileFlags="$CompileFlags -DBFW_X64"
fi

if [ "$Platform" == "x86" ]; then
	CompileFlags="$CompileFlags -m32 -DBFW_X86"
fi

mkdir -p "./Binaries/BFW_STATIC/Linux/$Configuration/$Platform/"
mkdir -p "./Objects/BFW_STATIC/Linux/$Configuration/$Platform/"

for File in $Files; do
	$Compiler $CompileFlags -c "./BFW/Sources/$File.cpp" -o "./Objects/BFW_STATIC/Linux/$Configuration/$Platform/$File.o" & Jobs+=($!)
done

for Pid in "${Jobs[@]}"; do
	wait "$Pid"
done

for File in $Files; do
	$Linker rcs "./Binaries/BFW_STATIC/Linux/$Configuration/$Platform/libBFW_STATIC.a" "./Objects/BFW_STATIC/Linux/$Configuration/$Platform/$File.o"
done

unset Jobs
unset Compiler
unset Linker
unset Files
unset CompileFlags

popd
