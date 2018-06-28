ffprobe -show_streams wangXiaoMin.mp4
ffmpeg.exe -i wangXiaoMin.mp4 -codec copy -bsf: h264_mp4toannexb -f h264 wangXiaoMin.264

split -b 10M ~/highProfile-level4.0-fp25-1920x1080-yuv420p-duration000405.264 264part-
cat 264part-* > highProfile-level4.0-fp25-1920x1080-yuv420p-duration000405.264

#find all frame type(I-frmae, P-frame or B-frame) in 264 file or mp4 file:
ffprobe videofilename.mp4 -show_frames > frameInfo.txt

#remove first byte in one file:
tail -c +2 test.264 > noBframe.264  #"-2", copying data begin the second byte in the file.

split -b 10M noBframe.264 noBframe-
cat noBframe-* > noBframe.264

#generate fragment mp4 file (fMp4) from noBframe.264 file
ffmpeg -framerate 25 -i noBframe.264 -c copy temp.mp4
ffmpeg -i temp.mp4 -c copy -f mp4 -movflags frag_keyframe+empty_moov fragment.mp4

