#!/bin/sh
# PL-gnu.sh

cat ./0D1-0/data.out | awk '{print ($2-92000)/1000,$7}' > cont.dat
cat ./0D1-1/data.out | awk '{print ($2-92000)/1000,$7}' > cont1.dat
cat ./0D1-2/data.out | awk '{print ($2-92000)/1000,$7}' > cont2.dat

gnuplot << EOM
#set term postscript eps color "Arial" 25
set term postscript eps enhanced "Times" 25 color
set output "nai.eps"

set key right top

set lmargin 10
set bmargin 5
set rmargin 10
set tmargin 5

#set size square

#set title "Ikr"

set style data lines
set style line 1 lt 2 linecolor 7 lw 4
set style line 2 lt 2 linecolor 1 lw 4
set style line 3 lt 2 linecolor 3 lw 4
set style line 4 lt 2 linecolor 5 lw 4
set style line 5 lt 2 linecolor 4 lw 4
set style line 6 lt 2 linecolor 1 lw 4
set style line 7 lt 2 linecolor 3 lw 4
set style line 8 lt 7 lw 3
set style line 9 pt 8 ps 3

set xrange [-0.1:2]
set yrange [5:10]
set tics out scale 2.5
set xtics 0,1
set mxtics 2
set ytics 6,2
set mytics 1

set border 3
set xtics nomirror
set ytics nomirror

set size 1.1,1.0 
set origin 0.0,0.0

set xlabel "Time (s)"
set ylabel "[Na]_{i} (mM)"

plot \
	"cont.dat" using 1:2 title "" linestyle 1,\
	"cont1.dat" using 1:2 title "" linestyle 2,\
	"cont2.dat" using 1:2 title "" linestyle 3

quit
EOM
#test -f PL.$$ && rm PL.$$ 
if test "$DISPLAY" != ""
then i=`ps -U $USER | grep gv | egrep -v grep | awk '{print $1}' -`
 if test "$i" != ""
 then kill -1 $i
 else gv -scale=1 nai.eps &
 fi
fi
