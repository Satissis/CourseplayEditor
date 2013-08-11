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

class Courseplay_EditorFrame;   // Dummy
class SettingsFrame;            // Dummy

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
    void saveLayout(wxString layout);
    wxString getSavedLayout();

    // Game Handling and path findings
    bool findInstallPath(FSGames gameId);
    bool findSavegamePath(FSGames gameId);
    void enableGame(FSGames gameId, bool enable = true, bool updateToolbar = true);
    void enableGameIfFound(FSGames gameId, bool updateToolbar = true);
    void setInstallPath(FSGames gameId, wxString path = wxEmptyString);
    void setSavegamePath(FSGames gameId, wxString path = wxEmptyString);

    bool setGameId(FSGames gameId);

    void setSavegameHasChanges(bool val = true);

    wxString getSavegamePath();
    wxString getInstallPath();

    void updateSavegameList();
    void setLoadLastSavegame(bool val);
    void setBackupSavegame(bool val);
    void setSavegameId(long val);

public: // Variables
    bool        gameIsEnabled[NumOfFSGames];
    bool        savegameHasChanges;
    bool        loadLastSavegame;
    bool        backupSavegame;

    long        selectedGameId;
    long        savegameId;

    wxString    defaultLayout;
    wxString    installPath[NumOfFSGames];
    wxString    savegamePath[NumOfFSGames];

protected: // Variables
    Courseplay_EditorFrame  *parent;
    SettingsFrame           *configFrame;

    bool saveVersion;
    long major;
    long minor;
    long build;

private: // Functions
    void updateGameSelect();

};


#endif // SETTINGS_H_INCLUDED
