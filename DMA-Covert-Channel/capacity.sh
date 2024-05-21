#!/bin/bash

if [[ $# -lt 1  ]]; 
	then
		echo -e "Missing board name, introduce one:"
		read BOARD
	else
	BOARD=$1
fi

ROOT_DIR=.
TEST_DIR=$ROOT_DIR/${BOARD}

# -cp ->  measure channel capacity
# -di -> samples are discrete
# -v 0 -> verbosity (0 to 5)

CONTENTION="Contention"
NO_CONTENTION="No_Contention"

cp ${TEST_DIR}/samples_cont.txt \
	${TEST_DIR}/Results/"$BOARD"_"$CONTENTION"_samples.txt

cp ${TEST_DIR}/samples_no_cont.txt \
	${TEST_DIR}/Results/"$BOARD"_"$NO_CONTENTION"_samples.txt

echo "Measuring channel with contention"

java -jar ./leakiest-1.4.9.jar -di -cp -v 0 \
	${TEST_DIR}/Results/"$BOARD"_"$CONTENTION"_samples.txt \
	> ${TEST_DIR}/Results/"$BOARD"_"$CONTENTION"_capacity.txt

cat ${TEST_DIR}/Results/"$BOARD"_"$CONTENTION"_capacity.txt

echo " "
echo "Measuring channel without contention"

java -jar ./leakiest-1.4.9.jar -di -cp -v 0 \
	 ${TEST_DIR}/Results/"$BOARD"_"$NO_CONTENTION"_samples.txt \
	 > ${TEST_DIR}/Results/"$BOARD"_"$NO_CONTENTION"_capacity.txt

cat ${TEST_DIR}/Results/"$BOARD"_"$NO_CONTENTION"_capacity.txt

echo " "
echo "Print Matrix"

java -jar ./leakiest-1.4.9.jar -di -cp -v 0 -p \
	 ${TEST_DIR}/Results/"$BOARD"_"$CONTENTION"_samples.txt \
	 > ${TEST_DIR}/Results/"$BOARD"_"$CONTENTION"_ch_matrix.txt
