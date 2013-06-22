#ifndef SETTINGS_H_INCLUDED
#define SETTINGS_H_INCLUDED

#include <wx/wx.h>
#include <wx/aui/aui.h>

#ifdef __WIN32__
#   include "WinSettings.h"
#else
#   error Platform not supported. Only Windows is supported right now.
#endif

#include "SettingsFrame.h"

class Settings : public WinSettings
{
public:
    Settings(wxFrame *frame, wxAuiManager *m_mgr, const wxString& appName = wxEmptyString);
    virtual ~Settings();

    void showSettings(void);
    void saveDefaultLayout(wxString layout);

    // Game Handling and path findings
    bool findInstallPath(FarmingSimulatorGames gameId);
    bool findSavegamePath(FarmingSimulatorGames gameId);
    void enableGame(FarmingSimulatorGames gameId, bool enable = true);
    void enableGameIfFound(FarmingSimulatorGames gameId);
    void setInstallPath(FarmingSimulatorGames gameId, wxString path = wxEmptyString);
    void setSavegamePath(FarmingSimulatorGames gameId, wxString path = wxEmptyString);

    void updateGameSelect(void);

public: // Variables
    bool        gameIsEnabled[NumOfFSGames];

    long        selectedGameId;

    wxString    defaultLayout;
    wxString    installPath[NumOfFSGames];
    wxString    savegamePath[NumOfFSGames];

protected:
    wxFrame         *parent;
    wxFrame         *configFrame;

private:

};


#endif // SETTINGS_H_INCLUDED
