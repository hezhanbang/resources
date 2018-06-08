ffprobe -show_streams wangXiaoMin.mp4
ffmpeg.exe -i wangXiaoMin.mp4 -codec copy -bsf: h264_mp4toannexb -f h264 wangXiaoMin.264

split -b 10M ~/highProfile-level4.0-fp25-1920x1080-yuv420p-duration000405.264 264part-
cat 264part-* > highProfile-level4.0-fp25-1920x1080-yuv420p-duration000405.264

#find all frame type(I-frmae, P-frame or B-frame) in 264 file or mp4 file:
ffprobe -show_frames videofilename.mp4 > frameInfo.txt

#remove first byte in one file:
tail -c +2 test.264 > noPframe.264  #"-2", copying data begin the second byte in the file.

split -b 10M noPframe.264 noPframe-
cat noPframe-* > noPframe.264
