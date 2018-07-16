#!/bin/sh
FILES=`ls w*_*`
SAMPLE_DIR=samples

mkdir -p $SAMPLE_DIR
for F in $FILES; do
	./$F 300 300 > $F.ppm
	convert $F.ppm -resize 100x100 $SAMPLE_DIR/$F.jpg
	rm $F.ppm
done
