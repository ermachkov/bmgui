#!/bin/sh

if [ $# -ne 2 ]
then
  echo "usage: "$0" <filename> <server_ip>"
  echo ""
  exit 1
else
  if [ -e "$1" ]
  then
    if [ `ping $2 -c 1 -W 1 | grep -c req=1` -eq 0 ]; then
      echo "server is unreacheble"
      exit 1
    else
      if [ $1 = "fware.hex" ]
      then
        cksum fware.hex > fware.crc
        wget $2 --header="666:filename=fware.hex" --post-file=fware.hex > /dev/null 2> /dev/null
        wget $2 --header="666:filename=fware.crc" --post-file=fware.crc > /dev/null 2> /dev/null
        rm fware.crc > /dev/null 2> /dev/null
        rm index*.html* > /dev/null 2> /dev/null
        echo "fware.hex was updated"
        exit 0
      else
        if [ $1 = "firmware.a00" ]
        then
          wget $2 --header="666:filename=firmware.a00" --post-file=firmware.a00  > /dev/null 2> /dev/null
          rm index*.html* > /dev/null 2> /dev/null
          echo "firmware.a00 was updated"
          exit 0
        else
          if [ $1 = "balance.ini" ]
          then
            wget $2 --header="666:filename=balance.ini" --post-file=balance.ini  > /dev/null 2> /dev/null
            rm index*.html* > /dev/null 2> /dev/null
            echo "balance.ini was updated"
            exit 0
          else
            echo "unknown file: \"$1\""
            exit 1
          fi
        fi
      fi
    fi
  else
    echo "file \"$1\" does not exist"
    exit 1
  fi
fi
exit 0

