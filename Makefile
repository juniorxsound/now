# Written By @juniorxsound <https://orfleisher.com>
image_tag := "juniorxsound/now:latest"
dockerfile := "Dockerfile.nvidia.gpu"

clean:
	rm -rf ./dist/* && rm -f ./video/transcode/*

setup: clean
	docker build -f ./docker/${dockerfile} -t ${image_tag}  ./

build: clean
	docker run -w /data --rm -it -v `pwd`:/data -t ${image_tag} g++ -std=c++11 -L/src src/components/TranscodingPipeline/TranscodingPipeline.cpp src/components/TranscodingProfile/TranscodingProfile.cpp src/main.cpp -o dist/now

shell:
	docker run --gpus all -w /data --rm -it -v `pwd`:/data -t ${image_tag} /bin/bash

run:
	docker run --gpus all -w /data --rm -it -v `pwd`:/data -t ${image_tag} ./dist/now

download:
	curl -o video/BigBuckBunny.mp4 http://commondatastorage.googleapis.com/gtv-videos-bucket/sample/BigBuckBunny.mp4