#pragma once

#include <Noahh/platform/cplatform.h>
#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

void NOAHH_C_DLL noahh_mod_log(void* mod, const char* message);

bool NOAHH_C_DLL noahh_mod_add_hook(void* mod, void* address, void* detour);

bool NOAHH_C_DLL noahh_get_last_error(char* buffer, size_t bufferSize);

#ifdef __cplusplus
}
#endif