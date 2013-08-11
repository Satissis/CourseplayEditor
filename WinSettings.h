#ifndef WINSETTINGS_H_INCLUDED
#define WINSETTINGS_H_INCLUDED

#include "Variables.h"
#include <wx/config.h>

class CoreSettings : public wxConfig
{
    public:
        CoreSettings();
        virtual ~CoreSettings();

        // Game Handling and path findings
        wxString doFindInstallPath(FSGames gameId);
        wxString doFindSavegamePath(FSGames gameId);

        // Variables.
        GameSearchPaths gameLocations[NumOfFSGames];

};

#endif // WINSETTINGS_H_INCLUDED
