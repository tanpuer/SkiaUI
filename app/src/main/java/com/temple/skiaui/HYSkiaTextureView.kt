package com.temple.skiaui

import android.content.Context
import android.graphics.SurfaceTexture
import android.util.AttributeSet
import android.view.*
import android.view.Choreographer.FrameCallback

/**
 * 使用SurfaceView，渲染延迟感觉比TextureView要明显，比如跟手这个直观的感觉，TextureView要比SurfaceView好。
 */
class HYSkiaTextureView @JvmOverloads constructor(
    context: Context, attrs: AttributeSet? = null
) : TextureView(context, attrs), TextureView.SurfaceTextureListener, FrameCallback {

    private var nativePtr: Long = 0L

    private var velocityTracker: VelocityTracker? = null

    init {
        surfaceTextureListener = this
    }

    override fun onSurfaceTextureAvailable(surface: SurfaceTexture, width: Int, height: Int) {
        nativePtr = nativeSurfaceCreated(Surface(surface))
        nativeSurfaceChanged(nativePtr, width, height)
        Choreographer.getInstance().postFrameCallback(this)
        velocityTracker = VelocityTracker.obtain()
    }

    override fun onSurfaceTextureDestroyed(surface: SurfaceTexture): Boolean {
        Choreographer.getInstance().removeFrameCallback(this)
        nativeSurfaceDestroyed(nativePtr)
        nativePtr = 0L
        velocityTracker?.recycle()
        velocityTracker = null
        return true
    }

    override fun onSurfaceTextureSizeChanged(surface: SurfaceTexture, width: Int, height: Int) {

    }

    override fun onSurfaceTextureUpdated(surface: SurfaceTexture) {

    }

    override fun doFrame(frameTimeNanos: Long) {
        nativeSurfaceDoFrame(nativePtr, frameTimeNanos / 1000000)
        Choreographer.getInstance().postFrameCallback(this)
    }

    override fun dispatchTouchEvent(event: MotionEvent): Boolean {
        if (nativePtr == 0L) {
            return false
        }
        nativeTouchEvent(nativePtr, event.action, event.x, event.y)
        velocityTracker?.addMovement(event)
        if (event.action == MotionEvent.ACTION_UP) {
            velocityTracker?.computeCurrentVelocity(1000)
            nativeSetVelocity(
                nativePtr,
                velocityTracker?.xVelocity ?: 0f,
                velocityTracker?.yVelocity ?: 0f
            )
        }
        return true
    }

    private external fun nativeSurfaceCreated(surface: Surface): Long
    private external fun nativeSurfaceChanged(nativePtr: Long, width: Int, height: Int)
    private external fun nativeSurfaceDestroyed(nativePtr: Long)
    private external fun nativeSurfaceDoFrame(nativePtr: Long, time: Long)
    private external fun nativeTouchEvent(nativePtr: Long, action: Int, x: Float, y: Float): Boolean
    private external fun nativeSetVelocity(nativePtr: Long, xVelocity: Float, yVelocity: Float)

    companion object {
        init {
            System.loadLibrary("native-lib")
        }
    }

}