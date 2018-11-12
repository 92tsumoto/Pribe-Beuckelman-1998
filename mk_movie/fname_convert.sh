#!/bin/sh

seed=0

while [ $seed -le 9 ]
do
	mv $seed.png 000$seed.png
	seed=`expr $seed + 1`
done

while [ $seed -le 99 ]
do
	mv $seed.png 00$seed.png
	seed=`expr $seed + 1`
done

while [ $seed -le 999 ]
do

mv $seed.png 0$seed.png
seed=`expr $seed + 1`

done

