#include <stdexcept>
#include <string>
#include <libraw/libraw.h>
#include <exiv2/exiv2.hpp>
#include <opencv2/imgproc.hpp>
#include <spdlog/spdlog.h>
#include "raw_decoder.hpp"

namespace nyabi
{
    // -- Public --
    std::pair<cv::Mat, PhotoMetadata> RawDecoder::decode(const std::filesystem::path &raw_path) const
    {
        spdlog::debug("Decoding RAW: {}", raw_path.string());
        auto image = decode_raw(raw_path);
        auto meta = extract_exif(raw_path);

        return {std::move(image), std::move(meta)};
    }

    // -- Private --
    cv::Mat RawDecoder::decode_raw(const std::filesystem::path &p)
    {
    }
} // namespace nyabi
