//
// Created by ByteDance on 2022/7/26.
//

#include <ScrollView.h>
#include "ScrollViewTest.h"

ScrollViewTest::ScrollViewTest() = default;

ScrollViewTest::~ScrollViewTest() = default;

void ScrollViewTest::doDrawTest(int drawCount, SkCanvas *canvas, int width, int height) {
    if (root == nullptr) {
        ALOGD("doDrawTest %d %d", width, height)
        root = new ScrollView();
        config = YGConfigNew();
        root->setConfig(config);
        root->setLayoutParams(LayoutParams::makeExactlyLayoutParams(width, height));
        root->setFlexWrap(YGWrapNoWrap);
        root->setFlexDirection(YGFlexDirectionColumn);
        root->setJustifyContent(YGJustifyFlexStart);
        root->setAlignItems(YGAlignCenter);
        root->setAlignContent(YGAlignCenter);
        root->setStrokeWidth(10);
        root->setStyle(SkPaint::kStroke_Style);
        root->setBackgroundColor(SK_ColorBLUE);

        for (int i = 0; i < 10; ++i) {
            {
                auto textView = new TextView();
                textView->setConfig(root->config);
                textView->setText(SkString("horizontal test"));
                textView->setTextColor(SK_ColorBLACK);
                textView->setTextSize(60);
                textView->setBackgroundColor(SK_ColorRED);
                textView->setStyle(SkPaint::kStroke_Style);
                auto tvLayoutParams = LayoutParams::makeWrapContent();
                tvLayoutParams->setMargin(50);
                root->addView(textView, tvLayoutParams);
            }

            {
                auto textView = new TextView();
                textView->setConfig(root->config);
                textView->setText(SkString("abcdefghijklmnopqrstuvw"));
                textView->setTextColor(SK_ColorGREEN);
                textView->setTextSize(100);
                textView->setBackgroundColor(SK_ColorRED);
                textView->setStyle(SkPaint::kStroke_Style);
                auto tvLayoutParams = LayoutParams::makeWrapContent();
                tvLayoutParams->setMargin(50);
                root->addView(textView, tvLayoutParams);
            }

            {
                auto textView = new TextView();
                textView->setConfig(root->config);
                textView->setTextColor(SK_ColorGREEN);
                textView->setTextSize(60);
                textView->setBackgroundColor(SK_ColorRED);
                textView->setStyle(SkPaint::kStroke_Style);
                textView->pushText(TextView::StringBuilder(SkString("这是"), SK_ColorCYAN,
                                                           SkFontStyle(SkFontStyle::kThin_Weight,
                                                                       SkFontStyle::kNormal_Width,
                                                                       SkFontStyle::kUpright_Slant),
                                                           40));
                textView->pushText(TextView::StringBuilder(SkString("StringBuilder"), SK_ColorGREEN,
                                                           SkFontStyle(SkFontStyle::kThin_Weight,
                                                                       SkFontStyle::kNormal_Width,
                                                                       SkFontStyle::kUpright_Slant),
                                                           100));
                textView->pushText(TextView::StringBuilder(SkString("测试"), SK_ColorYELLOW,
                                                           SkFontStyle(SkFontStyle::kThin_Weight,
                                                                       SkFontStyle::kNormal_Width,
                                                                       SkFontStyle::kUpright_Slant),
                                                           40));
                textView->pushText(TextView::StringBuilder(SkString("demo"), SK_ColorRED,
                                                           SkFontStyle(SkFontStyle::kThin_Weight,
                                                                       SkFontStyle::kNormal_Width,
                                                                       SkFontStyle::kUpright_Slant),
                                                           100));
                auto tvLayoutParams = LayoutParams::makeWrapContent();
                tvLayoutParams->setMargin(50);
                root->addView(textView, tvLayoutParams);
            }
        }

    }

    auto rootWidthSpec = MeasureSpec::makeMeasureSpec(width, EXACTLY);
    auto rootHeightSpec = MeasureSpec::makeMeasureSpec(height, EXACTLY);
    root->measure(rootWidthSpec, rootHeightSpec);
    root->layout(0, 0, width, height);
    root->draw(canvas);
}