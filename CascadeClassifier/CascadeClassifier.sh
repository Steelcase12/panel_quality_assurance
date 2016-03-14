#!/bin/bash
WIDTH=20
HEIGHT=20
SAMPLES_PER_POSITIVE=55
NUM_IMGS=21

# Creating Samples
# Remove existing sample images
cd samples
rm *.txt
rm *.jpg
# Run opencv_createsamples.exe
for i in `eval echo {0..$NUM_IMGS}` 
do
	opencv_createsamples -img ../positive_images/PositiveCollectionTagger/data/positive-clean/${i}_cropped.jpg -bg ../negative_images/negatives.txt -info ${i}_cropped.txt -num $SAMPLES_PER_POSITIVE -maxxangle 0.5 -maxyangle 0.5 -maxzangle 0.5 -maxidev 1.0 -bgcolor 0 -bgthresh 5 -w $WIDTH -h $HEIGHT
done 
# Combine description files into one
cat *.txt > positives.txt
# Get number of samples for next step
NUM_SAMPLES="$(ls -1 | wc -l)"
echo NUM_SAMPLES=$NUM_SAMPLES
cd ..
# Combining Samples
opencv_createsamples -info samples/positives.txt -bg negative_images/negatives.txt -vec cropped.vec -num $NUM_SAMPLES -w $WIDTH -h $HEIGHT
# Get parameters for next step
let NUMPOS=900 #($NUM_SAMPLES*8)/10
NUMNEG=600
# Training Cascade Classifier
cd classifier
rm *.xml
cd ..
opencv_traincascade -data classifier/ -vec cropped.vec -bg negatives.txt -numPos $NUMPOS -numNeg $NUMNEG -numStages 20 -precalcValBufSize 1024 -precalcIdxBufSize 1024 -featureType HAAR -minHitRate 0.995 -maxFalseAlarmRate 0.5 -w $WIDTH -h $HEIGHT