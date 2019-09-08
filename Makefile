# Written By @juniorxsound <https://orfleisher.com>
image_tag := "juniorxsound/now:latest"
dockerfile := "Dockerfile.nvidia.gpu"

clean:
	rm -rf ./dist/* && rm -f ./video/transcode/*

setup: clean
	docker build -f ./docker/${dockerfile} -t ${image_tag}  ./

build: clean
	docker run -w /data --rm -it -v `pwd`:/data -t ${image_tag} g++ -std=c++11 -L/src src/components/TranscodingPipeline/TranscodingPipeline.cpp src/components/TranscodingProfile/TranscodingProfile.cpp src/main.cpp -o dist/now

x264:
	docker run --gpus all -w /data --rm -it -v `pwd`:/data -t ${image_tag} \
		-hwaccel cuvid -c:v h264_cuvid -i $(input) \
		-filter:v scale_npp=w=-1:h=360:format=nv12:interp_algo=lanczos -vcodec h264_nvenc -preset fast $(output)_360p.mp4 \
		-filter:v scale_npp=w=-1:h=240:format=nv12:interp_algo=lanczos -vcodec h264_nvenc -preset fast $(output)_240p.mp4
shell:
	docker run --gpus all -w /data --rm -it -v `pwd`:/data -t ${image_tag} /bin/bash

run:
	docker run --gpus all -w /data --rm -it -v `pwd`:/data -t ${image_tag} ./dist/now

## -filter:v scale_npp=w=-1:h=720:format=nv12:interp_algo=lanczos -vcodec h264_nvenc -preset fast $(output)_720p.mp4 \
		-filter:v scale_npp=w=-1:h=480:format=nv12:interp_algo=lanczos -vcodec h264_nvenc -preset fast $(output)_480p.mp4 \