/* 
 * File:   CronExpression_test.cpp
 * Author: alex
 *
 * Created on June 17, 2016, 4:35 PM
 */

#include "staticlib/cron/CronExpression.hpp"

#include <iostream>
#include <cstring>

#include "staticlib/config/assert.hpp"

namespace sc = staticlib::cron;

void test() {
    
}

int main() {
    try {
        test();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
    return 0;
}

