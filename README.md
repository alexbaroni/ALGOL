# ALGOL
Utility library for algorithm analysis

Utlility classes for measuring executionn time, operation count (ctor, move, operator, ...) and pretty printing STL containers.  

For pretty printing credits goes to:  
https://louisdx.github.io/cxx-prettyprint/ i simply repackaged into my namespace. 

Tests and some examples are in tests and examples folder.  

Example:  

```cpp
#include <iostream>
#include <array>
#include "algol/io/pprint.hpp"
#include "algol/perf/stopwatch.hpp"
#include "algol/perf/operation_counter.hpp"

#define COMMA ,
PPRINT_DEFAULT_DECORATION(std::array<T COMMA N>, "[", "; ", "]", class T, std::size_t N)

int main()
{
    using stopwatch = algol::perf::stopwatch<std::chrono::microseconds>;
    using operation_counter = algol::perf::operation_counter<std::int32_t, std::uint64_t>;

    stopwatch sw;

    std::array<operation_counter, 10> values{2, 3, 5, 1, 10, 9, 4, 6, 8, 7};
    std::cout << values << std::endl;
    for (auto v : values) {
        if (v == 6)
            break;
    }

    std::cout << sw << std::endl;
    //operation_counter::report(std::cout);
    std::cout << "Assignments: " << operation_counter::assignments() << '\n';
    std::cout << "Comparisons: " << operation_counter::equal_comparisons() << std::endl;

    return 0;
}
```
