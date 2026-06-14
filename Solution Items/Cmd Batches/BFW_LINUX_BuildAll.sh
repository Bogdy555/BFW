#!/bin/bash

if [ -z "$SolutionDir" ]; then
	source "./BFW_LINUX_Path.sh"
fi

pushd "$SolutionDir"

source "./BFW_LINUX/Cmd Batches/BFW_LINUX_DYNAMIC_Build_Debug_x64.sh"
source "./BFW_LINUX/Cmd Batches/BFW_LINUX_DYNAMIC_Build_Debug_x86.sh"
source "./BFW_LINUX/Cmd Batches/BFW_LINUX_DYNAMIC_Build_Release_x64.sh"
source "./BFW_LINUX/Cmd Batches/BFW_LINUX_DYNAMIC_Build_Release_x86.sh"
source "./BFW_LINUX/Cmd Batches/BFW_LINUX_STATIC_Build_Debug_x64.sh"
source "./BFW_LINUX/Cmd Batches/BFW_LINUX_STATIC_Build_Debug_x86.sh"
source "./BFW_LINUX/Cmd Batches/BFW_LINUX_STATIC_Build_Release_x64.sh"
source "./BFW_LINUX/Cmd Batches/BFW_LINUX_STATIC_Build_Release_x86.sh"

popd
