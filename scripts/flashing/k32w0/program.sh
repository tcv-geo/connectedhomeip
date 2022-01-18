#! /bin/bash

set -eu

mydir="$(dirname "$0")"

found=false

IFS=$'\n'

for tool in $(find /usr/local/mcuxpressoide* -name crt_emu_cm_redlink)
do
  flashdir="$(dirname "$tool")"/Flash

  if [ -x "$tool" ] && [ -d "$flashdir" ]
  then
    found=true
    break
  fi
done

if ! $found
then
  echo MCUXpresso not found >&2
  exit 1
fi

if [ $# -ne 1 ]
then
  echo specify file to download as argument >&2
  exit 1
fi

# copy input to temporary file because it must have correct extension

axf="$(mktemp --suffix=.axf)"

trap "rm -f \"$axf\"" EXIT

cat "$1" >"$axf"

"$tool" -x "$mydir" -p K32W061 --flash-dir "$flashdir" --ConnectScript QN9090Connect.scp --flash-load-exec "$axf" --flash-hashing
