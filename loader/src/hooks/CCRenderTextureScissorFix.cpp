#include <Noahh/Noahh.hpp>
#include <Noahh/modify/CCEGLView.hpp>

using namespace noahh::prelude;

class $modify (CCRenderTextureScissorFix, CCEGLView) {
    virtual void setScissorInPoints(float x, float y, float w, float h) {
        GLint viewport[4];
        glGetIntegerv(GL_VIEWPORT, viewport);

        float factor = noahh::utils::getDisplayFactor();
        float multWidth = (viewport[2] / getFrameSize().width) / factor;
        float multHeight = (viewport[3] / getFrameSize().height) / factor;

        x *= multWidth;
        y *= multHeight;
        w *= multWidth;
        h *= multHeight;

        CCEGLView::setScissorInPoints(x, y, w, h);
    }
};

