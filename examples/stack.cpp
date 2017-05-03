#include "algol/ds/stack/linked_stack.hpp"
#include "algol/perf/operation_counter.hpp"

namespace ds = algol::ds;

int main() {
  using operation_counter = algol::perf::operation_counter<std::int32_t, std::uint64_t>;
  {
    ds::linked_stack <operation_counter> op_count_stack;
    ds::linked_stack <operation_counter> op_count_stack2;

    operation_counter o1{1};
    operation_counter o2{2};
    operation_counter o3{3};
    operation_counter o4{4};
    operation_counter o5{5};
    operation_counter::reset();

    op_count_stack.push(o1);
    op_count_stack.push(o2);
    op_count_stack.push(o3);
    op_count_stack.push(o4);
    op_count_stack.push(o5);

    op_count_stack.pop();
    operation_counter o = op_count_stack.top();
    op_count_stack2 = op_count_stack;
  }
  operation_counter::report(std::cout);

  return 0;
}
