// Copyright (c) 2013-2015 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVMS_GLOBAL_TYPEDEFS
#define SSVMS_GLOBAL_TYPEDEFS

#include <functional>

namespace ssvms
{
    using Action = std::function<void()>;
    using Predicate = std::function<bool()>;
}

#endif
