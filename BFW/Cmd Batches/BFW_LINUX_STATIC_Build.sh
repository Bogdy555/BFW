#!/bin/bash

if [ -z "$SolutionDir" ]; then
	source "../../Solution Items/Cmd Batches/BFW_LINUX_Path.sh"
fi

pushd "$SolutionDir"

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

mkdir -p "./Binaries/"
mkdir -p "./Binaries/BFW_STATIC/"
mkdir -p "./Binaries/BFW_STATIC/Linux/"
mkdir -p "./Binaries/BFW_STATIC/Linux/$Configuration/"
mkdir -p "./Binaries/BFW_STATIC/Linux/$Configuration/$Platform/"
mkdir -p "./Objects/"
mkdir -p "./Objects/BFW_STATIC/"
mkdir -p "./Objects/BFW_STATIC/Linux/"
mkdir -p "./Objects/BFW_STATIC/Linux/$Configuration/"
mkdir -p "./Objects/BFW_STATIC/Linux/$Configuration/$Platform/"

g++ $CompileFlags -c "./BFW/Sources/BFW_Assets.cpp" -o "./Objects/BFW_STATIC/Linux/$Configuration/$Platform/BFW_Assets.o"
g++ $CompileFlags -c "./BFW/Sources/BFW_Cryptography.cpp" -o "./Objects/BFW_STATIC/Linux/$Configuration/$Platform/BFW_Cryptography.o"
g++ $CompileFlags -c "./BFW/Sources/BFW_Debug.cpp" -o "./Objects/BFW_STATIC/Linux/$Configuration/$Platform/BFW_Debug.o"
g++ $CompileFlags -c "./BFW/Sources/BFW_GUI.cpp" -o "./Objects/BFW_STATIC/Linux/$Configuration/$Platform/BFW_GUI.o"
g++ $CompileFlags -c "./BFW/Sources/BFW_GUID.cpp" -o "./Objects/BFW_STATIC/Linux/$Configuration/$Platform/BFW_GUID.o"
g++ $CompileFlags -c "./BFW/Sources/BFW_EntryPoint.cpp" -o "./Objects/BFW_STATIC/Linux/$Configuration/$Platform/BFW_EntryPoint.o"
g++ $CompileFlags -c "./BFW/Sources/BFW_FileSystem.cpp" -o "./Objects/BFW_STATIC/Linux/$Configuration/$Platform/BFW_FileSystem.o"
g++ $CompileFlags -c "./BFW/Sources/BFW_Input.cpp" -o "./Objects/BFW_STATIC/Linux/$Configuration/$Platform/BFW_Input.o"
g++ $CompileFlags -c "./BFW/Sources/BFW_Log.cpp" -o "./Objects/BFW_STATIC/Linux/$Configuration/$Platform/BFW_Log.o"
g++ $CompileFlags -c "./BFW/Sources/BFW_Math_Matrix.cpp" -o "./Objects/BFW_STATIC/Linux/$Configuration/$Platform/BFW_Math_Matrix.o"
g++ $CompileFlags -c "./BFW/Sources/BFW_Math_Quaternion.cpp" -o "./Objects/BFW_STATIC/Linux/$Configuration/$Platform/BFW_Math_Quaternion.o"
g++ $CompileFlags -c "./BFW/Sources/BFW_Math_Vector.cpp" -o "./Objects/BFW_STATIC/Linux/$Configuration/$Platform/BFW_Math_Vector.o"
g++ $CompileFlags -c "./BFW/Sources/BFW_Math.cpp" -o "./Objects/BFW_STATIC/Linux/$Configuration/$Platform/BFW_Math.o"
g++ $CompileFlags -c "./BFW/Sources/BFW_MultiProcessing.cpp" -o "./Objects/BFW_STATIC/Linux/$Configuration/$Platform/BFW_MultiProcessing.o"
g++ $CompileFlags -c "./BFW/Sources/BFW_RunTime.cpp" -o "./Objects/BFW_STATIC/Linux/$Configuration/$Platform/BFW_RunTime.o"
g++ $CompileFlags -c "./BFW/Sources/BFW_String.cpp" -o "./Objects/BFW_STATIC/Linux/$Configuration/$Platform/BFW_String.o"
g++ $CompileFlags -c "./BFW/Sources/BFW_Time.cpp" -o "./Objects/BFW_STATIC/Linux/$Configuration/$Platform/BFW_Time.o"

ar rcs "./Binaries/BFW_STATIC/Linux/$Configuration/$Platform/libBFW_STATIC.a" "./Objects/BFW_STATIC/Linux/$Configuration/$Platform/BFW_Assets.o"
ar rcs "./Binaries/BFW_STATIC/Linux/$Configuration/$Platform/libBFW_STATIC.a" "./Objects/BFW_STATIC/Linux/$Configuration/$Platform/BFW_Cryptography.o"
ar rcs "./Binaries/BFW_STATIC/Linux/$Configuration/$Platform/libBFW_STATIC.a" "./Objects/BFW_STATIC/Linux/$Configuration/$Platform/BFW_Debug.o"
ar rcs "./Binaries/BFW_STATIC/Linux/$Configuration/$Platform/libBFW_STATIC.a" "./Objects/BFW_STATIC/Linux/$Configuration/$Platform/BFW_GUI.o"
ar rcs "./Binaries/BFW_STATIC/Linux/$Configuration/$Platform/libBFW_STATIC.a" "./Objects/BFW_STATIC/Linux/$Configuration/$Platform/BFW_GUID.o"
ar rcs "./Binaries/BFW_STATIC/Linux/$Configuration/$Platform/libBFW_STATIC.a" "./Objects/BFW_STATIC/Linux/$Configuration/$Platform/BFW_EntryPoint.o"
ar rcs "./Binaries/BFW_STATIC/Linux/$Configuration/$Platform/libBFW_STATIC.a" "./Objects/BFW_STATIC/Linux/$Configuration/$Platform/BFW_FileSystem.o"
ar rcs "./Binaries/BFW_STATIC/Linux/$Configuration/$Platform/libBFW_STATIC.a" "./Objects/BFW_STATIC/Linux/$Configuration/$Platform/BFW_Input.o"
ar rcs "./Binaries/BFW_STATIC/Linux/$Configuration/$Platform/libBFW_STATIC.a" "./Objects/BFW_STATIC/Linux/$Configuration/$Platform/BFW_Log.o"
ar rcs "./Binaries/BFW_STATIC/Linux/$Configuration/$Platform/libBFW_STATIC.a" "./Objects/BFW_STATIC/Linux/$Configuration/$Platform/BFW_Math_Matrix.o"
ar rcs "./Binaries/BFW_STATIC/Linux/$Configuration/$Platform/libBFW_STATIC.a" "./Objects/BFW_STATIC/Linux/$Configuration/$Platform/BFW_Math_Quaternion.o"
ar rcs "./Binaries/BFW_STATIC/Linux/$Configuration/$Platform/libBFW_STATIC.a" "./Objects/BFW_STATIC/Linux/$Configuration/$Platform/BFW_Math_Vector.o"
ar rcs "./Binaries/BFW_STATIC/Linux/$Configuration/$Platform/libBFW_STATIC.a" "./Objects/BFW_STATIC/Linux/$Configuration/$Platform/BFW_Math.o"
ar rcs "./Binaries/BFW_STATIC/Linux/$Configuration/$Platform/libBFW_STATIC.a" "./Objects/BFW_STATIC/Linux/$Configuration/$Platform/BFW_MultiProcessing.o"
ar rcs "./Binaries/BFW_STATIC/Linux/$Configuration/$Platform/libBFW_STATIC.a" "./Objects/BFW_STATIC/Linux/$Configuration/$Platform/BFW_RunTime.o"
ar rcs "./Binaries/BFW_STATIC/Linux/$Configuration/$Platform/libBFW_STATIC.a" "./Objects/BFW_STATIC/Linux/$Configuration/$Platform/BFW_String.o"
ar rcs "./Binaries/BFW_STATIC/Linux/$Configuration/$Platform/libBFW_STATIC.a" "./Objects/BFW_STATIC/Linux/$Configuration/$Platform/BFW_Time.o"

CompileFlags=

popd
