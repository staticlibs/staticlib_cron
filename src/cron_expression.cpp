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
 * File:   cron_expression.cpp
 * Author: alex
 * 
 * Created on June 17, 2016, 4:42 PM
 */

#include "staticlib/cron/cron_expression.hpp"

#include "ccronexpr.h"

#include <memory>
#include <ctime>
#include <cmath>
#include <ios>
#ifdef STATICLIB_WINDOWS
#include <iomanip>
#include <sstream>
#endif // STATICLIB_WINDOWS

#include "staticlib/config.hpp"
#include "staticlib/pimpl/pimpl_forward_macros.hpp"

// access to non-public cron_expr api
extern "C" time_t cron_mktime(struct tm* tm);

namespace staticlib {
namespace cron {

namespace { // anonymous

namespace sc = staticlib::config;

class cron_expr_deleter {
public:
    void operator()(cron_expr* ce) {
        cron_expr_free(ce);
    }
};

} // namespace

class cron_expression::impl : public staticlib::pimpl::pimpl_object::impl {
    std::string expression;
    std::string date_format;
    std::unique_ptr<cron_expr, cron_expr_deleter> cron;
    
public:

    impl(std::string expression, std::string date_format) :
    expression(std::move(expression)),
    date_format(std::move(date_format)) {
        const char* err = nullptr;
        cron_expr* cron_ptr = cron_parse_expr(this->expression.c_str(), &err);
        if (err) {
            throw cron_exception(TRACEMSG("Invalid cron expression specified:" + 
                    " [" + this->expression + "]"));
        }
        this->cron = std::unique_ptr<cron_expr, cron_expr_deleter>{cron_ptr, cron_expr_deleter{}};
    }

    std::chrono::seconds next(const cron_expression&) const {
        auto now = std::chrono::system_clock::now();
        time_t date = std::chrono::system_clock::to_time_t(now);
        return next_internal(date);
    }

    std::chrono::seconds next(const cron_expression&, const std::string& curdate) const {
        time_t date = parse_date(curdate);
        return next_internal(date);
    }
    
private:
    std::chrono::seconds next_internal(time_t curdate) const {
        time_t res = cron_next(cron.get(), curdate);
        if (static_cast<time_t> (-1) == res) {
            throw cron_exception(TRACEMSG("Error cron calculation," +
                    " curdate: [" + sc::to_string(curdate) + "]," +
                    " expression: [" + this->expression + "]" + 
                    " date_format: [" + this->date_format + "]"));
        }
        double diff = std::difftime(res, curdate);
        long long lldiff = ::llround(diff);
        return std::chrono::seconds{lldiff};
    }
    
    time_t parse_date(const std::string& datestr) const {
        struct tm cal;
#ifdef STATICLIB_WINDOWS
        std::istringstream input{datestr};
        input.imbue(std::locale(setlocale(LC_ALL, nullptr)));
        input >> std::get_time(std::addressof(cal), this->date_format.c_str());
        if (input.fail()) {
            throw cron_exception(TRACEMSG("Error parsing specified" +
                    "  date: [" + datestr + "], with format: [" + this->date_format + "]"));
        }
#else // STATICLIB_WINDOWS
        auto last_parsed = ::strptime(datestr.c_str(), this->date_format.c_str(), std::addressof(cal));
        if (nullptr == last_parsed) {
            throw cron_exception(TRACEMSG("Error parsing specified" +
                    "  date: [" + datestr + "], with format: [" + this->date_format + "]"));
        }
#endif // STATICLIB_WINDOWS
        return cron_mktime(std::addressof(cal));
    }    
};
PIMPL_FORWARD_CONSTRUCTOR(cron_expression, (std::string)(std::string), (), cron_exception)
PIMPL_FORWARD_METHOD(cron_expression, std::chrono::seconds, next, (), (const), cron_exception)
PIMPL_FORWARD_METHOD(cron_expression, std::chrono::seconds, next, (const std::string&), (const), cron_exception)

} //namespace
}
