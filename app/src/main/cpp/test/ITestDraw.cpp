//
// Created by cw on 2022/5/24.
//

#include "ITestDraw.h"
#include "FlexboxLayout.h"
#include "TextView.h"
#include "ImageView.h"

ITestDraw::ITestDraw() {

}

ITestDraw::~ITestDraw() {

}

void ITestDraw::doDrawTest(int drawCount, SkCanvas *canvas, int width, int height) {
    FlexboxLayout _root;
    _root.setLayoutParams(LayoutParams::makeExactlyWidth(width));
    _root.setFlexWrap(YGWrapWrap);
    _root.setFlexDirection(YGFlexDirectionRow);
    _root.setJustifyContent(YGJustifyCenter);
    _root.setAlignItems(YGAlignCenter);

    {
        auto view = new View();
        view->setBackgroundColor(SK_ColorRED);
        view->setStyle(SkPaint::kFill_Style);
        view->setCornerRadius(30);
        auto viewLayoutParams = LayoutParams::makeExactlyLayoutParams(300, 200);
        viewLayoutParams->setMargin({0, drawCount, 0, 0});
        _root.addView(view, viewLayoutParams);

        auto textView = new TextView();
        textView->setText(SkString("Hello World"));
        textView->setTextColor(SK_ColorBLACK);
        textView->setTextSize(60);
        textView->setBackgroundColor(SK_ColorRED);
        textView->setStyle(SkPaint::kStroke_Style);
//    textView->setAlignSelf(YGAlignFlexEnd);
        auto tvLayoutParams = LayoutParams::makeWrapContent(true, true);
        tvLayoutParams->setMargin(50);
        _root.addView(textView, tvLayoutParams);

        auto imageView = new ImageView();
        imageView->setSource("/sdcard/cowboy.png");
        imageView->setCornerRadius(30);
        imageView->setStyle(SkPaint::kStroke_Style);
        imageView->setBackgroundColor(SK_ColorRED);
        imageView->setStrokeWidth(10);
        _root.addView(imageView, LayoutParams::makeWrapContent(true, true));
    }

    auto rootWidthSpec = MeasureSpec::makeMeasureSpec(width, EXACTLY);
    auto rootHeightSpec = MeasureSpec::makeMeasureSpec(height, EXACTLY);
    _root.measure(rootWidthSpec, rootHeightSpec);
    _root.layout(0, 0, width, height);
    _root.draw(canvas);
}
