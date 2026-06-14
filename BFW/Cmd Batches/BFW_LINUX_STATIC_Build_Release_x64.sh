#!/bin/bash

if [ -z "$SolutionDir" ]; then
	source "../../Solution Items/Cmd Batches/BFW_LINUX_Path.sh"
fi

pushd "$SolutionDir"

Configuration=Release
Platform=x64

source "./BFW/Cmd Batches/BFW_LINUX_STATIC_Build.sh"

Configuration=
Platform=

popd
