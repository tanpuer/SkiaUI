package com.temple.skiaui

/**
 * 参考Flutter的配置
 */
enum class RenderMode {

    /**
     * {@code RenderMode}, which paints a Flutter UI to a {@link android.view.SurfaceView}. This mode
     * has the best performance, but a Flutter UI in this mode cannot be positioned between 2 other
     * Android {@code View}s in the z-index, nor can it be animated/transformed. Unless the special
     * capabilities of a {@link android.graphics.SurfaceTexture} are required, developers should
     * strongly prefer this render mode.
     */
    Surface,

    /**
     * {@code RenderMode}, which paints a Flutter UI to a {@link android.graphics.SurfaceTexture}.
     * This mode is not as performant as {@link #surface}, but a Flutter UI in this mode can be
     * animated and transformed, as well as positioned in the z-index between 2+ other Android {@code
     * Views}. Unless the special capabilities of a {@link android.graphics.SurfaceTexture} are
     * required, developers should strongly prefer the {@link #surface} render mode.
     */
    Texture

}