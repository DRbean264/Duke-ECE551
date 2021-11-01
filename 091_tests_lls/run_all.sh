#!/bin/bash

vg="valgrind --leak-check=full --log-file=vg.log --error-exitcode=33"
testdir=/usr/local/ece551/lls
nbroken=26

echo "**Testing correct implementation**"
echo "-----------------------------------"
g++ -o test-lls test-lls.cpp ${testdir}/il.o
if [ "$?" != "0" ]
then
    echo "Could not compile test-lls.cpp with il.o" 1>&2
    exit 1
fi
timeout -s 9 10 $vg ./test-lls
if [ "$?" != "0" ]
then
    echo "Your test program falsely failed the correct implementation!" 1>&2
    exit 1
fi
echo ""

for i in {1..26}
do
    echo "**Testing broken implementation ${i}**"
    echo "-----------------------------------"
    g++ -o test-lls test-lls.cpp ${testdir}/il${i}.o
    if [ "$?" != "0" ]
    then
	echo "Could not compile test-lls.cpp with ${i}" 1>&2
	exit 1
    fi
    timeout -s 9 10 $vg ./test-lls
    if [ "$?" == "0" ]
    then
	echo "Your test program did not identify ${i} as broken!" 1>&2
	exit 1
    fi
    echo ""
done

echo "You have successfully identified all broken implementations"
