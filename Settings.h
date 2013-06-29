#ifndef SETTINGS_H_INCLUDED
#define SETTINGS_H_INCLUDED

#include <wx/app.h>
#include <wx/wx.h>
#include <wx/aui/aui.h>

#ifdef __WIN32__
#   include "WinSettings.h"
#else
#   error Platform not supported. Only Windows is supported right now.
#endif

#include "SettingsFrame.h"
#include "Locale.h"

class Courseplay_EditorFrame;

class Settings : public CoreSettings, public Locale
{
public: // Functions
    Settings();
    Settings(Courseplay_EditorFrame *frame, wxAuiManager *m_mgr);
    virtual ~Settings();

    bool isFirstTimeSetup();
    void doFirstTimeSetup();

    void showSettings();
    void saveDefaultLayout(wxString layout);

    // Game Handling and path findings
    bool findInstallPath(FarmingSimulatorGames gameId);
    bool findSavegamePath(FarmingSimulatorGames gameId);
    void enableGame(FarmingSimulatorGames gameId, bool enable = true, bool updateToolbar = true);
    void enableGameIfFound(FarmingSimulatorGames gameId, bool updateToolbar = true);
    void setInstallPath(FarmingSimulatorGames gameId, wxString path = wxEmptyString);
    void setSavegamePath(FarmingSimulatorGames gameId, wxString path = wxEmptyString);

    bool setGameId(FarmingSimulatorGames gameId);

public: // Variables
    bool        gameIsEnabled[NumOfFSGames];

    long        selectedGameId;

    wxString    defaultLayout;
    wxString    installPath[NumOfFSGames];
    wxString    savegamePath[NumOfFSGames];

protected: // Variables
    Courseplay_EditorFrame  *parent;
    wxFrame                 *configFrame;

private: // Functions
    void updateGameSelect();

};


#endif // SETTINGS_H_INCLUDED
