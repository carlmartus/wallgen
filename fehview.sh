#!/bin/sh
CMD=$1
OUT=/tmp/fehview.ppm
RES_W=640
RES_H=480

echo "Run $1"

if [ -n "$CMD" ]; then
	./$CMD $RES_W $RES_H $2 $3 $4 $5 $6 > $OUT && feh $OUT
else
	echo "Specify which program to view"
	echo "You must have the program 'feh' installed to view the images"
fi

