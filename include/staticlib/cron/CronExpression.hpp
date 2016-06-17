/* 
 * File:   CronExpression.hpp
 * Author: alex
 *
 * Created on June 17, 2016, 11:25 AM
 */

#ifndef STATICLIB_CRON_CRONEXPRESSION_HPP
#define	STATICLIB_CRON_CRONEXPRESSION_HPP

#include <chrono>
#include <string>

#include "staticlib/pimpl.hpp"

#include "staticlib/cron/CronException.hpp"

namespace staticlib {
namespace cron {

class CronExpression : public staticlib::pimpl::PimplObject {
protected:
    /**
     * Implementation class
     */
    class Impl;    

public:
    /**
     * PIMPL-specific constructor
     * 
     * @param pimpl impl object
     */
    PIMPL_CONSTRUCTOR(CronExpression)    
            
    CronExpression(std::string expression, 
            std::string date_format = "%Y-%m-%d_%H:%M:%S");
    
    std::chrono::seconds next() const;
    
    std::chrono::seconds next(const std::string& curdate) const;
    
};

} // namespace
}

#endif	/* STATICLIB_CRON_CRONEXPRESSION_HPP */

