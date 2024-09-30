#include "bmp.hpp"
#include <fstream>
#include <stdexcept>
#include <vector>

namespace bmp_reader{

    BMP::BMP(const char* filename){
        std::ifstream stream{filename,std::ios_base::binary};
        if(!stream){
            stream.close();
			throw std::runtime_error("can't open file");
        }
        stream.read((char*) &file_header, sizeof(file_header));
        // ensure it is a bmp
        if(file_header.file_type != TYPE_MAGIC){
            stream.close();
            throw std::runtime_error("unrecognized file type");
        }
        stream.read((char*) &info_header, sizeof(info_header));
        // check for bit count
        if(info_header.bit_count == 32){
            stream.close();
            throw std::runtime_error("32 bit bitmaps are unsupported");
        }
        // go to the image data
        stream.seekg(file_header.offset_data, std::ios_base::beg);
        // height may be negative
        int32_t size = info_header.width*abs(info_header.height)*3; // 3 channels since we work with 24 bit bitmaps
        data = (uint8_t*) malloc(size);
        // each row in BMP must be padded to multiples of 4 bytes
        // otherwise the pixel data would be wrong
        if(info_header.width % 4 == 0){
            // no padding needed
            stream.read((char*) data, size);
        }else{
            uint32_t row = info_header.width * 3;
            uint32_t new_row = row;
            // define how many additional bytes per row we need
            while(new_row % 4 != 0){
                ++new_row;
            }
            std::vector<uint8_t> padding(new_row - row);
            int32_t height = abs(info_header.height);
            // read pixel data from padded rows
            for(int y = 0; y < height; ++y){
                stream.read((char*) (data + row * y), row);
                stream.read((char*) padding.data(), padding.size());
            }
        }
        stream.close();
    }

    BMP::~BMP(){
        free(data);
    }
    
    void BMP::getRGB(const int32_t& x, const int32_t& y, int* r, int* g, int* b){
        // colors are stored in BGR format
        *r = (int)data[3 * (abs(y) * info_header.width + x) + 2];
        *g = (int)data[3 * (abs(y) * info_header.width + x) + 1];
        *b = (int)data[3 * (abs(y) * info_header.width + x) + 0];
    }

    int32_t BMP::getHeight(){
        return info_header.height;
    }

    int32_t BMP::getWidth(){
        return info_header.width;
    }

}