#include "TranscodingPipeline.h"

TranscodingPipeline::TranscodingPipeline(const std::string &_inputFile,
                                         const std::string &_inputDecoder,
                                         const int &_batchSize) : 
                                         inputFile(_inputFile),
                                         batchSize(_batchSize),
                                         inputDecoder(_inputDecoder),
                                         ffmpegCmdPrefix("ffmpeg -hwaccel cuvid -c:v") {}

TranscodingPipeline::~TranscodingPipeline() {}

void TranscodingPipeline::addProfile(const TranscodingProfile &_profile) {
    profiles.push_back(_profile);
}

const int TranscodingPipeline::transcode() {

    // Split the vector into sub vectors of size batchSize (n)
    int size = (profiles.size() - 1) / batchSize + 1;

    // Store the return codes from calling ffmpeg
    int ret = 0;

    for (int i = 0; i < size; ++i) {
        // Get the ranges
        const int start_iter = i * batchSize;
        const int end_iter = i * batchSize + batchSize;

        // Deal with the last sub batch that doesn't fill a batch
        if (i * batchSize + batchSize > profiles.size()) {
            std::vector<TranscodingProfile> projectsSlice(&profiles[start_iter], &profiles[profiles.size()]);
            std::string cmd = this->CreateFFMPEGCommand(projectsSlice); 
            ret = std::system(cmd.c_str());
            return ret;
            
        }

        std::vector<TranscodingProfile> projectsSlice(&profiles[start_iter], &profiles[end_iter]);
        std::string cmd = this->CreateFFMPEGCommand(projectsSlice); 
        ret = std::system(cmd.c_str());
    }
    return ret;
}

std::string TranscodingPipeline::CreateFFMPEGCommand(std::vector<TranscodingProfile> profiles) {
    std::string cmd = ffmpegCmdPrefix + " " + inputDecoder + " -i " + inputFile;

    for(std::vector<TranscodingProfile>::iterator it = profiles.begin(); it != profiles.end(); it++) {
        cmd += " " + it->getProfile();
    }
    return cmd;
}