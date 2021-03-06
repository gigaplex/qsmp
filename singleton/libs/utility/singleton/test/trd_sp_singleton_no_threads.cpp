/*=============================================================================
    Copyright (c) 2007 Tobias Schwinger
  
    Use modification and distribution are subject to the Boost Software 
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt).
==============================================================================*/

// Pretend we have no threads and run the simple singleton test

#include <boost/config.hpp>
#undef BOOST_HAS_THREADS

#include <boost/utility/thread_specific_singleton.hpp>
#define SINGLETON_TYPE thread_specific_singleton
#include "singleton.cpp"

