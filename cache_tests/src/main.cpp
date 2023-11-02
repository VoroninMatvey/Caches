#include <iostream>
#include <generator.hpp>

int main() {

    int capacity, numb_of_page, min_value_of_page, max_value_of_page, count;
    std::cin >> capacity >> numb_of_page >> min_value_of_page >> max_value_of_page >> count;
    Tests::generator gen(capacity, numb_of_page, min_value_of_page, max_value_of_page);
    gen.test_gen(count);
    return 0;
}
