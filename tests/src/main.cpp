#include <iostream>
#include <generator.hpp>

int main() {

    int max_cache, min_cache, max_numb_of_page, min_numb_of_page, max_value_of_page, min_value_of_page, count;
    std::cin >> max_cache >> min_cache >> max_numb_of_page >> min_numb_of_page >> max_value_of_page >> min_value_of_page >> count;
    Tests::generator gen(max_cache, min_cache, max_numb_of_page, min_numb_of_page, max_value_of_page, min_value_of_page);
    gen.test_gen(count);
    return 0;
}
