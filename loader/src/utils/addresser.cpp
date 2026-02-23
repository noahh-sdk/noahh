/**
 * Adapted from https://gist.github.com/altalk23/29b97969e9f0624f783b673f6c1cd279
 */

#include <Noahh/DefaultInclude.hpp>
#include <Noahh/utils/addresser.hpp>
#include <cstdlib>
#include <stddef.h>

#define NOAHH_ADDRESSER_NEST1(macro, begin)                                                      \
    macro(NOAHH_CONCAT(begin, 0)), macro(NOAHH_CONCAT(begin, 1)), macro(NOAHH_CONCAT(begin, 2)), \
        macro(NOAHH_CONCAT(begin, 3)), macro(NOAHH_CONCAT(begin, 4)),                            \
        macro(NOAHH_CONCAT(begin, 5)), macro(NOAHH_CONCAT(begin, 6)),                            \
        macro(NOAHH_CONCAT(begin, 7)), macro(NOAHH_CONCAT(begin, 8)),                            \
        macro(NOAHH_CONCAT(begin, 9)), macro(NOAHH_CONCAT(begin, a)),                            \
        macro(NOAHH_CONCAT(begin, b)), macro(NOAHH_CONCAT(begin, c)),                            \
        macro(NOAHH_CONCAT(begin, d)), macro(NOAHH_CONCAT(begin, e)), macro(NOAHH_CONCAT(begin, f))

#define NOAHH_ADDRESSER_NEST2(macro, begin)                   \
    NOAHH_ADDRESSER_NEST1(macro, NOAHH_CONCAT(begin, 0)),     \
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

#define NOAHH_ADDRESSER_NEST3(macro, begin)                   \
    NOAHH_ADDRESSER_NEST2(macro, NOAHH_CONCAT(begin, 0)),     \
        NOAHH_ADDRESSER_NEST2(macro, NOAHH_CONCAT(begin, 1)), \
        NOAHH_ADDRESSER_NEST2(macro, NOAHH_CONCAT(begin, 2)), \
        NOAHH_ADDRESSER_NEST2(macro, NOAHH_CONCAT(begin, 3)), \
        NOAHH_ADDRESSER_NEST2(macro, NOAHH_CONCAT(begin, 4)), \
        NOAHH_ADDRESSER_NEST2(macro, NOAHH_CONCAT(begin, 5)), \
        NOAHH_ADDRESSER_NEST2(macro, NOAHH_CONCAT(begin, 6)), \
        NOAHH_ADDRESSER_NEST2(macro, NOAHH_CONCAT(begin, 7)), \
        NOAHH_ADDRESSER_NEST2(macro, NOAHH_CONCAT(begin, 8)), \
        NOAHH_ADDRESSER_NEST2(macro, NOAHH_CONCAT(begin, 9)), \
        NOAHH_ADDRESSER_NEST2(macro, NOAHH_CONCAT(begin, a)), \
        NOAHH_ADDRESSER_NEST2(macro, NOAHH_CONCAT(begin, b)), \
        NOAHH_ADDRESSER_NEST2(macro, NOAHH_CONCAT(begin, c)), \
        NOAHH_ADDRESSER_NEST2(macro, NOAHH_CONCAT(begin, d)), \
        NOAHH_ADDRESSER_NEST2(macro, NOAHH_CONCAT(begin, e)), \
        NOAHH_ADDRESSER_NEST2(macro, NOAHH_CONCAT(begin, f))

#define NOAHH_ADDRESSER_THUNK0_DEFINE(hex) (intptr_t) & f<hex * sizeof(intptr_t)>
#define NOAHH_ADDRESSER_TABLE_DEFINE(hex) (intptr_t) & ThunkTable::table

#define NOAHH_ADDRESSER_THUNK0_SET() NOAHH_ADDRESSER_NEST3(NOAHH_ADDRESSER_THUNK0_DEFINE, 0x)
#define NOAHH_ADDRESSER_TABLE_SET() NOAHH_ADDRESSER_NEST3(NOAHH_ADDRESSER_TABLE_DEFINE, 0x)

using namespace noahh::addresser;

namespace {
    template <ptrdiff_t index>
    NOAHH_HIDDEN ptrdiff_t f() {
        return index;
    }

    using thunk0_table_t = intptr_t[0x1000];
    using table_table_t = intptr_t[0x1000];

    struct NOAHH_HIDDEN ThunkTable {
        static inline thunk0_table_t table = {NOAHH_ADDRESSER_THUNK0_SET()};
    };

    class NOAHH_HIDDEN TableTable {
        friend class noahh::addresser::Addresser;

        static inline table_table_t table = {NOAHH_ADDRESSER_TABLE_SET()};
    };
}

Addresser::MultipleInheritance* Addresser::instance() {
    return reinterpret_cast<Addresser::MultipleInheritance*>(&TableTable::table);
}

#ifdef NOAHH_IS_WINDOWS
#include <delayimp.h>
extern "C" FARPROC WINAPI __delayLoadHelper2(PCImgDelayDescr pidd, FARPROC* ppfnIATEntry); // NOLINT(*-reserved-identifier)

FARPROC WINAPI delayLoadHook(unsigned dliNotify, PDelayLoadInfo pdli) {
    switch (dliNotify) {
        case dliFailLoadLib:
        case dliFailGetProc:
            // incase the delayload helper fails at all (missing symbol, or library entirely),
            // return -1, so we can more easily handle it below
            return (FARPROC)(-1);
        default:
            return NULL;
    }
}

extern "C" const PfnDliHook __pfnDliFailureHook2 = delayLoadHook;

PVOID NoahhFunctionTableAccess64(HANDLE hProcess, DWORD64 AddrBase);
#endif

intptr_t Addresser::followThunkFunction(intptr_t address) {
#ifdef NOAHH_IS_WINDOWS32
    // if theres a jmp at the start
    if (address && *reinterpret_cast<uint8_t*>(address) == 0xE9) {
        auto relative = *reinterpret_cast<uint32_t*>(address + 1);
        auto newAddress = address + relative + 5;
        // and if that jmp leads to a jmp dword ptr, only then follow it,
        // because otherwise its just a hook.
        // For some reason this [jmp -> jmp dword ptr] chain happens with a few cocos functions,
        // but not all. For example: cocos2d::ZipUtils::decompressString2
        if (*reinterpret_cast<uint8_t*>(newAddress) == 0xFF && *reinterpret_cast<uint8_t*>(newAddress + 1) == 0x25) {
            address = newAddress;
        }
    }

    // check if first instruction is a jmp dword ptr [....], i.e. if the func is a thunk
    if (address && *reinterpret_cast<uint8_t*>(address) == 0xFF && *reinterpret_cast<uint8_t*>(address + 1) == 0x25) {
        // read where the jmp reads from
        address = *reinterpret_cast<uint32_t*>(address + 2);
        // that then contains the actual address of the func
        address = *reinterpret_cast<uintptr_t*>(address);
    }

    // if it starts with mov eax,..., it's a delay loaded func
    if (address && *reinterpret_cast<uint8_t*>(address) == 0xB8) {
        // follow the jmp to the tailMerge func and grab the ImgDelayDescr pointer from there
        // do it this way instead of grabbing it from the NT header ourselves because
        // we don't know the dll name
        auto iddAddrRel = *reinterpret_cast<uint32_t*>(address + 6);
        auto iddAddr = address + 5 + iddAddrRel + 5;
        iddAddr = *reinterpret_cast<uintptr_t*>(iddAddr + 4);
        auto idd = reinterpret_cast<PCImgDelayDescr>(iddAddr);

        // read where the mov reads from, this is a ptr to the import
        address = *reinterpret_cast<uint32_t*>(address + 1);
        auto imp = reinterpret_cast<FARPROC*>(address);

        // get the address of the function, loading the library if needed
        address = reinterpret_cast<intptr_t>(__delayLoadHelper2(idd, imp));

        // if the helper failed, it will return -1, so we can handle it here
        if (address == -1) {
            address = 0;
        }
    }
#endif
#ifdef NOAHH_IS_WINDOWS64
    static constexpr auto checkByteSequence = [](uintptr_t address, const std::initializer_list<uint8_t>& bytes) {
        for (auto byte : bytes) {
            if (*reinterpret_cast<uint8_t*>(address++) != byte) {
                return false;
            }
        }
        return true;
    };

    // check if first instruction is a jmp qword ptr [rip + ...], i.e. if the func is a thunk
    // FF 25 xxxxxxxx
    if (address && checkByteSequence(address, {0xFF, 0x25})) {
        const auto offset = *reinterpret_cast<int32_t*>(address + 2);
        // rip is at address + 6 (size of the instruction)
        auto checkAddress = *reinterpret_cast<uintptr_t*>(address + 6 + offset);

        // only follow the thunk if it's not a hook handler
        if (NoahhFunctionTableAccess64(GetCurrentProcess(), static_cast<DWORD64>(checkAddress)) == nullptr) {
            address = checkAddress;
        }
    }

    // if it starts with lea eax,..., it's a delay loaded func
    // 48 8D 05 xxxxxxxx
    if (address && checkByteSequence(address, {0x48, 0x8d, 0x05})) {
        // follow the jmp to the tailMerge func and grab the ImgDelayDescr pointer from there
        // do it this way instead of grabbing it from the NT header ourselves because
        // we don't know the dll name
        auto leaAddress = address + 7 + *reinterpret_cast<int32_t*>(address + 3);

        auto jmpOffset = *reinterpret_cast<int32_t*>(address + 7 + 1);
        auto tailMergeAddr = address + 7 + jmpOffset + 5;
        // inside of the tail merge, try to find the lea rcx, [rip + ...]
        for (uintptr_t leaOffset = 10; leaOffset < 100; ++leaOffset) {
            auto leaAddr = tailMergeAddr + leaOffset;
            if (checkByteSequence(leaAddr, {0x48, 0x8d, 0x0d})) {
                auto offset = *reinterpret_cast<int32_t*>(leaAddr + 3);
                auto did = reinterpret_cast<PCImgDelayDescr>(leaAddr + 7 + offset);
                address = reinterpret_cast<intptr_t>(__delayLoadHelper2(did, reinterpret_cast<FARPROC*>(leaAddress)));

                if (address == -1) {
                    address = 0;
                }
                break;
            }
        }
    }

    // if theres a jmp at the start
    if (address && *reinterpret_cast<uint8_t*>(address) == 0xE9) {
        auto relative = *reinterpret_cast<uint32_t*>(address + 1);
        auto newAddress = address + relative + 5;
        address = newAddress;
    }
#endif
    return address;
}

