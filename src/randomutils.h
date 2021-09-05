#pragma once

// system includes
#include <random>

namespace cpputils {

template<typename T, typename Trandom>
T randomNumber(T min, T max, Trandom &&rng)
{
    std::uniform_int_distribution<T> dist{min, max};
    return dist(rng);
}

//template<typename Trandom>
//float randomNumber<float, Trandom>(float min, float max, Trandom &rng)
//{
//    std::uniform_real_distribution<float> dist{min, max};
//    return dist(rng);
//}

//template<typename Trandom>
//double randomNumber<double, Trandom>(double min, double max, Trandom &rng)
//{
//    std::uniform_real_distribution<double> dist{min, max};
//    return dist(rng);
//}

template<typename T, typename Trandom>
T randomNumber(T max, Trandom &&rng)
{
    std::uniform_int_distribution<T> dist{{}, max};
    return dist(rng);
}

//template<typename Trandom>
//float randomNumber<float, Trandom>(float max, Trandom &rng)
//{
//    std::uniform_real_distribution<float> dist{{}, max};
//    return dist(rng);
//}

//template<typename Trandom>
//double randomNumber<double, Trandom>(double max, Trandom &rng)
//{
//    std::uniform_real_distribution<double> dist{{}, max};
//    return dist(rng);
//}

} // namespace cpputils
