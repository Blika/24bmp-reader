#include "bmp/bmp.hpp"
#include <iostream>
#include <stdexcept>

using namespace bmp_reader;

const char BLACK = 'A';
const char WHITE = '`';

void displayBMP(BMP* p_bmp){
    int32_t height = abs(p_bmp->getHeight());
    for(int32_t y = 0; y < height; ++y){
        for(int32_t x = p_bmp->getWidth()-1; x > -1; --x){
            int r,g,b;
            p_bmp->getRGB(x,y,&r,&g,&b);
            if(r == 0 && g == 0 && b == 0){
                std::cout << BLACK;
            }else if(r == 255 && g == 255 && b == 255){
                std::cout << WHITE;
            }
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}

int main(int argc, const char** argv){
    for(int i = 1; i < argc; ++i){
        try{
            BMP* bmp = new BMP(argv[i]);
            displayBMP(bmp);
            delete bmp;
            if(i < argc-1){
                std::cout << '\n';
                std::cout << "==================================================================================" << '\n';
                std::cout << '\n';
            }
        }catch(const std::exception& e){
            std::cerr << e.what() << '\n';
            // skip unsupported files without crashing program
            continue;
        }
    }
    return 0;
}