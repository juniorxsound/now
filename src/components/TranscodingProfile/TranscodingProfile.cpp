#include "TranscodingProfile.h"

TranscodingProfile::TranscodingProfile(const int &_height,
                                       const std::string &_averageBitrate,
                                       const std::string &_profile,
                                       const std::string &_encoderType,
                                       const std::string &_namePrefix) :
                                       height(_height),
                                       width(-1),
                                       averageBitrate(_averageBitrate),
                                       profile(_profile),
                                       yuvScalingFormat("nv12"),
                                       encoderType(_encoderType),
                                       keyFrameSecondInterval(3),
                                       namePrefix(_namePrefix) {}

TranscodingProfile::~TranscodingProfile() {}

const std::string TranscodingProfile::getProfile() {
    return "-filter:v scale_npp=w=" + std::to_string(width) + ":h=" + std::to_string(height) +
            ":format=" + yuvScalingFormat + ":interp_algo=lanczos " +
            "-vcodec " + encoderType + " " +
            "-preset " + profile + " " +
            "-force_key_frames 'expr:gte(t,n_forced*" + std::to_string(keyFrameSecondInterval) + ")' " +
            namePrefix + "_" + std::to_string(height) + "p.mp4";
}