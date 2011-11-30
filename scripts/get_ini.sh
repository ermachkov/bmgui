#!/bin/sh

if [ $# -ne 1 ]
then
  echo "usage: "$0" <server_ip>"
  echo ""
else
  rm balance.ini > /dev/null 2> /dev/null
  wget http://$1/balance.ini > /dev/null 2> /dev/null
  if [ -e "balance.ini" ]
  then
    crc=`md5sum balance.ini`
    nano balance.ini
    if [ "$crc" != "`md5sum balance.ini`" ]
    then
      wget $1 --header="666:filename=balance.ini" --post-file=balance.ini > /dev/null 2> /dev/null
      rm index*.html* > /dev/null 2> /dev/null
      rm balance.ini > /dev/null 2> /dev/null
      echo "balance.ini was updated"
    else
      echo "balance.ini was saved"
    fi
  else
    echo "connection failed"
  fi
fi
exit 0

