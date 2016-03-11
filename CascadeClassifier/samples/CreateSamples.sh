#!/bin/bash
for i in {1..21} 
do
opencv_createsamples -img ../positive_images/PositiveCollectionTagger/data/positive-clean/${i}_cropped.jpg -bg ../negative_images/negatives.txt -info ${i}_cropped.txt -num 64 -maxxangle 0.2 -maxyangle 0.2 -maxzangle 0.2 -maxidev 0.5 -bgcolor 0 -bgthresh 5 -w 20 -h 20
done 