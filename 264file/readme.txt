ffprobe -show_streams wangXiaoMin.mp4
ffmpeg.exe -i wangXiaoMin.mp4 -codec copy -bsf: h264_mp4toannexb -f h264 wangXiaoMin.264