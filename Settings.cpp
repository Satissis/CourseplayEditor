#include "Settings.h"
#include "Courseplay_EditorMain.h"

Settings::Settings()
        : Locale((wxConfig*) this)
{
    setLocaleSearchPath(wxT("Langs"));
    setLocaleConfigPath(wxT("General"));
    loadDefaultLocaleIfExists();

    parent = NULL;
    defaultLayout = wxEmptyString;
    configFrame = NULL;
}

Settings::Settings(Courseplay_EditorFrame *frame, wxAuiManager *m_mgr)
        : Locale((wxConfig*) this)
{
    setLocaleSearchPath(wxT("Langs"));
    setLocaleConfigPath(wxT("General"));

    parent = frame;
    defaultLayout = wxEmptyString;

    Read(wxT("/General/SelectedGame"), &selectedGameId, FS2013);

    for (int i = 0; i < NumOfFSGames; i++)
    {
        Read(wxString::Format(wxT("/%s/Enabled"),           gameLocations[i].game.c_str()), &gameIsEnabled[i],  false);
        Read(wxString::Format(wxT("/%s/InstallLocation"),   gameLocations[i].game.c_str()), &installPath[i],    wxEmptyString);
        Read(wxString::Format(wxT("/%s/SavegameLocation"),  gameLocations[i].game.c_str()), &savegamePath[i],   wxEmptyString);
    }

    configFrame = new SettingsFrame(this, m_mgr, (wxWindow*) parent);
}

Settings::~Settings()
{
    // Here for destructing things if needed.
    if (configFrame)
        delete configFrame;
}

bool Settings::isFirstTimeSetup()
{
    bool doneFirstTimeSetup;
    Read(_T("/General/DoneFirstTimeSetup"), &doneFirstTimeSetup, false);
    return !doneFirstTimeSetup;
}

void Settings::doFirstTimeSetup()
{
    // Ask user for Language
    askUserForLanguage(_("Select language to use."), _("Language Select"));
    saveLocale();

    // Ask to auto detect locations
    wxString msg = wxEmptyString;
    msg += _("Do you want Courseplay Editor to try to auto detect where Farming Simulator(s) install and savegame locations are?\n\n");
    msg += _("If you select (No) you can set the install and savegame locations under Edit->Settings");
    int answer = wxMessageBox(msg, _("First Time Setup"), wxYES_NO | wxICON_QUESTION, parent);

    if (answer == wxYES)
    {
        bool fs2011FoundInstallPath = findInstallPath (FS2011);
        bool fs2011FoundSavePath    = findSavegamePath(FS2011);
        bool fs2013FoundInstallPath = findInstallPath (FS2013);
        bool fs2013FoundSavePath    = findSavegamePath(FS2013);

        // Enable game if both path is found.
        enableGameIfFound(FS2011, false);
        enableGameIfFound(FS2013, false);

        // Show result of auto detect.
        if (fs2011FoundInstallPath || fs2011FoundSavePath ||
            fs2013FoundInstallPath || fs2013FoundSavePath)
        {
            bool addExtraDescription = false;
            msg = wxEmptyString;
            if (fs2011FoundInstallPath && fs2011FoundSavePath)
                msg += _("Found all Farming Simulator 2011 Locations\n");
            else if (fs2011FoundInstallPath && !fs2011FoundSavePath)
            {
                msg += _("Found Farming Simulator 2011 install location, but did not find the savegame location\n");
                addExtraDescription = true;
            }
            else if (!fs2011FoundInstallPath && fs2011FoundSavePath)
            {
                msg += _("Found Farming Simulator 2011 savegame location but did not find the install location\n");
                addExtraDescription = true;
            }


            if (fs2013FoundInstallPath && fs2013FoundSavePath)
                msg += _("Found all Farming Simulator 2013 Locations\n");
            else if (fs2013FoundInstallPath && !fs2013FoundSavePath)
            {
                msg += _("Found Farming Simulator 2013 install location, but did not find the savegame location\n");
                addExtraDescription = true;
            }
            else if (!fs2013FoundInstallPath && fs2013FoundSavePath)
            {
                msg += _("Found Farming Simulator 2013 savegame location but did not find the install location\n");
                addExtraDescription = true;
            }

            if (addExtraDescription)
                msg += _("\nYou can manually select the install and savegame location under Edit->Settings menu if you have one of the game installed.");
        }
        else
        {
            msg = wxEmptyString;
            msg += _("Courseplay Editor did not find any Farming Simulator games.\n");
            msg += _("\nYou can manually select the install and savegame location under Edit->Settings menu if you have one of the game installed.");
        }
        wxMessageBox(msg, _("Courseplay Editor Auto Detect Result"), wxOK, parent);
    }

    Write(_T("/General/DoneFirstTimeSetup"), true);
}

void Settings::showSettings()
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

void Settings::enableGame(FarmingSimulatorGames gameId, bool enable, bool updateToolbar)
{
    Write(wxString::Format(_T("/%s/Enabled"), gameLocations[gameId].game.c_str()), enable);
    if (updateToolbar)
    {
        gameIsEnabled[gameId] = enable;
        updateGameSelect();
    }
}

void Settings::enableGameIfFound(FarmingSimulatorGames gameId, bool updateToolbar)
{
    // Set values
    wxString gameName = gameLocations[gameId].game;

    if (installPath[gameId] != wxEmptyString && savegamePath[gameId] != wxEmptyString &&
            wxDirExists(installPath[gameId]) && wxDirExists(savegamePath[gameId]))
        enableGame(gameId, true, updateToolbar);
    else
        enableGame(gameId, false, updateToolbar);
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

bool Settings::setGameId(FarmingSimulatorGames gameId)
{
    if (gameId >= 0 && gameId < NumOfFSGames)
    {
        selectedGameId = gameId;
        return Write(wxT("/General/SelectedGame"), selectedGameId);
    }

    return false;
}

void Settings::updateGameSelect()
{
    bool noGameActive = true;
    //parent->selectedGameId;
    // TODO: Update Game Select.
    if (selectedGameId < 0 || (selectedGameId >= 0 && !gameIsEnabled[selectedGameId]))
    {
        for (int i = 0; i < NumOfFSGames; i++)
        {
            if (gameIsEnabled[i])
            {
                noGameActive = false;
                selectedGameId = i;
                break;
            }
        }

        if (noGameActive)
            selectedGameId = -1;

        Write(wxT("/General/SelectedGame"), selectedGameId);

        parent->updateToolbar2();
    }
}
