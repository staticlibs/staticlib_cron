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

void test_simple() {
    sc::CronExpression cron{"* * * * * *"};
    auto secs = cron.next();
    slassert(1 == secs.count())
}

void test_format() {
    sc::CronExpression cron{"* * * * * *", "%Y-%m-%dT%H:%M:%S"};
    auto secs = cron.next("2012-07-01T09:00:00");
    slassert(1 == secs.count())
}

int main() {
    try {
        test_simple();
        test_format();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
    return 0;
}

