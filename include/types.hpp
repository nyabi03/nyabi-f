#pragma once
#include <cstdint>
#include <filesystem>
#include <optional>
#include <span>
#include <string>
#include <vector>
#include <opencv2/core.hpp>

namespace nyabi
{
    // -- Embedding --
    using Embedding = std::vector<float>;

    // -- Detection --
    struct BBox
    {
        float x, y, w, h;
        float confidence;
    };

    struct Crop
    {
        cv::Mat image;
        BBox bbox;
    };

    // -- Character DB --
    struct Character
    {
        int64_t id;
        std::string name;
        Embedding embedding;
        std::vector<float> hsv_histogram;
    };

    struct CharacterMatch
    {
        std::string name;
        float similarity;
    };

    // -- EXIF / Metadata --
    struct PhotoMetadata
    {
        std::string camera_model;
        std::string lens_model;
        std::string datetime_original;
        double focal_length = 0.0;
        double aperture = 0.0;
        double shutter_speed = 0.0;
        int iso = 0;
    };

    // -- Pipeline Results --
    struct CropResult
    {
        Crop crop;
        std::optional<CharacterMatch> match; // nullopt -> unclassified
    };

    struct ClassificationResult
    {
        std::filesystem::path source;
        PhotoMetadata metadata;
        std::vector<CropResult> crops;
    };

    // -- Configs --
    struct Config
    {
        std::filesystem::path detector_model_path;
        std::filesystem::path embedder_model_path;
        std::filesystem::path db_path;
        std::filesystem::path output_root;

        float detection_confidence_threshold = 0.5f;
        float color_histogram_threshold = 0.30f;
        float similarity_threshold = 0.75f;

        int detector_input_size = 640;
        int embedder_input_size = 224;
        int hsv_bins = 16;
    };
} // namespace nyabi
