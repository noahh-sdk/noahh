/**
 * Adapted from https://gist.github.com/altalk23/29b97969e9f0624f783b673f6c1cd279
 */

#include <Noahh/utils/addresser.hpp>
#include <cstdlib>
#include <stddef.h>
#include <Noahh/DefaultInclude.hpp>

#define NOAHH_ADDRESSER_NEST1(macro, begin)           \
macro(NOAHH_CONCAT(begin, 0)),                        \
macro(NOAHH_CONCAT(begin, 1)),                        \
macro(NOAHH_CONCAT(begin, 2)),                        \
macro(NOAHH_CONCAT(begin, 3)),                        \
macro(NOAHH_CONCAT(begin, 4)),                        \
macro(NOAHH_CONCAT(begin, 5)),                        \
macro(NOAHH_CONCAT(begin, 6)),                        \
macro(NOAHH_CONCAT(begin, 7)),                        \
macro(NOAHH_CONCAT(begin, 8)),                        \
macro(NOAHH_CONCAT(begin, 9)),                        \
macro(NOAHH_CONCAT(begin, a)),                        \
macro(NOAHH_CONCAT(begin, b)),                        \
macro(NOAHH_CONCAT(begin, c)),                        \
macro(NOAHH_CONCAT(begin, d)),                        \
macro(NOAHH_CONCAT(begin, e)),                        \
macro(NOAHH_CONCAT(begin, f))  

#define NOAHH_ADDRESSER_NEST2(macro, begin)           \
NOAHH_ADDRESSER_NEST1(macro, NOAHH_CONCAT(begin, 0)), \
NOAHH_ADDRESSER_NEST1(macro, NOAHH_CONCAT(begin, 1)), \
NOAHH_ADDRESSER_NEST1(macro, NOAHH_CONCAT(begin, 2)), \
NOAHH_ADDRESSER_NEST1(macro, NOAHH_CONCAT(begin, 3)), \
NOAHH_ADDRESSER_NEST1(macro, NOAHH_CONCAT(begin, 4)), \
NOAHH_ADDRESSER_NEST1(macro, NOAHH_CONCAT(begin, 5)), \
NOAHH_ADDRESSER_NEST1(macro, NOAHH_CONCAT(begin, 6)), \
NOAHH_ADDRESSER_NEST1(macro, NOAHH_CONCAT(begin, 7)), \
NOAHH_ADDRESSER_NEST1(macro, NOAHH_CONCAT(begin, 8)), \
NOAHH_ADDRESSER_NEST1(macro, NOAHH_CONCAT(begin, 9)), \
NOAHH_ADDRESSER_NEST1(macro, NOAHH_CONCAT(begin, a)), \
NOAHH_ADDRESSER_NEST1(macro, NOAHH_CONCAT(begin, b)), \
NOAHH_ADDRESSER_NEST1(macro, NOAHH_CONCAT(begin, c)), \
NOAHH_ADDRESSER_NEST1(macro, NOAHH_CONCAT(begin, d)), \
NOAHH_ADDRESSER_NEST1(macro, NOAHH_CONCAT(begin, e)), \
NOAHH_ADDRESSER_NEST1(macro, NOAHH_CONCAT(begin, f))  


#define NOAHH_ADDRESSER_THUNK0_DEFINE(hex) (intptr_t)&f<hex * sizeof(intptr_t)>
#define NOAHH_ADDRESSER_TABLE_DEFINE(hex) (intptr_t)&ThunkTable::table

#define NOAHH_ADDRESSER_THUNK0_SET() NOAHH_ADDRESSER_NEST2(NOAHH_ADDRESSER_THUNK0_DEFINE, 0x)
#define NOAHH_ADDRESSER_TABLE_SET() NOAHH_ADDRESSER_NEST2(NOAHH_ADDRESSER_TABLE_DEFINE, 0x)

using namespace noahh::addresser;

namespace {
	template<ptrdiff_t index>
	NOAHH_HIDDEN ptrdiff_t f() {
		return index;
	}

	using thunk0_table_t = intptr_t[0x100];
	using table_table_t = intptr_t[0x100];

	struct NOAHH_HIDDEN ThunkTable {
		static inline thunk0_table_t table = {
			NOAHH_ADDRESSER_THUNK0_SET()
		};
	};

	class NOAHH_HIDDEN TableTable {
		friend class noahh::addresser::Addresser;

		static inline table_table_t table = {
			NOAHH_ADDRESSER_TABLE_SET()
		};
	};
}

Addresser::MultipleInheritance* Addresser::instance() {
	return reinterpret_cast<Addresser::MultipleInheritance*>(&TableTable::table);
}
