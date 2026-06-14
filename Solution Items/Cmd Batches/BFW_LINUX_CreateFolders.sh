#!/bin/bash

if [ -z "$SolutionDir" ]; then
	source "./BFW_LINUX_Path.sh"
fi

pushd "$SolutionDir"

mkdir -p "./BFW/Resources/Icons/"
mkdir -p "./BFW_ESP32/Files/"
mkdir -p "./BFW_LINUX/Files/"
mkdir -p "./BFW_WINDOWS/Files/"
mkdir -p "./BFW_WINDOWS/Resources/Icons/"
mkdir -p "./Solution Items/Dependencies/ArduinoCore/Lib/"
mkdir -p "./Solution Items/Digital Certificates/BSW/"
mkdir -p "./Solution Items/Docs/"
mkdir -p "./Solution Items/Examples/"
mkdir -p "./Solution Items/ReadMe Resources/"

popd
