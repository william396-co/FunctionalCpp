#pragma once
#include <chrono>
#include <functional>
#include <ratio>
#include <string>
#include <utility>
#include <iomanip>
#include <type_traits>
#include "print.h"

namespace utils {

// use steady_clock or high_resolution_clock
template<typename Time = std::chrono::microseconds, typename Clock = std::chrono::high_resolution_clock>
struct perf_timer
{

    template<typename F, typename... Args>
    static Time duration( F && f, Args... args )
    {
        auto start = Clock::now();
        std::invoke( std::forward<F>( f ), std::forward<Args>( args )... );
        auto end = Clock::now();
        return std::chrono::duration_cast<Time>( end - start );
    }
};

// millseconds evalute executing time
template<typename Time = std::chrono::microseconds, typename F, typename... Args>
void perf_timer_out( std::string const & note, F && f, Args &&... args )
{
    auto t = perf_timer<Time, std::chrono::high_resolution_clock>::duration(
        std::forward<F>( f ), std::forward<Args>( args )... );

    using namespace std::chrono;
    using namespace std::chrono_literals;
    if constexpr ( std::is_same_v<Time, microseconds> ) {
        println( "executing timer:", std::setw( 20 ), duration<double, std::micro>( t ).count(), " microseconds[ ", note, " ]" );
    } else if constexpr ( std::is_same_v<Time, nanoseconds> ) {
        println( "executing timer:", std::setw( 10 ), duration<double, std::nano>( t ).count(), " nanoseconds[ ", note, " ]" );
    } else if constexpr ( std::is_same_v<Time, milliseconds> ) {
        println( "executing timer:", std::setw( 10 ), duration<double, std::milli>( t ).count(), " milliseconds[ ", note, " ]" );
    }
}

} // namespace utils
