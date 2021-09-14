#!/bin/bash

run_test() {
    ofile=$1
    test=`basename $ofile | sed 's/subseq//' | sed 's/.o//'`
    echo "-------------------------------------"
    echo "**Testing $2 implementation ${test}**"
    gcc -o test-subseq -std=gnu99 -Wall -Werror -pedantic test-subseq.c $ofile
    if [ "$?" != "0" ]
    then
	echo "Could not compile test-subseq.c" > /dev/stderr
	exit 1
    fi
    ./test-subseq
    if [ "$?" != 0 ]
    then
	if [ "$test" == "" ]
	then
	    echo "Your test program falsely failed the correct implementation!" > /dev/stderr
	    exit 1
	fi
    else
	if [ "$test" != "" ]
	then
	    echo "Your test program did not identify $ofile as broken!" > /dev/stderr
	    exit 1
	fi
    fi
    rm test-subseq
    echo ""    
}

run_test "/usr/local/ece551/subseq/subseq.o" "correct"

for i in {1..11}
do
    ofile="/usr/local/ece551/subseq/subseq$i.o"
    run_test ${ofile} "broken"
done
