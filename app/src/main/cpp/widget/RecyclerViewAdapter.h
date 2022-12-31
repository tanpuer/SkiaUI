//
// Created by ByteDance on 2022/12/6.
//

#ifndef SKIAUI_RECYCLERVIEWADAPTER_H
#define SKIAUI_RECYCLERVIEWADAPTER_H

#include "vector"
#include "RecyclerViewHolder.h"

template<typename T>
class RecyclerViewAdapter {

public:

    RecyclerViewAdapter() {
        data = std::vector<T>();
    }

    virtual ~RecyclerViewAdapter() {

    }

    virtual void setData(std::vector<T> data) {
        this->data = data;
    }

    virtual T getItem(int pos) {
        assert(pos >= 0 && pos < data.size());
        return data[pos];
    }

    int getSize() {
        return data.size();
    }

#pragma mark ViewHolder

    virtual RecyclerViewHolder<T> *onCreateViewHolder() = 0;

    virtual void onBindViewHolder(RecyclerViewHolder<T> *viewHolder, int index, T item) = 0;

#pragma mark notify

    virtual void notifyDataSetChanged() {

    }

    virtual void notifyItemChanged(int index) {

    }

protected:

    int totalIndex;

    int currentIndex;

    std::vector<T> data;

};

#endif //SKIAUI_RECYCLERVIEWADAPTER_H
