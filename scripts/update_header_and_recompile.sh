#!/usr/bin/env bash

changed_file=$1
SCRIPT_DIR=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &>/dev/null && pwd)
"$SCRIPT_DIR"/42header.sh "$changed_file"
make
