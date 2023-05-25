#include "dictchangedevent.h"
#include <QEvent>

const QEvent::Type DictChangedEvent::eventType = static_cast<QEvent::Type>(QEvent::registerEventType());

DictChangedEvent::DictChangedEvent()
    : QEvent(eventType)
{

}
