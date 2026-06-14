#!/bin/bash

if [ -z "$SolutionDir" ]; then
	source "../../Solution Items/Cmd Batches/BFW_LINUX_Path.sh"
fi

pushd "$SolutionDir"

Configuration=Debug
Platform=x86

source "./BFW_LINUX/Cmd Batches/BFW_LINUX_DYNAMIC_Build.sh"

Configuration=
Platform=

popd
