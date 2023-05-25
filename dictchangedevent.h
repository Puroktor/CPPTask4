#ifndef DICTCHANGEDEVENT_H
#define DICTCHANGEDEVENT_H

#include <QEvent>

class DictChangedEvent : public QEvent
{
public:
    static const QEvent::Type eventType;

    DictChangedEvent();
};


#endif // DICTCHANGEDEVENT_H
