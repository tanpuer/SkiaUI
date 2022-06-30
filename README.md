# SkiaUI

使用Skia和Yoga，基于SurfaceView实现简单的支持flexbox布局的ui样式demo
步骤：
1. 引入Skia和Yoga。
2. 配置好gl环境，使用Skia硬件加速。
3. 绘制模仿安卓Measure/Layout/Draw三板斧流程，只支持Flexbox布局。
4. 事件分发大体模仿安卓dispatchTouchEvent/interceptTouchEvent/onTouchEvent等，做了简化处理。
5. 动画支持scale/rotate/translate，在layout阶段更新SKMatrix，从而更新绘制的矩形。
6. 目前只支持View/TextView/ImageView，还在优化中。。。
7. todo 脏区渲染/scroll/
![image](https://github.com/tanpuer/SkiaUI/blob/master/app/skia-ui.png)
