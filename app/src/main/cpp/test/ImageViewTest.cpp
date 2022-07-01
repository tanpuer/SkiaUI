//
// Created by cw on 2022/7/1.
//

#include "ImageViewTest.h"

ImageViewTest::ImageViewTest() = default;

ImageViewTest::~ImageViewTest() = default;

void ImageViewTest::doDrawTest(int drawCount, SkCanvas *canvas, int width, int height) {
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
        root->setStrokeWidth(2);
        root->setStyle(SkPaint::kStroke_Style);
        root->setBackgroundColor(SK_ColorBLUE);

        {
            auto imageView = new ImageView();
            imageView->setConfig(root->config);
            imageView->setSource("/sdcard/cowboy.png");
            imageView->setCornerRadius(30);
            imageView->setScaleType(ImageView::ScaleType::FitCenter);
            imageView->setStyle(SkPaint::kStroke_Style);
            imageView->setBackgroundColor(SK_ColorRED);
            imageView->setStrokeWidth(2);
            auto lp = LayoutParams::makeExactlyLayoutParams(300, 200);
            root->addView(imageView, lp);
        }

        {
            auto imageView = new ImageView();
            imageView->setConfig(root->config);
            imageView->setSource("/sdcard/cowboy.png");
            imageView->setCornerRadius(30);
            imageView->setScaleType(ImageView::ScaleType::CenterCrop);
            imageView->setStyle(SkPaint::kStroke_Style);
            imageView->setBackgroundColor(SK_ColorRED);
            imageView->setStrokeWidth(2);
            auto lp = LayoutParams::makeExactlyLayoutParams(300, 200);
            lp->setMargin({0, 100, 0, 0});
            root->addView(imageView, lp);
        }

        {
            auto imageView = new ImageView();
            imageView->setConfig(root->config);
            imageView->setSource("/sdcard/cowboy.png");
            imageView->setCornerRadius(30);
            imageView->setScaleType(ImageView::ScaleType::FitCenter);
            imageView->setStyle(SkPaint::kStroke_Style);
            imageView->setBackgroundColor(SK_ColorRED);
            imageView->setStrokeWidth(2);
            auto lp = LayoutParams::makeExactlyLayoutParams(200, 300);
            lp->setMargin({0, 100, 0, 0});
            root->addView(imageView, lp);
        }

        {
            auto imageView = new ImageView();
            imageView->setConfig(root->config);
            imageView->setSource("/sdcard/cowboy.png");
            imageView->setCornerRadius(30);
            imageView->setScaleType(ImageView::ScaleType::CenterCrop);
            imageView->setStyle(SkPaint::kStroke_Style);
            imageView->setBackgroundColor(SK_ColorRED);
            imageView->setStrokeWidth(2);
            auto lp = LayoutParams::makeExactlyLayoutParams(200, 300);
            lp->setMargin({0, 100, 0, 0});
            root->addView(imageView, lp);
        }

        {
            auto imageView = new ImageView();
            imageView->setConfig(root->config);
            imageView->setSource("/sdcard/cowboy.png");
            imageView->setCornerRadius(30);
            imageView->setStyle(SkPaint::kStroke_Style);
            imageView->setBackgroundColor(SK_ColorRED);
            imageView->setStrokeWidth(2);
            auto lp = LayoutParams::makeExactlyLayoutParams(300, 200);
            lp->setMargin({0, 100, 0, 0});
            root->addView(imageView, lp);
        }

        {
            auto imageView = new ImageView();
            imageView->setConfig(root->config);
            imageView->setSource("/sdcard/cowboy.png");
            imageView->setCornerRadius(100);
            imageView->setScaleType(ImageView::ScaleType::FitCenter);
            imageView->setStyle(SkPaint::kStroke_Style);
            imageView->setBackgroundColor(SK_ColorRED);
            imageView->setStrokeWidth(2);
            auto lp = LayoutParams::makeExactlyLayoutParams(200, 200);
            lp->setMargin({0, 100, 0, 0});
            root->addView(imageView, lp);
        }
    }
    auto rootWidthSpec = MeasureSpec::makeMeasureSpec(width, EXACTLY);
    auto rootHeightSpec = MeasureSpec::makeMeasureSpec(height, EXACTLY);
    root->measure(rootWidthSpec, rootHeightSpec);
    root->layout(0, 0, width, height);
    root->draw(canvas);
}


