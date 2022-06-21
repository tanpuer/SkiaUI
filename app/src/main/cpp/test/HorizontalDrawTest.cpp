//
// Created by cw on 2022/5/24.
//

#include "HorizontalDrawTest.h"

HorizontalDrawTest::HorizontalDrawTest() {
    root = new FlexboxLayout();
}

HorizontalDrawTest::~HorizontalDrawTest() {

}

void HorizontalDrawTest::doDrawTest(int drawCount, SkCanvas *canvas, int width, int height) {
    root->removeAllViews();
    auto config = YGConfigNew();
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
        auto _root1 = new FlexboxLayout();
        _root1->setConfig(config);
        _root1->setFlexWrap(YGWrapWrap);
        _root1->setFlexDirection(YGFlexDirectionRow);
        _root1->setJustifyContent(YGJustifyCenter);
        _root1->setAlignItems(YGAlignCenter);
        _root1->setAlignContent(YGAlignCenter);
        _root1->setStrokeWidth(10);
        _root1->setStyle(SkPaint::kStroke_Style);
        _root1->setBackgroundColor(SK_ColorGREEN);
        {
            auto view = new View();
            view->setConfig(_root1->config);
            view->setBackgroundColor(SK_ColorRED);
            view->setStyle(SkPaint::kFill_Style);
            view->setCornerRadius(30);
            auto viewLayoutParams = LayoutParams::makeExactlyLayoutParams(200, 200);
            viewLayoutParams->setMargin({0, 0, 0, 0});
            _root1->addView(view, viewLayoutParams);

            auto textView = new TextView();
            textView->setConfig(_root1->config);
            textView->setText(SkString("Code Boy"));
            textView->setTextColor(SK_ColorBLACK);
            textView->setTextSize(60);
            textView->setBackgroundColor(SK_ColorRED);
            textView->setStyle(SkPaint::kStroke_Style);
//        textView->setAlignSelf(YGAlignCenter);
            auto tvLayoutParams = LayoutParams::makeWrapContent(true, true);
            tvLayoutParams->setMargin(50);
            _root1->addView(textView, tvLayoutParams);

            auto imageView = new ImageView();
            imageView->setConfig(_root1->config);
            imageView->setSource("/sdcard/cowboy.png");
            imageView->setCornerRadius(30);
            imageView->setStyle(SkPaint::kStroke_Style);
            imageView->setBackgroundColor(SK_ColorRED);
            imageView->setStrokeWidth(10);
            _root1->addView(imageView, LayoutParams::makeWrapContent(true, true));

            root->addView(_root1, LayoutParams::makeExactlyWidth(width));
        }
        {
            auto _root2 = new FlexboxLayout();
            _root2->setConfig(config);
            _root2->setFlexWrap(YGWrapWrap);
            _root2->setFlexDirection(YGFlexDirectionRow);
            _root2->setJustifyContent(YGJustifyCenter);
            _root2->setAlignItems(YGAlignCenter);
            _root2->setAlignContent(YGAlignCenter);
            _root2->setStrokeWidth(10);
            _root2->setStyle(SkPaint::kStroke_Style);
            _root2->setBackgroundColor(SK_ColorGREEN);
            {
                auto view = new View();
                view->setConfig(_root2->config);
                view->setBackgroundColor(SK_ColorYELLOW);
                view->setStyle(SkPaint::kFill_Style);
                view->setCornerRadius(10);
                auto viewLayoutParams = LayoutParams::makeExactlyLayoutParams(300, 200);
                viewLayoutParams->setMargin({0, 0, 0, 0});
                _root2->addView(view, viewLayoutParams);

                auto textView = new TextView();
                textView->setConfig(_root2->config);
                textView->setText(SkString("Code Boy"));
                textView->setTextColor(SK_ColorBLACK);
                textView->setTextSize(60);
                textView->setBackgroundColor(SK_ColorRED);
                textView->setStyle(SkPaint::kStroke_Style);
//        textView->setAlignSelf(YGAlignCenter);
                auto tvLayoutParams = LayoutParams::makeWrapContent(true, true);
                tvLayoutParams->setMargin(50);
                _root2->addView(textView, tvLayoutParams);

                auto imageView = new ImageView();
                imageView->setConfig(_root2->config);
                imageView->setSource("/sdcard/cowboy.png");
                imageView->setCornerRadius(30);
                imageView->setStyle(SkPaint::kStroke_Style);
                imageView->setBackgroundColor(SK_ColorRED);
                imageView->setStrokeWidth(10);
                _root2->addView(imageView, LayoutParams::makeWrapContent(true, true));
                auto root2LayoutParams = LayoutParams::makeWrapContent();
                root2LayoutParams->setMargin({0, 400, 0, 0});
                root->addView(_root2, root2LayoutParams);
            }
        }

    }

    auto rootWidthSpec = MeasureSpec::makeMeasureSpec(width, EXACTLY);
    auto rootHeightSpec = MeasureSpec::makeMeasureSpec(height, EXACTLY);
    root->measure(rootWidthSpec, rootHeightSpec);
    root->layout(0, 0, width, height);
    root->draw(canvas);

    YGConfigFree(config);
}
