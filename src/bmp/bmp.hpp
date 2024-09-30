#pragma once

#include <cstdint>

namespace bmp_reader{

    // file type magic value
    const uint16_t TYPE_MAGIC = 0x4D42;

    // relevant headers to work with 24-bit bitmaps
    #pragma pack(push, 2)
    struct FileHeader{
        uint16_t file_type;
        uint32_t file_size;
        uint16_t reserved1;
        uint16_t reserved2;
        uint32_t offset_data;
    };

    struct InfoHeader{
        uint32_t size;
        int32_t width;
        int32_t height;
        uint16_t planes;
        uint16_t bit_count;
        uint32_t compression;
        uint32_t size_image;
        int32_t x_pixels_per_meter;
        int32_t y_pixels_per_meter;
        uint32_t colors_used;
        uint32_t colors_important;
    };
    #pragma pack(pop)

    class BMP{

        public: 
            BMP(const char* filename);
            ~BMP();

            void getRGB(const int32_t& x, const int32_t& y, int* r, int* g, int* b);
            int32_t getHeight();
            int32_t getWidth();

        private:
            FileHeader file_header;
            InfoHeader info_header;

            // image data, BGR format
            uint8_t* data;
    };
}