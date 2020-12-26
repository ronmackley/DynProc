#!/bin/bash

if [ "$1" == "clean" ]
then
	rm -fv ExternalFunction mf.so *~
	exit
fi


g++ -v -o ExternalFunction ExternalFunction.cpp -ldl
g++ -v -fPIC -shared -o mf.so mf.cpp

