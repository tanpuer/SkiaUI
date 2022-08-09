package com.temple.skiaui

import android.content.Context
import android.util.AttributeSet
import android.view.*

class HYSkiaView @JvmOverloads constructor(
    context: Context, attrs: AttributeSet? = null, defStyleAttr: Int = 0
) : SurfaceView(context, attrs, defStyleAttr), SurfaceHolder.Callback, Choreographer.FrameCallback {

    private var nativePtr: Long = 0L

    private var velocityTracker: VelocityTracker? = null

    init {
        holder.addCallback(this)
    }

    override fun surfaceCreated(holder: SurfaceHolder) {
        nativePtr = nativeSurfaceCreated(holder.surface)
        Choreographer.getInstance().postFrameCallback(this)
        velocityTracker = VelocityTracker.obtain()
    }

    override fun surfaceChanged(holder: SurfaceHolder, format: Int, width: Int, height: Int) {
        nativeSurfaceChanged(nativePtr, width, height)
    }

    override fun surfaceDestroyed(holder: SurfaceHolder) {
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

    override fun dispatchTouchEvent(event: MotionEvent): Boolean {
        if (nativePtr == 0L) {
            return false
        }
        velocityTracker?.addMovement(event)
        if (event.action == MotionEvent.ACTION_UP) {
            velocityTracker?.computeCurrentVelocity(1000)
            nativeSetVelocity(
                nativePtr,
                velocityTracker?.xVelocity ?: 0f,
                velocityTracker?.yVelocity ?: 0f
            )
        }
        return nativeTouchEvent(nativePtr, event.action, event.x, event.y)
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