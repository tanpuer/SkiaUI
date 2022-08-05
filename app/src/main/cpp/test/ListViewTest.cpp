//
// Created by ByteDance on 2022/8/4.
//

#include "ListViewTest.h"

ListViewTest::ListViewTest() = default;

ListViewTest::~ListViewTest() = default;

void ListViewTest::doDrawTest(int drawCount, SkCanvas *canvas, int width, int height) {

}

View *ListViewTest::getRootView() {
    return ITestDraw::getRootView();
}
