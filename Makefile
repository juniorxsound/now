# Written By @juniorxsound <https://orfleisher.com>
image_tag := "juniorxsound/now:latest"
dockerfile := "Dockerfile.nvidia.gpu"

clean:
	rm -rf ./dist/*

setup: clean
	docker build -f ./docker/${dockerfile} -t ${image_tag}  ./

x264:
	docker run --gpus all -w /data --rm -it -v `pwd`:/data -t ${image_tag} \
		-hwaccel cuvid -c:v h264_cuvid -i $(input) \
		-vf scale_npp=1280:720 -vcodec h264_nvenc $(output)_720p.mp4 \
		-vf scale_npp 640:480 -vcodec h264_nvenc $(output)_480p.mp4 \
		-vf scale_npp 480:360 -vcodec h264_nvenc $(output)_360p.mp4 \
		-vf scale_npp 352:240 -vcodec h264_nvenc $(output)_240p.mp4

run:
	docker run -t ${image_tag}