#include "WinSettings.h"

WinSettings::WinSettings(const wxString& appName)
    : wxConfig(appName)
{
    // Add search pattern for fs2011
    gameLocations[FS2011].game = wxT("FS2011");
    gameLocations[FS2011].installLocations.Alloc(9);
    gameLocations[FS2011].installLocations.Add(_T("Steam App 90200"));
    gameLocations[FS2011].installLocations.Add(_T("FarmingSimulator2011INT_is1"));
    gameLocations[FS2011].installLocations.Add(_T("FarmingSimulator2011EN_is1"));
    gameLocations[FS2011].installLocations.Add(_T("FarmingSimulator2011DE_is1"));
    gameLocations[FS2011].installLocations.Add(_T("FarmingSimulator2011FR_is1"));
    gameLocations[FS2011].installLocations.Add(_T("FarmingSimulator2011ES_is1"));
    gameLocations[FS2011].installLocations.Add(_T("FarmingSimulator2011IT_is1"));
    gameLocations[FS2011].installLocations.Add(_T("FarmingSimulator2011RU_is1"));
    gameLocations[FS2011].installLocations.Add(_T("FarmingSimulator2011JP_is1"));
    gameLocations[FS2011].savegameLocation = _T("\\My Games\\FarmingSimulator2011");

    // Add search pattern for fs2013
    gameLocations[FS2013].game = wxT("FS2013");
    gameLocations[FS2013].installLocations.Alloc(9);
    gameLocations[FS2013].installLocations.Add(_T("Steam App 220260"));
    gameLocations[FS2013].installLocations.Add(_T("FarmingSimulator2013INT_is1"));
    gameLocations[FS2013].installLocations.Add(_T("FarmingSimulator2013EN_is1"));
    gameLocations[FS2013].installLocations.Add(_T("FarmingSimulator2013DE_is1"));
    gameLocations[FS2013].installLocations.Add(_T("FarmingSimulator2013FR_is1"));
    gameLocations[FS2013].installLocations.Add(_T("FarmingSimulator2013ES_is1"));
    gameLocations[FS2013].installLocations.Add(_T("FarmingSimulator2013IT_is1"));
    gameLocations[FS2013].installLocations.Add(_T("FarmingSimulator2013RU_is1"));
    gameLocations[FS2013].installLocations.Add(_T("FarmingSimulator2013JP_is1"));
    gameLocations[FS2013].savegameLocation = _T("\\My Games\\FarmingSimulator2013");
}

WinSettings::~WinSettings()
{
}

wxString WinSettings::doFindInstallPath(FarmingSimulatorGames gameId)
{
    // Create main search reg keys
    wxRegKey *MainRegKey = new wxRegKey(_T("HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall"));
    wxRegKey *Main6432RegKey = new wxRegKey(_T("HKEY_LOCAL_MACHINE\\SOFTWARE\\Wow6432Node\\Microsoft\\Windows\\CurrentVersion\\Uninstall"));
    wxRegKey *temp;

    // Loop through available search criteria.
    for (int i = 0; i < (int)gameLocations[gameId].installLocations.GetCount(); i++)
    {
        temp = new wxRegKey(*MainRegKey, gameLocations[gameId].installLocations[i]);
        if (temp->Exists())
        {
            wxString strPath;
            temp->QueryValue(wxT("InstallLocation"), strPath);

            if (strPath != wxEmptyString && wxDirExists(strPath))
            {
                Write(wxString::Format(wxT("/%s/InstallLocation"), gameLocations[gameId].game.c_str()), strPath);

                // cleanup
                delete MainRegKey;
                delete Main6432RegKey;
                delete temp;

                return strPath;
            }
        }

        delete temp;
        temp = new wxRegKey(*Main6432RegKey, gameLocations[gameId].installLocations[i]);
        if (temp->Exists())
        {
            wxString strPath = wxEmptyString;
            temp->QueryValue(_T("InstallLocation"), strPath);

            if (strPath != wxEmptyString && wxDirExists(strPath))
            {
                Write(wxString::Format(wxT("/%s/InstallLocation"), gameLocations[gameId].game.c_str()), strPath);

                // cleanup
                delete MainRegKey;
                delete Main6432RegKey;
                delete temp;

                return strPath;
            }
        } // if (temp->Exists())

        // prepare for next loop
        delete temp;
    } // for (int i = 0; i < gameLocations[gameId].installLocations->GetCount(); i++)
    // cleanup
    delete MainRegKey;
    delete Main6432RegKey;

    Write(wxString::Format(wxT("/%s/InstallLocation"), gameLocations[gameId].game.c_str()), wxEmptyString);

    return wxEmptyString;
}

wxString WinSettings::doFindSavegamePath(FarmingSimulatorGames gameId)
{
    // Create Document search reg key
    wxRegKey Documents(_T("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Shell Folders"));

    // Check if the reg key exists
    if (Documents.Exists())
    {
        wxString strPath = wxEmptyString;
        Documents.QueryValue(_T("Personal"), strPath);

        if (strPath != wxEmptyString)
        {
            strPath += gameLocations[gameId].savegameLocation;

            if (wxDirExists(strPath))
            {
                Write(wxString::Format(wxT("/%s/SavegameLocation"), gameLocations[gameId].game.c_str()), strPath);
                return strPath;
            }
        }
    }

    Write(wxString::Format(wxT("/%s/SavegameLocation"), gameLocations[gameId].game.c_str()), wxEmptyString);

    return wxEmptyString;
}
