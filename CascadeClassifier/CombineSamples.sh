#!/bin/bash

opencv_createsamples -info samples/positives.txt -bg negative_images/negatives.txt -vec cropped.vec -num 1280 -w 20 -h 20