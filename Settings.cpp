#include "Settings.h"

Settings::Settings(wxFrame *frame, wxAuiManager *m_mgr, const wxString& appName)
        : WinSettings(appName)
{
    parent = frame;
    defaultLayout = wxEmptyString;

    Read(wxT("/General/SelectedGame"), &selectedGameId, FS2013);

    for (int i = 0; i < NumOfFSGames; i++)
    {
        Read(wxString::Format(wxT("/%s/Enabled"),           gameLocations[i].game.c_str()), &gameIsEnabled[i],  false);
        Read(wxString::Format(wxT("/%s/InstallLocation"),   gameLocations[i].game.c_str()), &installPath[i],    wxEmptyString);
        Read(wxString::Format(wxT("/%s/SavegameLocation"),  gameLocations[i].game.c_str()), &savegamePath[i],   wxEmptyString);
    }

    configFrame = new SettingsFrame(this, m_mgr, parent);
}

Settings::~Settings()
{
    delete configFrame;
    // Here for destructing things if needed.
}

void Settings::showSettings(void)
{
    configFrame->Show();
    configFrame->SetFocus();
}

void Settings::saveDefaultLayout(wxString layout)
{
    defaultLayout = layout;
}

bool Settings::findInstallPath(FarmingSimulatorGames gameId)
{
    installPath[gameId] = doFindInstallPath(gameId);

    return (installPath[gameId] != wxEmptyString);
}

bool Settings::findSavegamePath(FarmingSimulatorGames gameId)
{
    savegamePath[gameId] = doFindSavegamePath(gameId);

    return (savegamePath[gameId] != wxEmptyString);
}

void Settings::enableGame(FarmingSimulatorGames gameId, bool enable)
{
    Write(wxString::Format(_T("/%s/Enabled"), gameLocations[gameId].game.c_str()), enable);
    gameIsEnabled[gameId] = enable;
    updateGameSelect();
}

void Settings::enableGameIfFound(FarmingSimulatorGames gameId)
{
    // Set values
    wxString gameName = gameLocations[gameId].game;

    if (installPath[gameId] != wxEmptyString && savegamePath[gameId] != wxEmptyString &&
            wxDirExists(installPath[gameId]) && wxDirExists(savegamePath[gameId]))
        enableGame(gameId, true);
    else
        enableGame(gameId, false);
}

void Settings::setInstallPath(FarmingSimulatorGames gameId, wxString path)
{
    Write(wxString::Format(wxT("/%s/InstallLocation"), gameLocations[gameId].game.c_str()), path);
    installPath[gameId] = path;
}

void Settings::setSavegamePath(FarmingSimulatorGames gameId, wxString path)
{
    Write(wxString::Format(wxT("/%s/SavegameLocation"), gameLocations[gameId].game.c_str()), path);
    savegamePath[gameId] = path;
}

void Settings::updateGameSelect(void)
{
    //parent->selectedGameId;

}
