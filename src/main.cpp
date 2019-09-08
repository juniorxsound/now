#include <iostream> 

#include "components/TranscodingProfile/TranscodingProfile.h"
#include "components/TranscodingPipeline/TranscodingPipeline.h"

int main(int argc, char *argv[])
{
	std::cout << std::endl
		<< "Welcome to Now! A GPU accelerated transcoder 📽" << std::endl
		<< "Written by @juniorxsound <https://orfleisher.com>" << std::endl
		<< std::endl;

    // Create the pipeline
    TranscodingPipeline pipeline("./video/BigBuckBunny.mp4", "h264_cuvid", 2);
    pipeline.addProfile(TranscodingProfile(240, "2M", "fast", "h264_nvenc", "./video/transcode/BigBuckBunny"));
    pipeline.addProfile(TranscodingProfile(360, "3M", "fast", "h264_nvenc", "./video/transcode/BigBuckBunny"));
    pipeline.addProfile(TranscodingProfile(480, "4M", "fast", "h264_nvenc", "./video/transcode/BigBuckBunny"));
    pipeline.addProfile(TranscodingProfile(720, "5M", "fast", "h264_nvenc", "./video/transcode/BigBuckBunny"));
    const int ret = pipeline.transcode();
    return ret;
}