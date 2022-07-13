//
// Created by DZSB-000848 on 1/26/22.
//

#include "TextView.h"

#include <utility>
#include <base/native_log.h>
#include "core/SkFont.h"

TextView::TextView() : View() {
    textPaint = new SkPaint();
    textPaint->setAntiAlias(true);
    textRect = SkRect::MakeEmpty();
    ellipsisStr = SkString('...');
    defaultStyle = std::make_unique<TextStyle>();
    fontCollection = sk_make_sp<FontCollection>();
    fontCollection->setDefaultFontManager(SkFontMgr::RefDefault());
}

TextView::~TextView() {
    delete textPaint;
//    ALOGD("~View TextView")
}

const char *TextView::name() {
    return "TextView";
}

void TextView::setText(SkString text) {
    this->text = std::move(text);
    isDirty = true;
}

SkString TextView::getText() {
    return text;
}

void TextView::setTextColor(SkColor color) {
    SkASSERT(textPaint);
    textPaint->setColor(color);
    defaultStyle->setColor(color);
    isDirty = true;
}

void TextView::setAlpha(float alpha) {
    View::setAlpha(alpha);
    textPaint->setAlphaf(alpha);
    isDirty = true;
}

void TextView::measure(int widthMeasureSpec, int heightMeasureSpec) {
    if (text.isEmpty()) {
        setMeasuredDimension(0, 0);
        return;
    }
//    auto length = font.measureText(static_cast<const void *>(text.c_str()), strlen(text.c_str()),
//                                   SkTextEncoding::kUTF8,
//                                   &textRect, textPaint);
//    if (layoutParams->_widthMode == EXACTLY && layoutParams->_heightMode == EXACTLY) {
//        auto ellipsisStrLength = font.measureText(static_cast<const void *>(ellipsisStr.c_str()), 3,
//                                                  SkTextEncoding::kUTF8,
//                                                  nullptr, textPaint);
//        if (layoutParams->_width < length) {
//            textVector.clear();
//            //todo LineBreak
//        }
//        setMeasuredDimension(layoutParams->_width, layoutParams->_height);
//        return;
//    }
//    setMeasuredDimension(static_cast<int>(length), static_cast<int>(font.getSpacing()));


    if (isDirty) {
        isDirty = false;
        skia::textlayout::ParagraphStyle paraStyle;
        paraStyle.setTextStyle(*defaultStyle);
        paraStyle.setTextAlign(TextAlign::kCenter);
        paragraphBuilder = std::make_unique<ParagraphBuilderImpl>(paraStyle, fontCollection);
        paragraphBuilder->addText(text.c_str());
        paragraph = paragraphBuilder->Build();
        if (layoutParams->_widthMode == EXACTLY && layoutParams->_heightMode == EXACTLY) {
            setMeasuredDimension(layoutParams->_width, layoutParams->_height);
            return;
        }
//        auto rectsForRange = paragraph->getRectsForRange(0, text.size(), RectHeightStyle::kTight,
//                                                         RectWidthStyle::kTight);
//        assert(rectsForRange.empty());
//        auto wrapRect = rectsForRange[0].rect;
//        if (layoutParams->_widthMode == EXACTLY) {
//            setMeasuredDimension(layoutParams->_width, wrapRect.height());
//        } else if (layoutParams->_heightMode == EXACTLY) {
//            setMeasuredDimension(wrapRect.width(), layoutParams->_height);
//        } else {
//            setMeasuredDimension(wrapRect.width(), wrapRect.height());
//        }
    }
}

void TextView::draw(SkCanvas *canvas) {
    View::draw(canvas);
    //y是基线的位置
//    canvas->drawSimpleText(text.c_str(), text.size(), SkTextEncoding::kUTF8, skRect.left(),
//                           skRect.top() + textRect.height(), font, *textPaint);
//    canvas->drawSimpleText(text.c_str(), text.size(), SkTextEncoding::kUTF8, skRect.left(),
//                           skRect.top() + textRect.height() * 2, font, *textPaint);

    SkASSERT(paragraph);
    paragraph->layout(skRect.width());
    paragraph->paint(canvas, skRect.left(), skRect.top());
}

void TextView::setTextSize(SkScalar textSize) {
    font.setSize(textSize);
    defaultStyle->setFontSize(textSize);
    isDirty = true;
}
