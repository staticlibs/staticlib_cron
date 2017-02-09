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
 * File:   cron_expression.hpp
 * Author: alex
 *
 * Created on June 17, 2016, 11:25 AM
 */

#ifndef STATICLIB_CRON_CRONEXPRESSION_HPP
#define	STATICLIB_CRON_CRONEXPRESSION_HPP

#include <chrono>
#include <string>

#include "staticlib/pimpl.hpp"

#include "staticlib/cron/cron_exception.hpp"

namespace staticlib {
namespace cron {

/**
 * Cron expression implementation
 */
class cron_expression : public staticlib::pimpl::pimpl_object {
protected:
    /**
     * implementation class
     */
    class impl;    

public:
    /**
     * PIMPL-specific constructor
     * 
     * @param pimpl impl object
     */
    PIMPL_CONSTRUCTOR(cron_expression)    
            
    /**
     * Constructor
     * 
     * @param expression Cron expression
     * @param date_format date format for parsing `curdate` (optional),
     *        `%Y-%m-%d_%H:%M:%S` is used by default
     */
    cron_expression(std::string expression, std::string date_format = "%Y-%m-%d_%H:%M:%S");
    
    /**
     * Calculates a number of seconds to the next Cron fire event starting from the current instant
     * 
     * @return number of seconds to the next Cron fire event starting from the current instant
     */
    std::chrono::seconds next() const;

    /**
     * Calculates a number of seconds to the next Cron fire event starting from the specified date
     * 
     * @param curdate starting date for calculation
     * @return number of seconds to the next Cron fire event starting from the specified date
     */
    std::chrono::seconds next(const std::string& curdate) const;
    
};

} // namespace
}

#endif	/* STATICLIB_CRON_CRONEXPRESSION_HPP */

