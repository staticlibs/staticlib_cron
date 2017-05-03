/*
 * Copyright 2016, alex at staticlibs.net
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/* 
 * File:   expression_test.cpp
 * Author: alex
 *
 * Created on June 17, 2016, 4:35 PM
 */

#include "staticlib/cron/expression.hpp"

#include <iostream>
#include <cstring>

#include "staticlib/config/assert.hpp"

void test_simple() {
    sl::cron::expression cron{"* * * * * *"};
    std::chrono::milliseconds secs = cron.next<std::chrono::milliseconds>();
    slassert(1000 == secs.count())
}

void test_format() {
    sl::cron::expression cron{"* * * * * *", "%Y-%m-%dT%H:%M:%S"};
    auto secs = cron.next<std::chrono::seconds>("2012-07-01T09:00:00");
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

