#ifndef _TRANSCODING_PROLFILE_H_
#define _TRANSCODING_PROLFILE_H_

#include <string>
#include <iostream>

class TranscodingProfile {
    public:
        TranscodingProfile(const int &_height,
                           const std::string &__averageBitrate,
                           const std::string &_profile,
                           const std::string &_encoderType,
                           const std::string &_namePrefix);

        ~TranscodingProfile();

        // Getter for the transcoding profile assembled as a string for FFMPEG
        const std::string getProfile();

    private:

        const int height;
        const int width;

        const std::string namePrefix;
        const std::string averageBitrate;
        const std::string profile;
        const std::string yuvScalingFormat;
        const std::string encoderType;
};

#endif // _TRANSCODING_PROLFILE_H_