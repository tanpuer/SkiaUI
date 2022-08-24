//
// Created by ByteDance on 2022/8/4.
//

#include <time_utils.h>
#include "ListViewTest.h"
#include "BaseListView.h"
#include "HYListView.h"
#include "HYListAdapter.h"

ListViewTest::ListViewTest() = default;

ListViewTest::~ListViewTest() = default;

void ListViewTest::doDrawTest(int drawCount, SkCanvas *canvas, int width, int height) {
    if (root == nullptr) {
        auto listView = new HYListView();
        config = YGConfigNew();
        root = listView;
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
        auto adapter = new HYListAdapter();
        auto data = std::vector<int>();
        for (int i = 0; i < 10; ++i) {
            data.emplace_back(i);
        }
        adapter->setData(data);
        listView->setAdapter(adapter);
    }

    auto rootWidthSpec = MeasureSpec::makeMeasureSpec(width, EXACTLY);
    auto rootHeightSpec = MeasureSpec::makeMeasureSpec(height, EXACTLY);
    root->measure(rootWidthSpec, rootHeightSpec);
    root->layout(0, 0, width, height);
    root->draw(canvas);
}
