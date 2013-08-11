#include "Settings.h"
#include "Courseplay_EditorMain.h"
#include "version.h"

#define LayoutUpdateMajor 0
#define LayoutUpdateMinor 0
#define LayoutUpdateBuild 718

Settings::Settings()
        : Locale(this)
{
    setLocaleSearchPath(wxT("Langs"));
    setLocaleConfigPath(wxT("General"));
    loadDefaultLocaleIfExists();

    parent = NULL;
    defaultLayout = wxEmptyString;

    savegameHasChanges = false;
    loadLastSavegame = false;
    backupSavegame = false;
    savegameId = 0;
    saveVersion = false;
    major = 0;
    minor = 0;
    build = 0;

    configFrame = NULL;
}

Settings::Settings(Courseplay_EditorFrame *frame, wxAuiManager *m_mgr)
        : Locale(this)
{
    setLocaleSearchPath(wxT("Langs"));
    setLocaleConfigPath(wxT("General"));

    parent = frame;
    defaultLayout = m_mgr->SavePerspective();

    savegameHasChanges = true;

    saveVersion = true;
    Read(wxT("/General/Major"), &major, EditorVersion::MAJOR);
    Read(wxT("/General/Minor"), &minor, EditorVersion::MINOR);
    Read(wxT("/General/Build"), &build, EditorVersion::BUILD);

    Read(wxT("/General/SelectedGame"), &selectedGameId, FS2013);
    Read(wxT("/General/LoadLastSavegame"), &loadLastSavegame, false);
    Read(wxT("/General/BackupSavegame"), &backupSavegame, true);

    if (loadLastSavegame)
        Read(wxT("/General/SavegameId"), &savegameId, 0);
    else
        savegameId = 0;

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

    if (saveVersion)
    {
        Write(_T("/General/Major"), EditorVersion::MAJOR);

        Write(_T("/General/Minor"), EditorVersion::MINOR);

        Write(_T("/General/Build"), EditorVersion::BUILD);
    }
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
    //(SettingsFrame*)configFrame->up
    configFrame->updateTapPanels();
    configFrame->Show();
    configFrame->SetFocus();
}

void Settings::saveDefaultLayout(wxString layout)
{
    defaultLayout = layout;
}

void Settings::saveLayout(wxString layout)
{
    Write(_T("GUI/layout"), layout);
}

wxString Settings::getSavedLayout()
{
    if (
         major < LayoutUpdateMajor ||
        (major <= LayoutUpdateMajor && minor < LayoutUpdateMinor) ||
        (major <= LayoutUpdateMajor && minor <= LayoutUpdateMinor && build < LayoutUpdateBuild)
       )
    {
        wxString msg = _("The layout have changed since last version.\n\nThe layout will be reset.");
        wxMessageBox(msg, _("New Layout!"), wxOK | wxCENTER | wxICON_INFORMATION);
        saveLayout(defaultLayout);
        return defaultLayout;
    }
    else
        return Read(_T("GUI/layout"), defaultLayout);
}

bool Settings::findInstallPath(FSGames gameId)
{
    installPath[gameId] = doFindInstallPath(gameId);

    return (installPath[gameId] != wxEmptyString);
}

bool Settings::findSavegamePath(FSGames gameId)
{
    savegamePath[gameId] = doFindSavegamePath(gameId);

    return (savegamePath[gameId] != wxEmptyString);
}

void Settings::enableGame(FSGames gameId, bool enable, bool updateToolbar)
{
    Write(wxString::Format(_T("/%s/Enabled"), gameLocations[gameId].game.c_str()), enable);
    if (updateToolbar)
    {
        gameIsEnabled[gameId] = enable;
        updateGameSelect();
    }
}

void Settings::enableGameIfFound(FSGames gameId, bool updateToolbar)
{
    // Set values
    wxString gameName = gameLocations[gameId].game;

    if (installPath[gameId] != wxEmptyString && savegamePath[gameId] != wxEmptyString &&
            wxDirExists(installPath[gameId]) && wxDirExists(savegamePath[gameId]))
        enableGame(gameId, true, updateToolbar);
    else
        enableGame(gameId, false, updateToolbar);
}

void Settings::setInstallPath(FSGames gameId, wxString path)
{
    Write(wxString::Format(wxT("/%s/InstallLocation"), gameLocations[gameId].game.c_str()), path);
    installPath[gameId] = path;
}

void Settings::setSavegamePath(FSGames gameId, wxString path)
{
    Write(wxString::Format(wxT("/%s/SavegameLocation"), gameLocations[gameId].game.c_str()), path);
    savegamePath[gameId] = path;
}

bool Settings::setGameId(FSGames gameId)
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

void Settings::updateSavegameList()
{
    parent->updateSavegameList();
}

wxString Settings::getSavegamePath()
{
    if (selectedGameId >= 0)
        return savegamePath[selectedGameId];

    return wxEmptyString;
}

wxString Settings::getInstallPath()
{
    if (selectedGameId >= 0)
        return installPath[selectedGameId];

    return wxEmptyString;
}

void Settings::setSavegameHasChanges(bool val)
{
    savegameHasChanges = val;
}

void Settings::setLoadLastSavegame(bool val)
{
    loadLastSavegame = val;
    Write(wxT("/General/LoadLastSavegame"), loadLastSavegame);
}

void Settings::setBackupSavegame(bool val)
{
    backupSavegame = val;
    Write(wxT("/General/BackupSavegame"), backupSavegame);
}

void Settings::setSavegameId(long val)
{
    savegameId = val;
    Write(wxT("/General/SavegameId"), savegameId);
}
