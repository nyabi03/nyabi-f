#pragma once
#include <filesystem>
#include <utility>
#include <opencv2/core.hpp>
#include "types.hpp"

namespace nyabi
{
    class RawDecoder
    {
    public:
        [[nodiscard]] std::pair<cv::Mat, PhotoMetadata> decode(const std::filesystem::path &raw_path) const;

    private:
        static cv::Mat decode_raw(const std::filesystem::path &p);

        static PhotoMetadata extract_exif(const std::filesystem::path &p);
    };
} // namespace nyabi
