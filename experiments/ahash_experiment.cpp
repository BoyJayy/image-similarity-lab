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
};

signed main() {
    const fs::path dir = "experiments/pics";
    const fs::path original_path = dir / "original.jpeg";
    imgsim::ImgHash orig_hash = imgsim::average_hash(original_path);
    std::vector<Exp> pics = {
        {"copy",dir / "copy.jpeg"},
        {"copy of a copy",dir / "copy copy.jpeg"},
        {"rotate",dir / "rotate.jpeg"},
        {"resized",dir / "resized.jpeg"},
        {"crop", dir / "crop.jpeg"},
        {"different1",dir / "different1.jpeg"},
        //{"different2",dir / "different2.jpeg"},
    };
    std::cout << std::left << std::setw(15) <<"image"<<"distance\n";
    for (auto& pic: pics) {
        imgsim::ImgHash pichash = imgsim::average_hash(pic.path);
        std::uint32_t d = imgsim::hamming_distance(orig_hash, pichash);
        std::cout << std::setw(15) << pic.name << d << '\n';
    }

}