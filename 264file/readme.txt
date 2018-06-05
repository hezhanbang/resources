ffprobe -show_streams wangXiaoMin.mp4
ffmpeg.exe -i wangXiaoMin.mp4 -codec copy -bsf: h264_mp4toannexb -f h264 wangXiaoMin.264

split -b 10M ~/highProfile-level4.0-fp25-1920x1080-yuv420p-duration000405.264 264part-
cat 264part-* > highProfile-level4.0-fp25-1920x1080-yuv420p-duration000405.264

