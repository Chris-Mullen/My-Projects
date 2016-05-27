function mpg
	system("rm -rf mpg-out; mkdir mpg-out");
	%system("ffmpeg -i tmp/frame%d.png mpg-out/out.mpg");

	%-qmax (max video quantize scale (default 31) 0->839.9kb(avi)/834.3kb(mp4))
	%system("ffmpeg -i tmp/frame%05d.png -qmax 1 -bf 10 mpg-out/out.mp4"); %%DATA LOSS
        system("ffmpeg -i holframes/frame%05d.png -qmax 1 mpg-out/out.mp4");
	%system("ffmpeg -i tmp/frame%05d.png -qmax 1 mpg-out/out.avi");
	%system("ffmpeg -i tmp/frame%05d.png -qmax 1 mpg-out/out.mpg");

	%system("ffmpeg -i tmp/frame%d.png -ps 3 mpg-out/out.mp4");  %2.8mb
	%system("ffmpeg -i tmp/frame%d.png -ps 3 mpg-out/out.avi");  %2.8mb

	%system("ffmpeg -i tmp/frame%d.png -ps 2 mpg-out/out.mp4");  %2.8mb
	%system("ffmpeg -i tmp/frame%d.png -ps 2 mpg-out/out.avi");  %2.8mb

	%system("ffmpeg -i tmp/frame%d.png -ps 1 mpg-out/out.mp4");  %2.8mb
	%system("ffmpeg -i tmp/frame%d.png -ps 1 mpg-out/out.avi");  %2.8mb

	%system("ffmpeg -i tmp/frame%d.png -ps 0 mpg-out/out.mp4");  %2mb
	%system("ffmpeg -i tmp/frame%d.png -ps 0 mpg-out/out.avi");  %2mb

	%system("ffmpeg -i tmp/frame%d.png -b_strategy 1 mpg-out/out.mp4");  %2mb
	%system("ffmpeg -i tmp/frame%d.png -b_strategy 1 mpg-out/out.avi");  %2mb

	%system("ffmpeg -i tmp/frame%d.png -b_qfactor 0 mpg-out/out.mp4");  %2mb
	%system("ffmpeg -i tmp/frame%d.png -b_qfactor 0 mpg-out/out.avi");  %2mb

	%system("ffmpeg -i tmp/frame%d.png -bf 0 mpg-out/out.mp4");  %2mb
	%system("ffmpeg -i tmp/frame%d.png -bf 0 mpg-out/out.avi");  %2mb

	%system("ffmpeg -i tmp/frame%d.png -bf 2 mpg-out/out.mp4");  %2.1mb
	%system("ffmpeg -i tmp/frame%d.png -bf 2 mpg-out/out.avi");  %2.1mb

	%system("ffmpeg -i tmp/frame%d.png -bf 5 mpg-out/out.mp4");  %2.1mb
	%system("ffmpeg -i tmp/frame%d.png -bf 5 mpg-out/out.avi");  %2.1mb

	%system("ffmpeg -i tmp/frame%d.png -bf 10 mpg-out/out.mp4");  %2.2mb
	%system("ffmpeg -i tmp/frame%d.png -bf 10 mpg-out/out.avi");  %2.2mb

	%system("ffmpeg -i tmp/frame%d.png -bf 16 mpg-out/out.mp4");
	%system("ffmpeg -i tmp/frame%d.png -bf 16 mpg-out/out.avi");

	%system("ffmpeg -i tmp/frame%d.png -qdiff 0 mpg-out/out.mp4");
	%system("ffmpeg -i tmp/frame%d.png -qdiff 0 mpg-out/out.avi");

	%%BASIC CONVERSION
	%system("ffmpeg -i tmp/frame%d.png mpg-out/out.mp4");
	%system("ffmpeg -i tmp/frame%d.png mpg-out/out.avi");

	%%MOTION COMPENSATION PARAMETERS
	%system("ffmpeg -i tmp/frame%d.png -cmp sad mpg-out/out.mp4");%sad==0 (absolute differences(motioncomp))
	%system("ffmpeg -i tmp/frame%d.png -cmp sad mpg-out/out.avi");%sad==0 (absolute differences(motioncomp))
	%system("ffmpeg -i tmp/frame%d.png -flags qpel mpg-out/out.avi");%sad==0 (absolute differences(motioncomp))
	%system("ffmpeg -i tmp/frame%d.png -flags qpel mpg-out/out.mp4");%sad==0 (absolute differences(motioncomp))

	%system("ffmpeg -i tmp/frame%d.png -b 100 mpg-out/out.mp4");
	%system("ffmpeg -i tmp/frame%d.png -b 100 mpg-out/out.avi");

	%system("ffmpeg -i tmp/frame%d.png -flags ilme mpg-out/out.mp4");
	%system("ffmpeg -i tmp/frame%d.png -flags ilme mpg-out/out.avi");	

	%system("ffmpeg -i tmp/frame%d.png -me_method epzs mpg-out/out.mp4");
	%system("ffmpeg -i tmp/frame%d.png -me_method epzs mpg-out/out.avi");

	%system("ffmpeg -i tmp/frame%d.png -me_method zero -ac 0 mpg-out/out.mp4");
	%system("ffmpeg -i tmp/frame%d.png -me_method zero -ac 0 mpg-out/out.avi");

	%-bf (number of b-frames, 0->2mb, <0->2.1mb)
	%system("ffmpeg -i tmp/frame%d.png -bf 0 mpg-out/out.mp4");
	%system("ffmpeg -i tmp/frame%d.png -bf 0 mpg-out/out.avi");

	%system("ffmpeg -f image2 -i tmp/frame%d.png  mpg-out/mymov.avi ");
	%system("ffmpeg -y -i tmp/frame%d.png -vcodec libx264 mpg-out/mymov.avi");
	%system("ffmpeg -i tmp/frame%d.png -vcodec libx264 -crf 20 mpg-out/out.mp4");
	
	%BEST SO FAR
	%system("ffmpeg -i tmp/frame%d.png mpg-out/frames.avi");


	%lossless codecs
	%system("ffmpeg -i tmp/frame%d.png -vcodec huffyuv mpg-out/huffyuv.avi");
	%system("ffmpeg -i tmp/frame%d.png -vcodec ffv1 mpg-out/ffv1.avi");
	%system("ffmpeg -i tmp/frame%d.png -vcodec v308 mpg-out/output.avi");

	%-same but each frame *20 (to be able to see better)
	%system("ffmpeg -i mpg-out/out.avi -vf \"setpts=20.0*PTS\" mpg-out/out_avi_20.avi");
	%system("ffmpeg -i mpg-out/out.mp4 -vf \"setpts=20.0*PTS\" mpg-out/out_mp4_20.mp4");
	end

