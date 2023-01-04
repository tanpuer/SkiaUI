package com.temple.skiaui

import android.view.Choreographer
import android.view.MotionEvent
import android.view.Surface
import android.view.VelocityTracker

class HYSkiaEngine : Choreographer.FrameCallback {

    private var nativePtr: Long = 0L

    private var velocityTracker: VelocityTracker? = null

    fun createSurface(surface: Surface) {
        nativePtr = nativeSurfaceCreated(surface)
        Choreographer.getInstance().postFrameCallback(this)
        velocityTracker = VelocityTracker.obtain()
    }

    fun changeSurfaceSize(width: Int, height: Int) {
        nativeSurfaceChanged(nativePtr, width, height)
    }

    fun destroySurface() {
        Choreographer.getInstance().removeFrameCallback(this)
        nativeSurfaceDestroyed(nativePtr)
        nativePtr = 0L
        velocityTracker?.recycle()
        velocityTracker = null
    }

    override fun doFrame(time: Long) {
        nativeSurfaceDoFrame(nativePtr, time / 1000000)
        Choreographer.getInstance().postFrameCallback(this)
    }

    fun dispatchHYTouchEvent(event: MotionEvent): Boolean {
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