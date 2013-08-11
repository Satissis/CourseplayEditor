#include "Variables.h"

CourseData::CourseData()
{
    //ctor
}

CourseData::~CourseData()
{
    //dtor
}

void CourseData::Add(wxDouble   PosX,
                     wxDouble   PosY,
                     wxDouble   Angle,
                     short      Wait,
                     short      Crossing,
                     short      Reverse,
                     wxDouble   Speed,
                     // For Courseplay 3.4+
                     wxString   Turn,
                     short      TurnStart,
                     short      TurnEnd,
                     short      Ridgemarker,
                     wxString   Generated
                    )
{
    posX.Add(PosX);
    posY.Add(PosY);
    angle.Add(Angle);
    wait.Add(Wait);
    crossing.Add(Crossing);
    rev.Add(Reverse);
    speed.Add(Speed);
    // For Courseplay 3.4+
    turn.Add(Turn);
    turnStart.Add(TurnStart);
    turnEnd.Add(TurnEnd);
    ridgemarker.Add(Ridgemarker);
    generated.Add(Generated);
}

void CourseData::Alloc(size_t nCount)
{
    posX.Alloc(nCount);
    posY.Alloc(nCount);
    angle.Alloc(nCount);
    wait.Alloc(nCount);
    crossing.Alloc(nCount);
    rev.Alloc(nCount);
    speed.Alloc(nCount);
    // For Courseplay 3.4+
    turn.Alloc(nCount);
    turnStart.Alloc(nCount);
    turnEnd.Alloc(nCount);
    ridgemarker.Alloc(nCount);
    generated.Alloc(nCount);
}

void CourseData::Clear()
{
    posX.Clear();
    posY.Clear();
    angle.Clear();
    wait.Clear();
    crossing.Clear();
    rev.Clear();
    speed.Clear();
    // For Courseplay 3.4+
    turn.Clear();
    turnStart.Clear();
    turnEnd.Clear();
    ridgemarker.Clear();
    generated.Clear();
}

size_t CourseData::Count()
{
    return posX.Count();
}
