#include <imgsim/search.hpp>
#include <imgsim/hash.hpp>
#include <algorithm>
#include <vector>
/*
 * there we just need to brute force every hash and compare it to the query
 * if the hammming distance is less we put it in the front of the vector
 * to solve it: the most common way is to use a comparator and sort the vector
 */
namespace imgsim {
    std::vector<imgsim::Match> brute_force_k(std::uint64_t query, std::vector<std::uint64_t>& hashes, std::size_t k){
        std::vector<imgsim::Match> matches;
        matches.reserve(hashes.size());
        for (std::size_t i = 0; i < hashes.size(); i++) {
            matches.push_back({imgsim::Match{
                .index = i,
                .distance = imgsim::hamming_distance(query, hashes[i]),
                .hash = hashes[i],
            }});
        }
        auto cmp = [](const imgsim::Match& a, const imgsim::Match& b) {
            if (a.distance != b.distance) {
                return a.distance < b.distance;
            }
            return a.index < b.index;
        };
        std::sort(matches.begin(), matches.end(), cmp);
        if (matches.size() > k)
            matches.resize(k);
        return matches;
    }
}
