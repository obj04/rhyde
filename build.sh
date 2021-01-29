#!/usr/bin/env bash


function compile {
	cd $1
	for f in $( ls )
	do
		if [ "$( echo $f | grep .cpp )" ]
		then g++ -c $f || return 1
		fi
		if [ -d $f ]
		then compile $f || return 1
		fi
	done
	cd ..
}

compile src
retval=$?
[ $retval -eq 0 ] && g++ -pthread -o rhyde $( find -name *.o )

for f in $( find -name *.o )
do rm $f
done
exit $retval
