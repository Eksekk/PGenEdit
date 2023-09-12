#include "pch.h"
#include "TimeChooserCtrl.h"
#include "GameStructAccessor.h"

GameTime::GameTime() : ticks(0), minutes(0), hours(0), days(0), weeks(0), months(0), years(0)
{

}

GameTime GameTime::current()
{
    int64_t ticks = gameAccessor->getTime();
    return GameTime();
}

bool GameTime::processTimeChanges()
{
    return false;
}

GameTime operator-(const GameTime& lhs, const GameTime& rhs)
{
    return GameTime();
}
