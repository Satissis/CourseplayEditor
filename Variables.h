#ifndef VARIABLES_H_INCLUDED
#define VARIABLES_H_INCLUDED

#include <wx/wx.h>
#include <wx/dynarray.h>
#include <wx/arrimpl.cpp>


enum FSGames
{
    FS2011,
    FS2013,

    NumOfFSGames,
};

struct GameSearchPaths
{
    wxString        game;
    wxArrayString   installLocations;
    wxString        savegameLocation;
};

struct LangList
{
    wxArrayString names;
    wxArrayString fileNames;
    wxArrayLong identifiers;
};

struct Savegames
{
    wxArrayShort    isValid;
    wxArrayString   name;
    wxArrayShort    isMod;
    wxArrayShort    isZip;
    wxArrayString   mapId;
    wxArrayString   mapFile;
    wxArrayInt      mapWidth;
    wxArrayInt      mapHeight;
    wxArrayString   courseplayFile;

    void Add(short IsValid,
             wxString MapName,
             short IsMod = false,
             short IsZip = false,
             wxString MapId = wxEmptyString,
             wxString MapFile = wxEmptyString,
             int width = 0,
             int height = 0,
             wxString CourseplayFile = wxEmptyString)
    {
        isValid.Add(IsValid);
        name.Add(MapName);
        isMod.Add(IsMod);
        isZip.Add(IsZip);
        mapId.Add(MapId);
        mapFile.Add(MapFile);
        mapWidth.Add(width);
        mapHeight.Add(height);
        courseplayFile.Add(CourseplayFile);
    }

    void Alloc(size_t nCount)
    {
        isValid.Alloc(nCount);
        name.Alloc(nCount);
        isMod.Alloc(nCount);
        isZip.Alloc(nCount);
        mapId.Alloc(nCount);
        mapFile.Alloc(nCount);
        mapWidth.Alloc(nCount);
        mapHeight.Alloc(nCount);
        courseplayFile.Alloc(nCount);
    }

    void Clear()
    {
        isValid.Clear();
        name.Clear();
        isMod.Clear();
        isZip.Clear();
        mapId.Clear();
        mapFile.Clear();
        mapWidth.Clear();
        mapHeight.Clear();
        courseplayFile.Clear();
    }

    size_t Count()
    {
        return isValid.Count();
    }
};

class CourseData
{
public: // Functions
    CourseData();
    ~CourseData();

    void Add(wxDouble   PosX,
             wxDouble   PosY,
             wxDouble   Angle,
             short      Wait,
             short      Crossing,
             short      Reverse,
             wxDouble   Speed,
             // For Courseplay 3.4+
             wxString   Turn = wxEmptyString,
             short      TurnStart = 0,
             short      TurnEnd = 0,
             short      Ridgemarker = 0,
             wxString   Generated = wxEmptyString
            );
    void Alloc(size_t nCount);
    void Clear();
    size_t Count();

public: // Variables
    wxArrayDouble posX;
    wxArrayDouble posY;
    wxArrayDouble angle;
    wxArrayShort  wait;
    wxArrayShort  crossing;
    wxArrayShort  rev;
    wxArrayDouble speed;
    // variables under here is for Courseplay 3.4+
    wxArrayString turn; // false, left, right
    wxArrayShort  turnStart;
    wxArrayShort  turnEnd;
    wxArrayShort  ridgemarker; // 0 = off, 1 = left, 2 = right
    wxArrayString generated; // false, true
};

WX_DECLARE_OBJARRAY(CourseData, ArrayCourseData);
//WX_DEFINE_OBJARRAY(ArrayCourseData);

struct SavegameData
{
    // CP Hud Data
    wxDouble posX;
    wxDouble posY;

    void SetHud(wxDouble PosX = 0.43299999833107, wxDouble PosY = 0.0020000000949949)
    {
        posX = PosX;
        posY = PosY;
    }

    // CP Course Data
    wxArrayString   name;
    wxArrayInt      id;
    wxArrayLong     numWaypoints;
    ArrayCourseData course;

    void Add(wxString   Name,
             int        Id,
             long       NumWaypoints,
             CourseData Course
            )
    {
        name.Add(Name);
        id.Add(Id);
        numWaypoints.Add(NumWaypoints);
        course.Add(Course);
    }

    void Alloc(size_t nCount)
    {
        name.Alloc(nCount);
        id.Alloc(nCount);
        numWaypoints.Alloc(nCount);
        course.Alloc(nCount);
    }

    void Clear()
    {
        name.Clear();
        id.Clear();
        numWaypoints.Clear();
        course.Clear();
    }

    size_t Count()
    {
        return name.Count();
    }

    // Holds the savegame data to be used.
};

#endif // VARIABLES_H_INCLUDED
