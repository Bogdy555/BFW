#!/bin/bash

if [ -z "$SolutionDir" ]; then
	source "../../Solution Items/Cmd Batches/BFW_LINUX_Path.sh"
fi

pushd "$SolutionDir"

CompileFlags="-Wall -Wno-unused-variable -std=c++20 -static-libstdc++ -static-libgcc -fPIC -DBFW_LINUX_PLATFORM -DBFW_LITTLE_ENDIAN -DBFW_BUILD_DYNAMIC"
LinkFlags="-shared -static-libstdc++ -static-libgcc"

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

mkdir -p "./Binaries/"
mkdir -p "./Binaries/BFW_DYNAMIC/"
mkdir -p "./Binaries/BFW_DYNAMIC/Linux/"
mkdir -p "./Binaries/BFW_DYNAMIC/Linux/$Configuration/"
mkdir -p "./Binaries/BFW_DYNAMIC/Linux/$Configuration/$Platform/"
mkdir -p "./Objects/"
mkdir -p "./Objects/BFW_DYNAMIC/"
mkdir -p "./Objects/BFW_DYNAMIC/Linux/"
mkdir -p "./Objects/BFW_DYNAMIC/Linux/$Configuration/"
mkdir -p "./Objects/BFW_DYNAMIC/Linux/$Configuration/$Platform/"

g++ $CompileFlags -c "./BFW/Sources/BFW_Assets.cpp" -o "./Objects/BFW_DYNAMIC/Linux/$Configuration/$Platform/BFW_Assets.o"
g++ $CompileFlags -c "./BFW/Sources/BFW_Cryptography.cpp" -o "./Objects/BFW_DYNAMIC/Linux/$Configuration/$Platform/BFW_Cryptography.o"
g++ $CompileFlags -c "./BFW/Sources/BFW_Debug.cpp" -o "./Objects/BFW_DYNAMIC/Linux/$Configuration/$Platform/BFW_Debug.o"
g++ $CompileFlags -c "./BFW/Sources/BFW_GUI.cpp" -o "./Objects/BFW_DYNAMIC/Linux/$Configuration/$Platform/BFW_GUI.o"
g++ $CompileFlags -c "./BFW/Sources/BFW_GUID.cpp" -o "./Objects/BFW_DYNAMIC/Linux/$Configuration/$Platform/BFW_GUID.o"
g++ $CompileFlags -c "./BFW/Sources/BFW_EntryPoint.cpp" -o "./Objects/BFW_DYNAMIC/Linux/$Configuration/$Platform/BFW_EntryPoint.o"
g++ $CompileFlags -c "./BFW/Sources/BFW_Input.cpp" -o "./Objects/BFW_DYNAMIC/Linux/$Configuration/$Platform/BFW_Input.o"
g++ $CompileFlags -c "./BFW/Sources/BFW_Log.cpp" -o "./Objects/BFW_DYNAMIC/Linux/$Configuration/$Platform/BFW_Log.o"
g++ $CompileFlags -c "./BFW/Sources/BFW_Math_Matrix.cpp" -o "./Objects/BFW_DYNAMIC/Linux/$Configuration/$Platform/BFW_Math_Matrix.o"
g++ $CompileFlags -c "./BFW/Sources/BFW_Math_Quaternion.cpp" -o "./Objects/BFW_DYNAMIC/Linux/$Configuration/$Platform/BFW_Math_Quaternion.o"
g++ $CompileFlags -c "./BFW/Sources/BFW_Math_Vector.cpp" -o "./Objects/BFW_DYNAMIC/Linux/$Configuration/$Platform/BFW_Math_Vector.o"
g++ $CompileFlags -c "./BFW/Sources/BFW_Math.cpp" -o "./Objects/BFW_DYNAMIC/Linux/$Configuration/$Platform/BFW_Math.o"
g++ $CompileFlags -c "./BFW/Sources/BFW_MultiProcessing.cpp" -o "./Objects/BFW_DYNAMIC/Linux/$Configuration/$Platform/BFW_MultiProcessing.o"
g++ $CompileFlags -c "./BFW/Sources/BFW_RunTime.cpp" -o "./Objects/BFW_DYNAMIC/Linux/$Configuration/$Platform/BFW_RunTime.o"
g++ $CompileFlags -c "./BFW/Sources/BFW_String.cpp" -o "./Objects/BFW_DYNAMIC/Linux/$Configuration/$Platform/BFW_String.o"
g++ $CompileFlags -c "./BFW/Sources/BFW_Time.cpp" -o "./Objects/BFW_DYNAMIC/Linux/$Configuration/$Platform/BFW_Time.o"

g++ "./Objects/BFW_DYNAMIC/Linux/$Configuration/$Platform/BFW_Assets.o" "./Objects/BFW_DYNAMIC/Linux/$Configuration/$Platform/BFW_Cryptography.o" "./Objects/BFW_DYNAMIC/Linux/$Configuration/$Platform/BFW_Debug.o" "./Objects/BFW_DYNAMIC/Linux/$Configuration/$Platform/BFW_GUI.o" "./Objects/BFW_DYNAMIC/Linux/$Configuration/$Platform/BFW_GUID.o" "./Objects/BFW_DYNAMIC/Linux/$Configuration/$Platform/BFW_EntryPoint.o" "./Objects/BFW_DYNAMIC/Linux/$Configuration/$Platform/BFW_Input.o" "./Objects/BFW_DYNAMIC/Linux/$Configuration/$Platform/BFW_Log.o" "./Objects/BFW_DYNAMIC/Linux/$Configuration/$Platform/BFW_Math_Matrix.o" "./Objects/BFW_DYNAMIC/Linux/$Configuration/$Platform/BFW_Math_Quaternion.o" "./Objects/BFW_DYNAMIC/Linux/$Configuration/$Platform/BFW_Math_Vector.o" "./Objects/BFW_DYNAMIC/Linux/$Configuration/$Platform/BFW_Math.o" "./Objects/BFW_DYNAMIC/Linux/$Configuration/$Platform/BFW_MultiProcessing.o" "./Objects/BFW_DYNAMIC/Linux/$Configuration/$Platform/BFW_RunTime.o" "./Objects/BFW_DYNAMIC/Linux/$Configuration/$Platform/BFW_String.o" "./Objects/BFW_DYNAMIC/Linux/$Configuration/$Platform/BFW_Time.o" $LinkFlags -o "./Binaries/BFW_DYNAMIC/Linux/$Configuration/$Platform/libBFW_DYNAMIC.so"

if [ -f "./Binaries/BFW_LINUX_DYNAMIC/$Configuration/$Platform/libBFW_DYNAMIC.so" ]; then
	cp "./Binaries/BFW_DYNAMIC/Linux/$Configuration/$Platform/libBFW_DYNAMIC.so" "./Binaries/BFW_LINUX_DYNAMIC/$Configuration/$Platform/"
fi

CompileFlags=
LinkFlags=

popd
