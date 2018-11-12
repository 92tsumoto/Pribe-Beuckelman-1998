#!/bin/sh

ffmpeg -i %04d.png -vcodec mjpeg -qscale 0 PB_AP.avi


ffmpeg -r 50 -i %04d.png -vcodec mjpeg -qscale 0 PB_AP2.avi
ffmpeg -r 100 -i %04d.png -vcodec mjpeg -qscale 0 PB_AP3.avi
