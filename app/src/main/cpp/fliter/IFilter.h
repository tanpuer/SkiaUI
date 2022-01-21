//
// Created by DZSB-000848 on 1/21/22.
//

#ifndef SKIAUI_IFILTER_H
#define SKIAUI_IFILTER_H


class IFilter {

public:

    IFilter() {};

    virtual ~IFilter() {};

    virtual void setWindowSize(int width, int height) = 0;

    virtual void doFrame() = 0;

protected:

    int width = 0;
    int height = 0;

};


#endif //SKIAUI_IFILTER_H
