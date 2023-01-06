//
// Created by ByteDance on 2022/12/7.
//

#ifndef SKIAUI_HYRECYCLERVIEW_H
#define SKIAUI_HYRECYCLERVIEW_H


#include "../widget/RecyclerView.h"
#include "TextView.h"

struct TestModel {

    int a;
    SkString b;

    TestModel(int a, SkString b) {
        this->a = a;
        this->b = b;
    }

};

class HYRecyclerView : public RecyclerView<TestModel *> {

public:

    HYRecyclerView() {
        auto adapter = new HYRecyclerAdapter();
        auto data = std::vector<TestModel *>();
        for (int i = 0; i < 200; ++i) {
            auto string = "abc" + std::to_string(i);
            data.emplace_back(new TestModel(i, SkString(string)));
        }
        adapter->setData(data);
        setAdapter(adapter);
    }

    virtual ~HYRecyclerView() {

    }

    class HYRecyclerAdapter : public RecyclerViewAdapter<TestModel *> {

        RecyclerViewHolder<TestModel *> *onCreateViewHolder() override {
            auto textView = new TextView();
            textView->setText(SkString("abc"));
            textView->setTextColor(SK_ColorBLACK);
            textView->setTextSize(60);
            textView->setBackgroundColor(SK_ColorRED);
            textView->setStyle(SkPaint::kStroke_Style);
            textView->setDecoration(kLineThrough);
            textView->setDecorationStyle(kSolid);
            textView->setDecorationThicknessMultiplier(3);
            textView->setDecorationColor(SK_ColorRED);
            auto vh = new HYRecyclerVH(textView);
            return vh;
        }

        void onBindViewHolder(RecyclerViewHolder<TestModel *> *viewHolder, int index,
                              TestModel *item) override {
            viewHolder->updateView(item);
            ALOGD("RecyclerView onBindViewHolder %s", item->b.c_str())
        }

        void
        onRecycleViewHolder(RecyclerViewHolder<TestModel *> *viewHolder, TestModel *item) override {
            ALOGD("RecyclerView onRecycleViewHolder %s", item->b.c_str())
        }

        class HYRecyclerVH : public RecyclerViewHolder<TestModel *> {

        public:

            HYRecyclerVH(View *itemView) : RecyclerViewHolder<TestModel *>(itemView) {

            }

            HYRecyclerVH() = delete;

            void updateView(TestModel *item) override {
                auto textView = dynamic_cast<TextView *>(itemView);
                if (textView != nullptr) {
                    textView->setText(item->b);
                }
            }

        };

    };

};

#endif //SKIAUI_HYRECYCLERVIEW_H
