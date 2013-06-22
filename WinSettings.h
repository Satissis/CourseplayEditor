#ifndef WINSETTINGS_H_INCLUDED
#define WINSETTINGS_H_INCLUDED

#include "Variables.h"
#include <wx/config.h>

class WinSettings : public wxConfig
{
    public:
        WinSettings(const wxString& appName = wxEmptyString);
        virtual ~WinSettings();

        // Game Handling and path findings
        wxString doFindInstallPath(FarmingSimulatorGames gameId);
        wxString doFindSavegamePath(FarmingSimulatorGames gameId);

        // Variables.
        GameSearchPaths gameLocations[NumOfFSGames];

};

#endif // WINSETTINGS_H_INCLUDED
