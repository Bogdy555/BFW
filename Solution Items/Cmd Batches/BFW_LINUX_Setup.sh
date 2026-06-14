#!/bin/bash

if [ -z "$SolutionDir" ]; then
	source "./BFW_LINUX_Path.sh"
fi

pushd "$SolutionDir"

source "./Solution Items/Cmd Batches/BFW_LINUX_CreateFolders.sh"

popd
