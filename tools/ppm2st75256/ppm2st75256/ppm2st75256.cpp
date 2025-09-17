#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
#include <string>
#include <sstream>

// Simple grayscale threshold
inline uint8_t rgb_to_gray(uint8_t r, uint8_t g, uint8_t b) {
    return static_cast<uint8_t>((r * 30 + g * 59 + b * 11) / 100);
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: ppm2st75256 input.ppm output.bin\n";
        return 1;
    }

    std::ifstream in(argv[1], std::ios::binary);
    if (!in) {
        std::cerr << "Error: cannot open input file\n";
        return 1;
    }

    std::string magic;
    in >> magic;
    if (magic != "P6") {
        std::cerr << "Error: only binary PPM (P6) supported\n";
        return 1;
    }

    int width, height, maxval;
    in >> width >> height >> maxval;
    in.ignore(); // skip single whitespace

    if (width != 256 || height != 160) {
        std::cerr << "Error: input image must be exactly 256x160\n";
        return 1;
    }

    std::vector<uint8_t> rgb(width * height * 3);
    in.read(reinterpret_cast<char*>(rgb.data()), rgb.size());

    std::vector<uint8_t> out(256 * (160 / 8), 0);

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int idx = (y * width + x) * 3;
            uint8_t gray = rgb_to_gray(rgb[idx], rgb[idx + 1], rgb[idx + 2]);

            int page = y / 8;
            int bit = y % 8;
            if (gray < 128) { // black pixel = ON
                out[page * 256 + x] |= (1 << bit);
            }
        }
    }

    std::ofstream fout(argv[2], std::ios::binary);
    fout.write(reinterpret_cast<char*>(out.data()), out.size());
    fout.close();

    std::cout << "Converted " << argv[1] << " -> " << argv[2]
        << " (" << out.size() << " bytes)\n";

    return 0;
}
