CODE = 10

check:
	echo ${CODE}
	g++ -o ${CODE} ${CODE}.cpp
	python3 check.py ./standard ./${CODE} "python3 makedata.py"
	rm ${CODE}

test:
	g++ -o ${CODE} ${CODE}.cpp
	./${CODE}
	rm ${CODE}
debug:
	g++ -g -o ${CODE} ${CODE}.cpp