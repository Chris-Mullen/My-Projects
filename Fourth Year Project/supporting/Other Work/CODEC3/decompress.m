function decompress
    system("rm -rf vidframes; mkdir vidframes");
    system("ffmpeg -i mpg-out/out.mp4 -qmax 1 vidframes/frame%05d.png");
    end
