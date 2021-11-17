#include <algorithm>
#include <functional>
#include <string>

namespace util {

auto contains(const std::string& in, const std::string& needle)
{
    auto it = std::search(in.begin(), in.end(),
        std::boyer_moore_searcher(
            needle.begin(), needle.end()));
    return it;
}

}