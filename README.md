Cron expressions library for Staticlibs
=======================================

[![travis](https://travis-ci.org/staticlibs/staticlib_cron.svg?branch=master)](https://travis-ci.org/staticlibs/staticlib_cron)
[![appveyor](https://ci.appveyor.com/api/projects/status/github/staticlibs/staticlib_cron?svg=true)](https://ci.appveyor.com/project/staticlibs/staticlib-cron)

This project is a part of [Staticlibs](http://staticlibs.net/).

This library implements [Cron expressions](https://en.wikipedia.org/wiki/Cron), 
it is built on top of [ccronexpr](https://github.com/staticlibs/ccronexpr) library.

Link to the [API documentation](http://staticlibs.github.io/staticlib_cron/docs/html/classstaticlib_1_1cron_1_1expression.html).

Usage example
-------------

Create a `sl::cron::expression` instance using an expression and an optional date format string:

    auto cron = sl::cron::expression("0 */2 1-4 * * *", "%Y-%m-%d_%H:%M:%S");

Number of seconds to the next fire time can be calculated either from current instant, or from a specified date:

    auto millis millis_from_now = cron.next<std::chrono::milliseconds>();
    auto secs_from_spec_date = cron.next<std::chrono::seconds>("2012-07-01_09:00:00");

By default all dates calculation is done using UTC dates.
To use local dates instead configure build with `-Dstaticlib_cron_USE_LOCALTIME=ON` option.

How to build
------------

[CMake](http://cmake.org/) is required for building.

[pkg-config](http://www.freedesktop.org/wiki/Software/pkg-config/) utility is used for dependency management.
For Windows users ready-to-use binary version of `pkg-config` can be obtained from [tools_windows_pkgconfig](https://github.com/staticlibs/tools_windows_pkgconfig) repository.
See [StaticlibsPkgConfig](https://github.com/staticlibs/wiki/wiki/StaticlibsPkgConfig) for Staticlibs-specific details about `pkg-config` usage.

To build the library on Windows using Visual Studio 2013 Express run the following commands using
Visual Studio development command prompt 
(`C:\Program Files (x86)\Microsoft Visual Studio 12.0\Common7\Tools\Shortcuts\VS2013 x86 Native Tools Command Prompt`):

    git clone https://github.com/staticlibs/staticlib_config.git
    git clone https://github.com/staticlibs/staticlib_support.git
    git clone https://github.com/staticlibs/staticlib_pimpl.git
    git clone https://github.com/staticlibs/staticlib_cron.git
    git clone https://github.com/staticlibs/ccronexpr.git
    cd staticlib_cron
    mkdir build
    cd build
    cmake ..
    msbuild staticlib_cron.sln

See [StaticlibsToolchains](https://github.com/staticlibs/wiki/wiki/StaticlibsToolchains) for 
more information about the toolchain setup and cross-compilation.

License information
-------------------

This project is released under the [Apache License 2.0](http://www.apache.org/licenses/LICENSE-2.0).

Changelog
---------

**2018-02-28**

 * version 1.1.2
 * `ccronexp` submodule dropped

**2017-12-23**

 * version 1.1.1
 * vs2017 support
 * `ccronexp` update

**2017-05-03**

 * version 1.1.0
 * duration conversion support
 * minor renaming

**2016-06-17**

 * version 1.0
 * initial public version
