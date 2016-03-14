#!/bin/bash

opencv_traincascade -data classifier/ -vec cropped.vec -bg negatives.txt -numPos 1000 -numNeg 500 -numStages 20 -precalcValBufSize 1024 -precalcIdxBufSize 1024 -featureType HAAR -minHitRate 0.995 -maxFalseAlarmRate 0.5 -w 20 -h 20
