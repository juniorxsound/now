#ifndef _TRANSCODING_PIPELINE_H_
#define _TRANSCODING_PIPELINE_H_

#include <vector>
#include <string.h>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include <bits/stdc++.h>
#include <stdio.h>

#include "../TranscodingProfile/TranscodingProfile.h"

class TranscodingPipeline {
    public:
        TranscodingPipeline(const std::string &_inputFile,
                            const std::string &_inputDecoder,
                            const int &_batchSize);
        ~TranscodingPipeline();

        // Add a profiles to the pipeline
        void addProfile(const TranscodingProfile &_profile);
        // void addProfiles(const std::vector<TranscodingProfile> &profiles);

        const int transcode();
    private:
        std::string CreateFFMPEGCommand(std::vector<TranscodingProfile> profiles);

        std::vector<TranscodingProfile> profiles;
        const int batchSize;
        const std::string inputFile;
        const std::string inputDecoder;
        const std::string ffmpegCmdPrefix;
};

#endif // _TRANSCODING_PIPELINE_H_