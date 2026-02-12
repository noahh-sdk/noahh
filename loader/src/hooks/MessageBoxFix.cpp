#include <Noahh/Modify.hpp>

#ifdef NOAHH_IS_WINDOWS

USE_NOAHH_NAMESPACE();
using noahh::core::meta::x86::Thiscall;

// for some reason RobTop uses MessageBoxW in his GLFW error handler.
// no one knows how this is possible (he passes char* to wchar_t*).
// so anyway, here's a fix for it

static auto CCEGLVIEW_CON_ADDR = reinterpret_cast<void*>(base::getCocos() + 0xc2860);

static void __cdecl fixedErrorHandler(int code, const char* description) {
    Log::get() << Severity::Critical << "GLFW Error " << code << ": " << description;
    MessageBoxA(
        nullptr,
        CCString::createWithFormat(
            "GLFWError #%d: %s\nPlease contact the "
            "Noahh Development Team for more information.",
            code, description
        )->getCString(), 
        "OpenGL Error",
        MB_ICONERROR
    );
}

static CCEGLView* CCEGLView_CCEGLView(CCEGLView* self) {
    // you will never have to make a manual hook with Noahh again, they said
    // it will be fun, they said
    reinterpret_cast<CCEGLView*(__thiscall*)(CCEGLView*)>(CCEGLVIEW_CON_ADDR)(self);
    static auto p = Mod::get()->patch(
        reinterpret_cast<void*>(noahh::base::getCocos() + 0x19feec),
        to_byte_array(&fixedErrorHandler)
    );
    return self;
}
static auto _ = Interface::get()->addHook<&CCEGLView_CCEGLView, Thiscall>("CCEGLView::CCEGLView", CCEGLVIEW_CON_ADDR);

#endif