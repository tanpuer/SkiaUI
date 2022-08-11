# SkiaUI

切换到develop分支

使用Skia和Yoga，基于SurfaceView实现简单的支持flexbox布局的ui样式demo
步骤：
1. 引入Skia和Yoga。
   skia编译参考官方文档 https://skia.org/docs/user/build/。 
   Yoga直接源码拿过来用了。
2. 配置好gl环境，使用Skia硬件加速。
3. 绘制模仿安卓Measure/Layout/Draw三板斧流程，只支持Flexbox布局。
4. 事件分发大体模仿安卓dispatchTouchEvent/interceptTouchEvent/onTouchEvent等，做了简化处理。
5. 动画支持scale/rotate/translate，在layout阶段更新SKMatrix，从而更新绘制的矩形。
6. 目前只支持View/TextView/ImageView，todo View凑活；ImageView支持了scaleType，圆角；TextView接入SkParagraph。后续想用这套试试富文本编辑器;
   ProgressBar支持圆形和直线形，可拖拽修改进度。
7. scrollView实现，滑动，fling，目前滑动效果过于僵硬，todo 优化滑动效果。
8. todo 脏区渲染
9. todo ListView的实现
10. todo 接入v8


![image](https://github.com/tanpuer/SkiaUI/blob/develop/app/example1.jpeg)
![image](https://github.com/tanpuer/SkiaUI/blob/develop/app/example2.jpeg)
![image](https://github.com/tanpuer/SkiaUI/blob/develop/app/example1.gif)
![image](https://github.com/tanpuer/SkiaUI/blob/develop/app/example2.gif)
