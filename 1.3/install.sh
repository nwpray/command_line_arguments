#!/bin/bash

if [ -a setport ]
    then rm setport
fi

if [ -a tests ]
    then rm tests
fi

sed -i '/alias setport=/d' ~/.bash_aliases 
sed -i '/alias setporttest=/d' ~/.bash_aliases

make setport
make tests

echo "alias setport=\"$PWD/setport\"" >> ~/.bash_aliases
echo "alias setporttest=\"$PWD/tests\"" >> ~/.bash_aliases

exec bash