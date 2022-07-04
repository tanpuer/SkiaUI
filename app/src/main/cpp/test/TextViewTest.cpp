//
// Created by cw on 2022/7/2.
//

#include "TextViewTest.h"
#include "../../jniLibs/skia/include/core/SkCanvas.h"

TextViewTest::TextViewTest() = default;

TextViewTest::~TextViewTest() = default;

void TextViewTest::doDrawTest(int drawCount, SkCanvas *canvas, int width, int height) {
    if (root == nullptr) {
        ALOGD("doDrawTest %d %d", width, height)
        root = new FlexboxLayout();
        config = YGConfigNew();
        root->setConfig(config);
        root->setLayoutParams(LayoutParams::makeExactlyLayoutParams(width, height));
        root->setFlexWrap(YGWrapWrap);
        root->setFlexDirection(YGFlexDirectionColumn);
        root->setJustifyContent(YGJustifyCenter);
        root->setAlignItems(YGAlignCenter);
        root->setAlignContent(YGAlignCenter);
        root->setStrokeWidth(10);
        root->setStyle(SkPaint::kStroke_Style);
        root->setBackgroundColor(SK_ColorBLUE);

        {
            auto textView = new TextView();
            textView->setConfig(root->config);
            textView->setText(SkString("Code Boy"));
            textView->setTextColor(SK_ColorBLACK);
            textView->setTextSize(60);
            textView->setBackgroundColor(SK_ColorRED);
            textView->setStyle(SkPaint::kStroke_Style);
//        textView->setAlignSelf(YGAlignCenter);
            auto tvLayoutParams = LayoutParams::makeWrapContent(true, true);
            tvLayoutParams->setMargin(50);
            root->addView(textView, tvLayoutParams);
        }

        {
            auto textView = new TextView();
            textView->setConfig(root->config);
            textView->setText(SkString("Xiao Hai Yang"));
            textView->setTextColor(SK_ColorBLACK);
            textView->setTextSize(60);
            textView->setBackgroundColor(SK_ColorRED);
            textView->setStyle(SkPaint::kStroke_Style);
//        textView->setAlignSelf(YGAlignCenter);
            auto tvLayoutParams = LayoutParams::makeExactlyLayoutParams(300, 300);
            tvLayoutParams->setMargin(50);
            root->addView(textView, tvLayoutParams);
        }
    }

    auto rootWidthSpec = MeasureSpec::makeMeasureSpec(width, EXACTLY);
    auto rootHeightSpec = MeasureSpec::makeMeasureSpec(height, EXACTLY);
    root->measure(rootWidthSpec, rootHeightSpec);
    root->layout(0, 0, width, height);
    root->draw(canvas);
}
