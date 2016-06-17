/* 
 * File:   CronException.hpp
 * Author: alex
 *
 * Created on June 17, 2016, 11:25 AM
 */

#ifndef STATICLIB_CRON_CRONEXCEPTION_HPP
#define	STATICLIB_CRON_CRONEXCEPTION_HPP

#include "staticlib/config/BaseException.hpp"

namespace staticlib {
namespace cron {

/**
 * Module specific exception
 */
class CronException : public staticlib::config::BaseException {
public:
    /**
     * Default constructor
     */
    CronException() = default;

    /**
     * Constructor with message
     * 
     * @param msg error message
     */
    CronException(const std::string& msg) :
    staticlib::config::BaseException(msg) { }

};

} //namespace
}

#endif	/* STATICLIB_CRON_CRONEXCEPTION_HPP */

