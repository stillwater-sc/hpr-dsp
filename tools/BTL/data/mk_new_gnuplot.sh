#! /bin/bash
WHAT=$1
DIR=$2
cat ../${WHAT}.hh > ${WHAT}.gnuplot

DATA_FILE=`cat ../order_lib`

echo plot \\ >> $WHAT.gnuplot

for FILE in $DATA_FILE
do
    LAST=$FILE
done


for FILE in $DATA_FILE
do
     if [ $FILE != $LAST ]
     then
	echo "'"$FILE"'" ",\\" >>  $WHAT.gnuplot
     fi
done
echo "'"$LAST"'" >>  $WHAT.gnuplot

echo set term postscript color >> $WHAT.gnuplot
echo set output "'"../${DIR}/$WHAT.ps"'" >> $WHAT.gnuplot
#echo set term pbm color >> $WHAT.gnuplot
#echo set output "'"../${DIR}/$WHAT.ppm"'" >> $WHAT.gnuplot
echo plot \\ >> $WHAT.gnuplot
for FILE in $DATA_FILE
do
     if [ $FILE != $LAST ]
     then
	echo "'"$FILE"'" ",\\" >>  $WHAT.gnuplot
     fi
done
echo "'"$LAST"'" >>  $WHAT.gnuplot

gnuplot -persist < $WHAT.gnuplot

rm $WHAT.gnuplot




