#pragma once
#include "Types.hpp"
#include <Noahh/utils/addresser.hpp>

namespace noahh::modifier {
	struct addresses {
		#include <codegenned/GeneratedAddress.hpp>
	};
}