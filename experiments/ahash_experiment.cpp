#include "imgsim/hash.hpp"
#include <imgsim/image.hpp>
#include <iomanip>
#include <ios>
#include <iostream>
#include <vector>


namespace fs = std::filesystem;

struct Exp {
    std::string name;
    fs::path path;
    bool same_source;
};

signed main() {
    const fs::path dir = "experiments/pics";
    const fs::path original_path = dir / "original.jpeg";
    imgsim::ImgHash orig_hash = imgsim::average_hash(original_path);
    std::vector<Exp> pics = {
        {"copy", dir / "copy.jpeg",       1},
        {"copy2",dir / "copy copy.jpeg",  1},
        {"resized",dir / "resized.jpeg",    1},
        {"compressed",dir / "compress.jpeg",   1},
        {"bright",dir / "bright.jpg",      1},
        {"dark", dir / "dark.jpg",        1},
        {"crop",dir / "crop.jpeg",       1},
        {"rotate", dir / "rotate.jpeg",     1},
        {"different1",dir / "different1.jpeg", 0},
        {"different2", dir / "different2.jpeg", 0},
        {"different3", dir / "different3.jpeg", 0},
        {"different4", dir / "different4.jpeg", 0},
        {"different5", dir / "different5.jpeg", 0},
    };
    std::cout << std::left << std::setw(15) <<"image"<<"distance\n";
    for (auto& pic: pics) {
        imgsim::ImgHash pichash = imgsim::average_hash(pic.path);
        std::uint32_t d = imgsim::hamming_distance(orig_hash, pichash);
        std::cout<< std::setw(15) << pic.name<< std::setw(15) << (pic.same_source ? "same" : "different")<< d << '\n';
    }

}