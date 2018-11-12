#!/bin/sh
# PL-gnu.sh
m=1024

cat current.out | awk '{print $1-29010,$2}' > AP.dat
cat current.out | awk '{print $1-29010,$3}' > ina.dat
cat current.out | awk '{print $1-29010,$4}' > ical.dat
cat current.out | awk '{print $1-29010,$6}' > ikr.dat
cat current.out | awk '{print $1-29010,$7}' > iks.dat
cat current.out | awk '{print $1-29010,$8}' > ik1.dat
cat current.out | awk '{print $1-29010,$5}' > ito.dat

gnuplot << EOM
#set term postscript eps color "Arial" 25
#set term postscript eps enhanced "Times" 25 color
set term png truecolor rounded font "arial,10" enhanced size 1280,768
set output "ap.png"

set key right bottom

set lmargin 10
set bmargin 5
set rmargin 10
set tmargin 5

set style data lines
set style line 1 lt 1 linecolor 7 lw 4
set style line 2 lt 1 linecolor 1 lw 4
set style line 3 lt 1 linecolor 3 lw 4
set style line 4 lt 1 linecolor 5 lw 4
set style line 5 lt 1 linecolor 4 lw 4
set style line 6 lt 2 linecolor 1 lw 4
set style line 7 lt 2 linecolor 3 lw 4
set style line 8 lt 7 lw 3
set style line 9 pt 8 ps 3

set multiplot
set origin 0.2,0

set xrange [0:800]
set yrange [-100:60]
set tics out
set xtics 0,200
set mxtics 2
set ytics -90,30
#set mytics 2

set border 3
set xtics nomirror
set ytics nomirror

set size 0.4,0.45 
#set origin 0.0,0.0

set xlabel "Time (ms)"
set ylabel "V_{m} (mV)"

plot \
	"AP.dat" using 1:2 title "" linestyle 1

set origin 0.2,0.25

set xrange [0:800]
set yrange [-400:20]
set tics out
set format x ""
set ytics -400,100

set border 2
set xtics nomirror
set ytics nomirror
set noxtics 

set size 0.4,0.45 
#set origin 0.0,0.0

set xlabel ""
set ylabel "I_{Na}, I_{to} ({/Symbol m}A/{/Symbol m}F)"

plot \
	"ina.dat" using 1:2 title "I_{Na}" linestyle 1,\
	"ito.dat" using 1:2 title "I_{to}" linestyle 2

set origin 0.2,0.5

set xrange [0:800]
set yrange [-2.6:1.0]
set tics out
set format x ""
set ytics -2.5,0.5

set border 2
set xtics nomirror
set ytics nomirror
set noxtics 

set size 0.4,0.45 
#set origin 0.0,0.0

set xlabel ""
set ylabel "I_{Ca(L), I_{Kr}, I_{Ks}, I_{K1}"

plot \
	"ical.dat" using 1:2 title "I_{Ca(L)}" linestyle 1,\
	"ikr.dat" using 1:2 title "I_{Kr}" linestyle 2,\
	"iks.dat" using 1:2 title "I_{Ks}" linestyle 3,\
	"ik1.dat" using 1:2 title "I_{K1}" linestyle 4

set nomultiplot

quit
EOM
#test -f PL.$$ && rm PL.$$ 
if test "$DISPLAY" != ""
then i=`ps -U $USER | grep gv | egrep -v grep | awk '{print $1}' -`
 if test "$i" != ""
 then kill -1 $i
 else gv -scale=1 ap.eps &
 fi
fi
