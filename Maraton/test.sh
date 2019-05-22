#!/bin/bash

for f in $2/*.in
    do
        ./$1 <$f >${f%.in}.T_out 2>${f%.in}.T_err

	if diff ${f%.in}.out ${f%.in}.T_out
        then
            echo "${f%.in} out passed"
        else
            echo "${f%.in} out failed"
        fi
        
        if diff ${f%.in}.err ${f%.in}.T_err
            then
                echo "${f%.in} err passed"
            else
                echo "${f%.in} err failed"
	fi
    done;

if test $# = 3
then
for f in $2/*.T_out
	do	rm $f
		rm ${f%.T_out}.T_err
	done;
fi
