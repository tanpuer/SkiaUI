//
// Created by DZSB-000848 on 1/24/22.
//

#ifndef SKIAUI_FLEXLAYOUT_H
#define SKIAUI_FLEXLAYOUT_H

#pragma mark 容器的属性 start

enum class FlexDirection {
    row, //主轴为水平方向，起点在左端
    row_reverse, //主轴为水平方向，起点在右端
    column, //主轴为垂直方向，起点在上沿
    column_reverse //主轴为垂直方向，起点在下沿
};

//项目如何换行
enum class FlexWarp {
    no_wrap, //不换行
    wrap, //换行，第一行在上方
    wrap_reverse //换行，第一行在下方
};

//项目在主轴上的对齐方式
enum class JustifyContent {
    flex_start, //左对齐
    flex_end, //右对齐
    center, //居中
    space_between, //两端对齐，项目间隔相等
    space_around //每个项目的两侧间隔相等
};

//项目在交叉轴上如何对齐
enum class AlignItems {
    flex_start, //交叉轴的起点对齐
    flex_end, //交叉轴的终点对齐
    center, //交叉轴的中点对齐
    baseline, //项目的第一行文字的基线对齐
    stretch, //如果项目未设置高度或设为auto，将撑满整个容器的高度
};

//定义了多根轴线的对齐方式，如果项目只有一根轴线，该属性不起作用
enum class AlignContent {
    flex_start, //与交叉轴的起点对齐
    flex_end, //与交叉轴的终点对齐
    center, //与交叉轴的中点对齐
    space_between, //与交叉轴两端对齐，轴线之间间隔平均分布
    space_around, //每根轴线两侧的间隔相等
    stretch, //轴线占满整个交叉轴
};

#pragma mark 容器的属性 end

#pragma mark 项目的属性 start

//order, flex-grow, flex-shrink,

//定义项目的排列顺序，数值越小，排列越靠前，默认0
struct Order {
    int value = 0;
};

//定义项目的放大比例，默认为0 = 如果存在剩余空间也不放大
struct FlexGrow {
    int value = 0;
};

//定义项目的缩小比例，默认为1，如果空间不足，该项目将缩小
struct FlexShrink {
    int value = 1;
};

//定义在分配多余的空间之前，项目占据的主轴空间。浏览器根据这个属性，计算主轴是否有多余空间。它的默认值为auto，即项目的本来大小
struct FlexBias {
    bool value = true;
};

//是flex-grow，flex-shrink，flex-bias的简写，默认是0 1 auto
struct Flex {

    FlexGrow flexGrow;
    FlexShrink flexShrink;
    FlexBias flexBias;

    void defaultAuto() {
        flexGrow.value = 1;
        flexShrink.value = 1;
        flexBias.value = true;
    }

    void defaultNone() {
        flexGrow.value = 0;
        flexShrink.value = 0;
        flexBias.value = true;
    }

};

//允许单个项目有与其他项目不一样的对齐方式，可覆盖AlignItems属性，默认auto
struct AlignSelf {
    bool defaultValue = true;
    AlignItems alignSelf;
};

#pragma mark 项目的属性 end

#endif //SKIAUI_FLEXLAYOUT_H