//
// Created by ByteDance on 2022/8/5.
//

#ifndef SKIAUI_BASELISTADAPTER_H
#define SKIAUI_BASELISTADAPTER_H

#include "vector"
#include "View.h"

template<typename T>
class BaseListAdapter {

    static_assert(std::is_default_constructible<T>::value,
                  "Class ListAdapter require default-constructor");

public:

    BaseListAdapter();

    virtual ~BaseListAdapter();

    virtual void setData(std::vector<T> data);

    virtual void notifyDataSetChanged();

    virtual void notifyItemChanged();

    virtual int getItemCount();

    virtual View *createView();

    virtual void bindView(View *view, T model);

    virtual void attachView(View *view);

    virtual void detachView(View *view);

protected:

    std::vector<T> mData;

};


#endif //SKIAUI_BASELISTADAPTER_H
