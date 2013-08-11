#include "DataHandler.h"

#include "Settings.h"

#include <wx/dir.h>
#include <wx/filename.h>
#include <wx/tokenzr.h>
#include <wx/wfstream.h>
#include <wx/mstream.h>
#include <wx/zipstrm.h>
#include <wx/sstream.h>
#include <wx/strconv.h>
#include <wx/regex.h>

//#include <iostream>
#include <memory>

#define BUFSIZE 0x10000 // the buffer size to pull each time


DataHandler::DataHandler(Settings *settings)
{
    //ctor
    setup = settings;

    savegameList = new Savegames;

    // Define the possible map sizes
    mapSizes[512] = 1024;
    mapSizes[513] = 1024;
    mapSizes[1024] = 2048;
    mapSizes[1025] = 2048;
    mapSizes[2048] = 4096;
    mapSizes[2049] = 4096;
    mapSizes[4096] = 8192;
    mapSizes[4097] = 8192;
    mapSizes[8192] = 16384;
    mapSizes[8193] = 16384;
    mapSizes[16384] = 32768;
    mapSizes[16385] = 32768;
}

DataHandler::~DataHandler()
{
    //dtor
    if (savegameList)
        delete savegameList;

    mapSizes.clear();
}

bool DataHandler::getSavegames()
{
    FSGames gameId = (FSGames) setup->selectedGameId;
    wxString path = setup->getSavegamePath();

    savegameList->Clear();

    if (wxDirExists(path))
    {
        savegameList->Add(false, _("Select Savegame"));

        //wxDir dir(path);
        bool savegameFound = true;
        short  num = 1;
        while (savegameFound)
        {
            wxString SGPath = path + wxFileName::GetPathSeparator() + wxString::Format(wxT("savegame%d"), num);
            if (wxDirExists(SGPath))
            {
                bool        isValid         = false;
                bool        isAMod          = false;
                bool        isAZip          = false;
                wxString    name            = wxEmptyString;
                wxString    mapId           = wxEmptyString;
                wxString    mapFile         = wxEmptyString;
                int         width           = 0;
                int         height          = 0;
                wxString    courseplayFile  = wxEmptyString;

                if (gameId != FS2011 && num < 10)
                    name = wxString::Format(wxT("0%d: "), num);
                else
                    name = wxString::Format(wxT("%d: "), num);

                wxString career = SGPath + wxFileName::GetPathSeparator() + wxT("careerSavegame.xml");
                if (wxFileExists(career))
                {
                    wxXmlDocument xml;

                    xml.Load(career);

                    if (xml.IsOk() && xml.GetRoot()->GetName() == wxT("careerSavegame"))
                    {
                        wxXmlNode *root;
                        root = xml.GetRoot();

                        isValid = root->GetPropVal(wxT("valid"), wxT("false")) == wxT("true");
                        if (isValid)
                        {
                            mapId = root->GetPropVal(wxT("mapId"), wxT("Map01"));

                            isAMod = isMod(mapId);
                            isAZip = isZip(mapId);
                            if (isAMod && isAZip)
                                updateZipDataFileList(mapId);

                            mapFile = getMapFile(mapId);
                            isValid = mapFile != wxEmptyString;

                            if (isValid)
                            {
                                wxString tempName = getMapName(mapId);

                                if (tempName == wxEmptyString)
                                {
                                    isValid = false;
                                    name += _("Invalid Savegame");
                                }
                                else
                                    name += tempName;
                            }

                            if (isValid)
                                isValid = getMapSize(width, height, mapId);

                            if (isValid)
                            {
                                wxFloat32 km2 = ((float)width / 1000) * ((float)height / 1000);

                                name += wxString::Format(wxT(" (%.2fKm%c)"), km2, 178);

                                wxString cpFile = SGPath + wxFileName::GetPathSeparator() + wxT("courseplay.xml");
                                if (wxFileExists(cpFile))
                                {
                                    courseplayFile = cpFile;
                                }
                            }
                        }
                        else
                            name += _("Unused Savegame");
                    }
                    else
                        name += _("Invalid Savegame");
                }

                savegameList->Add(isValid, name, isAMod, isAZip, mapId, mapFile, width, height, courseplayFile);

                num++;
            }
            else
              savegameFound = false;
        }

        // TODO: Remove this after totally implemented and fully tested.
        /*
        int listNum = 2;
        wxLogDebug( wxT("------------------------------------------------------------")                             );
        wxLogDebug( wxString::Format(wxT("-- Savegame Num %d"), listNum                                         )   );
        wxLogDebug( wxT("------------------------------------------------------------")                             );
        wxLogDebug( wxString::Format(   wxT("Name: %s"),        savegameList->name[listNum].c_str()             )   );
        wxLogDebug( wxString::Format(   wxT("IsValid: %d"),     savegameList->isValid[listNum]                  )   );
        wxLogDebug( wxString::Format(   wxT("IsMod: %d"),       savegameList->isMod[listNum]                    )   );
        wxLogDebug( wxString::Format(   wxT("IsZip: %d"),       savegameList->isZip[listNum]                    )   );
        wxLogDebug( wxString::Format(   wxT("MapId: %s"),       savegameList->mapId[listNum].c_str()            )   );
        wxLogDebug( wxString::Format(   wxT("MapFile: %s"),     savegameList->mapFile[listNum].c_str()          )   );
        wxLogDebug( wxString::Format(   wxT("MapWidth: %d"),    savegameList->mapWidth[listNum]                 )   );
        wxLogDebug( wxString::Format(   wxT("MapHeight: %d"),   savegameList->mapHeight[listNum]                )   );
        wxLogDebug( wxString::Format(   wxT("CPFile: %s"),      savegameList->courseplayFile[listNum].c_str()   )   );
        wxLogDebug( wxT("------------------------------------------------------------")                             );
        */

        if (savegameList->Count() > 1)
            return true;
        else
            savegameList->name[0] = _("No Savegames Found");
    }
    else
        savegameList->Add(false, _("No Savegames Found"));

    return false;
}

bool DataHandler::loadSavegame()
{
    // TODO: load the savegame.



    return true;
}

bool DataHandler::saveSavegame()
{
    // TODO: Save the savegame
    return true;
}

/************************************************************************************************************
** Protected Functions
************************************************************************************************************/

wxString DataHandler::buildSearchString(wxArrayString array, wxString tokenizer)
{
    if (!array.IsEmpty() && tokenizer != wxEmptyString)
    {
        wxString string = wxEmptyString;
        for (int i = 0; i < (int)array.Count(); i++)
        {
            if (i > 0)
                string += tokenizer;

            string += array[i];
        }

        // wxLogDebug(wxString::Format(wxT("buildSearchString: %s"), string.c_str()));
        return string;
    }

    return wxEmptyString;
}

wxString DataHandler::findModDataFile(wxString path, wxString regEx)
{
    wxRegEx fileToken(regEx, wxRE_EXTENDED | wxRE_ICASE);

    if (fileToken.IsValid())
    {
        wxDir dir(path);

        wxString filename;
        bool cont = dir.GetFirst(&filename);
        while (cont)
        {
            wxString fileOrDir = dir.GetName() + wxFileName::GetPathSeparator() + filename;

            if (wxDirExists(fileOrDir))
            {
                wxString returnFile = findModDataFile(fileOrDir, regEx);
                if (returnFile != wxEmptyString)
                    return returnFile;
            }
            else if (fileToken.Matches(filename))
            {
                return fileOrDir;
            }

            cont = dir.GetNext(&filename);
        }
    }

    return wxEmptyString;
}

wxString DataHandler::getMapName(wxString mapID)
{
    FSGames gameId = (FSGames) setup->selectedGameId;

    if (isMod(mapID))
    {
        return getModMapName(mapID);
    }
    else
    {
        if (gameId == FS2013)
            return _("Hagenstedt");
        else
            return _("Standard Map");
    }

}

wxString DataHandler::getModMapName(wxString mapID)
{
    wxStringTokenizer tkz(mapID, wxT("."));
    wxString mapToken = tkz.GetNextToken();
    wxXmlDocument xml;
    wxMemoryBuffer buf;

    // Load modDesc.xml from a zip file.
    if (isZip(mapID))
    {
        wxString file = findZipDataFile(wxT("modDesc\\.xml$"));
        if (file != wxEmptyString)
        {
            getZipData(buf, mapID, file);
        }
    }
    // Load modDesc.xml from a folder.
    else
    {
        wxString path = getCurrentModDir() + wxFileName::GetPathSeparator() + mapToken;
        readFileData(buf, findModDataFile(path, wxT("modDesc\\.xml$")));
    }

    // Convert buffer data to correct encoding.
    wxString data = getXmlStringData(buf);

    // If we got data, load it into the xml handler
    if (data != wxEmptyString)
    {
        wxStringInputStream in(data);
        xml.Load(in, wxT("UTF-8"), wxXMLDOC_KEEP_WHITESPACE_NODES);
    }
    // Else we return an unknown map name.
    else
        return _("Unknown Map Name");

    // Find the title of the map in the xml we just loaded
    if (xml.IsOk() && xml.GetRoot()->GetName() == wxT("modDesc"))
    {
        wxXmlNode *root;
        root = xml.GetRoot();

        wxStringTokenizer tkz(mapID, wxT("."));
        tkz.GetNextToken(); // Skip the first one since we don't need it.
        wxString specialization = tkz.GetNextToken(); // Get the second mapId, which is the specialization

        // Create xml search pattern to find the map name
        wxArrayString xmlPaths;
        xmlPaths.Alloc(4);
        xmlPaths.Add(wxString::Format( wxT("maps.map->id=%s.title.%s"), specialization.c_str(), setup->shortLangName.c_str()));
        xmlPaths.Add(wxString::Format( wxT("maps.map->id=%s.title.en"), specialization.c_str()));
        xmlPaths.Add(wxString::Format( wxT("title.%s"), setup->shortLangName.c_str()));
        xmlPaths.Add(wxT("title.en"));

        for (int i = 0; i < (int)xmlPaths.Count(); i++)
        {
            if ( XmlElementExists( root, xmlPaths[i] ) )
            {
                wxXmlNode *child = getXmlElement(root, xmlPaths[i]);
                return child->GetNodeContent();
            }
        }

        // we didn't find any map name, so we still lets it be active, but with an unknown map name
        return _("Unknown Map Name");
    }

    return wxEmptyString;
}

wxString DataHandler::getMapFile(wxString mapID)
{
    //FSGames gameId = (FSGames) setup->selectedGameId;
    if (isMod(mapID))
    {
        return getModMapFile(mapID);
    }
    else
    {
        wxString mapFile =  setup->getInstallPath() + wxFileName::GetPathSeparator() +
                            wxT("data") + wxFileName::GetPathSeparator() +
                            wxT("maps") + wxFileName::GetPathSeparator() +
                            wxT("map01") + wxFileName::GetPathSeparator() +
                            wxT("pda_map.dds");

        if (wxFileExists(mapFile))
            return mapFile;
        else
            return wxEmptyString;
    }

}

wxString DataHandler::getModMapFile(wxString mapID)
{
    wxStringTokenizer tkz(mapID, wxT("."));
    wxString mapToken = tkz.GetNextToken();

    if (isZip(mapID))
    {
        return findZipDataFile(wxT("pda_map\\.dds$"));
    }
    else
    {
        wxString path = getCurrentModDir() + wxFileName::GetPathSeparator() + mapToken;
        return findModDataFile(path, wxT("pda_map\\.dds$"));
    }
}

bool DataHandler::getMapSize(int &width, int &height, wxString mapID)
{
    FSGames gameId = (FSGames) setup->selectedGameId;

    wxStringTokenizer tkz(mapID, wxT("."));
    wxString mapToken = tkz.GetNextToken();

    if (isMod(mapID))
    {
        return getModMapSize(width, height, mapID);
    }
    else
    {
        if (gameId == FS2011)
        {
            width = 2048;
            height = 2048;
            return true;
        }
        else if (gameId == FS2013)
        {
            width = 2048;
            height = 2048;
            return true;
        }
    }

    return false;
}

bool DataHandler::getModMapSize(int &width, int &height, wxString mapID)
{
    wxStringTokenizer tkz(mapID, wxT("."));
    wxString mapToken = tkz.GetNextToken();
    wxMemoryBuffer buf;

    // Get *_dem.png from a zip file.
    if (isZip(mapID))
    {
        wxString file = findZipDataFile(wxT("_dem\\.png$"));
        if (file != wxEmptyString)
        {
            getZipData(buf, mapID, file);
        }
    }
    // Get *_dem.png from a folder.
    else
    {
        wxString path = getCurrentModDir() + wxFileName::GetPathSeparator() + mapToken;
        readFileData(buf, findModDataFile(path, wxT("_dem\\.png$")));
    }

    wxMemoryInputStream in(buf.GetData(), buf.GetDataLen());
    if (in.IsOk())
    {
        wxImage png(in, wxBITMAP_TYPE_PNG);
        if (png.IsOk())
        {
            width = mapSizes[png.GetWidth()];
            height = mapSizes[png.GetHeight()];

            if (width == 0 || height == 0)
                return false;
            else
                return true;
        }
    }

    return false;
}

wxString DataHandler::getCurrentModDir()
{
    if (setup->selectedGameId == FS2011)
        return getCurrentFS11ModDir();
    else if (setup->selectedGameId == FS2013)
        return getCurrentFS13ModDir();

    // Game not found. Return empty string since we can't find anything.
    // This should never happen but is here in case something went wrong.
    return wxEmptyString;
}

wxString DataHandler::getCurrentFS11ModDir()
{
    wxString xmlFile = setup->getSavegamePath() + wxFileName::GetPathSeparator() + wxT("savegames.xml");
    if (wxFileExists(xmlFile))
    {
        wxXmlDocument xml;
        wxXmlNode *root;

        xml.Load(xmlFile);

        root = xml.GetRoot();
        if (xml.IsOk() && root->GetName() == wxT("savegames"))
        {
            wxXmlNode *child = getXmlElement(root, wxT("settings.modsDirectoryOverride"));
            if (child)
            {
                wxString isActive = child->GetPropVal(wxT("active"), wxT("false"));
                if (isActive == wxT("true"))
                {
                    wxDir dir(child->GetPropVal(wxT("directory"), wxEmptyString));
                    if (dir.Exists(dir.GetName()))
                        return dir.GetName();
                }
                else
                    return setup->getSavegamePath() + wxFileName::GetPathSeparator() + wxT("mods");
            }
        }
    }

    // Didn't find anything, so return an empty string
    return wxEmptyString;
}

wxString DataHandler::getCurrentFS13ModDir()
{
    wxString xmlFile = setup->getSavegamePath() + wxFileName::GetPathSeparator() + wxT("gameSettings.xml");
    if (wxFileExists(xmlFile))
    {
        wxXmlDocument xml;
        wxXmlNode *root;

        xml.Load(xmlFile);

        root = xml.GetRoot();
        if (xml.IsOk() && root->GetName() == wxT("gameSettings"))
        {
            wxXmlNode *child = getXmlElement(root, wxT("modsDirectoryOverride"));
            wxString isActive = child->GetPropVal(wxT("active"), wxT("false"));
            if (isActive == wxT("true"))
            {
                wxDir dir(child->GetPropVal(wxT("directory"), wxEmptyString));
                if (dir.Exists(dir.GetName()))
                    return dir.GetName();
            }
            else
                return setup->getSavegamePath() + wxFileName::GetPathSeparator() + wxT("mods");

        }
    }

    // Didn't find anything, so return an empty string
    return wxEmptyString;
}

bool DataHandler::isMod(wxString mapID)
{
    return mapID != wxT("Map01");
}

bool DataHandler::readFileData(wxMemoryBuffer &buf, wxString file)
{
   std::auto_ptr<wxZipEntry> entry;

    wxFFileInputStream xmlFile(file);

    unsigned char tempbuf[BUFSIZE];

    while( xmlFile.CanRead() && !xmlFile.Eof() )
    {
        xmlFile.Read(tempbuf, BUFSIZE);
        size_t readlen = xmlFile.LastRead();
        if ( readlen>0 )
        {
            buf.AppendData(tempbuf, readlen);
        }
    }

    if (buf.GetDataLen() > 0)
    {
        return true;
    }

    return false;
}

////////////////////////////////////////////////////////////////////////
// XML HANDLING
////////////////////////////////////////////////////////////////////////
wxString DataHandler::getXmlStringData(wxMemoryBuffer &buf)
{
    wxString utf8((const char*) buf.GetData(), wxConvUTF8, buf.GetDataLen());
    if (utf8 != wxEmptyString)
        return utf8;

    wxString ISO8859_1((const char*) buf.GetData(), wxConvISO8859_1, buf.GetDataLen());
    if (ISO8859_1 != wxEmptyString)
        return ISO8859_1;

    return wxEmptyString;
}

wxXmlNode* DataHandler::getXmlElement(wxXmlNode *root, wxString elementToFind)
{
    wxStringTokenizer tkz(elementToFind, wxT("."));
    wxString searchStr  = tkz.GetNextToken();

    wxString attr       = wxEmptyString;
    wxString val        = wxEmptyString;
    bool hasAttribute   = false;

    if (searchStr.Find(wxT("->")) != wxNOT_FOUND)
    {
        wxStringTokenizer tkz2(searchStr, wxT("->"));
        // Set the actually search string
        searchStr = tkz2.GetNextToken();

        // Find the attribute name and value to search for.
        wxStringTokenizer tkz3(tkz2.GetNextToken(), wxT("="));
        attr = tkz3.GetNextToken();
        val  = tkz3.GetNextToken();

        hasAttribute = true;
    }

    if (searchStr != wxEmptyString)
    {
        wxXmlNode *child = root->GetChildren();
        while (child) {
            wxString propVal = wxEmptyString;
            if (child->HasProp(attr))
                child->GetPropVal(attr, &propVal);

            if (child->GetName() == searchStr && (!hasAttribute || (hasAttribute && propVal == val))) {
                if (tkz.HasMoreTokens())
                {
                    wxArrayString searchList;
                    searchList.Alloc(tkz.CountTokens());

                    while ( tkz.HasMoreTokens() )
                    {
                        wxString str = tkz.GetNextToken();
                        if (str != wxEmptyString)
                            searchList.Add(str);
                    }

                    return getXmlElement(child, buildSearchString(searchList,wxT(".")));
                }
                else
                {
                    return child;
                }
            }

            child = child->GetNext();
        }
    }

    return NULL;
}

bool DataHandler::XmlElementExists(wxXmlNode *root, wxString elementToFind)
{
    return (getXmlElement(root, elementToFind) != NULL);
}

long DataHandler::getNumOfXmlElements(wxXmlNode *root)
{
    long num = 0;

    wxXmlNode *child = root->GetChildren();

    while (child) {
        num++;
        child = child->GetNext();
    }

    return num;
}

bool DataHandler::hasChildren(wxXmlNode *root)
{
    return (root->GetChildren() != NULL);
}

////////////////////////////////////////////////////////////////////////
// ZIP HANDLING
////////////////////////////////////////////////////////////////////////
bool DataHandler::isZip(wxString mapID)
{
    wxStringTokenizer tkz(mapID, wxT("."));
    wxString name = tkz.GetNextToken(); // Only gets the first token, since we don't need the other one in this function

    return wxFileExists(getCurrentModDir() + wxFileName::GetPathSeparator() + name + wxT(".zip"));
}

wxString DataHandler::getZipFile(wxString mapID)
{
    wxStringTokenizer tkz(mapID, wxT("."));
    wxString name = tkz.GetNextToken(); // Only gets the first token, since we don't need the other one in this function

    return getCurrentModDir() + wxFileName::GetPathSeparator() + name + wxT(".zip");
}

wxArrayString DataHandler::getZipInfo(wxString mapID)
{
    std::auto_ptr<wxZipEntry> entry;

    wxFFileInputStream in(getZipFile(mapID));
    wxZipInputStream zip(in);
    wxArrayString out;
    out.Clear();

    while (entry.reset(zip.GetNextEntry()), entry.get() != NULL)
    {
        out.Add(entry->GetName());
    }

    return out;
}

void DataHandler::updateZipDataFileList(wxString mapID)
{
    zipDataFileList.Clear();
    zipDataFileList = getZipInfo(mapID);
}

bool DataHandler::zipDataFileExists(wxString file)
{
    for (int i = 0; i < (int)zipDataFileList.Count(); i++)
    {
        // Check if the data file is in the zip file and return true if it's found.
        if (zipDataFileList[i] == file)
            return true;
    }

    return false; // We didn't find the file so we return false.
}

wxString DataHandler::getZipDataFile(wxArrayString files)
{
    for (int i = 0; i < (int)files.Count(); i++)
    {
        if (zipDataFileExists(files[i]))
            return files[i];
    }

    return wxEmptyString;
}

bool DataHandler::getZipData(wxMemoryBuffer &buf, wxString mapID, wxString dataFile)
{
    std::auto_ptr<wxZipEntry> entry;

    wxFFileInputStream in(getZipFile(mapID));
    wxZipInputStream zip(in);

    do { entry.reset(zip.GetNextEntry()); } while (entry.get() != NULL && entry->GetName() != dataFile);

    if (entry.get() != NULL && !entry.get()->IsDir())
    {
        zip.OpenEntry(*entry.get());

        unsigned char tempbuf[BUFSIZE];

        while( zip.CanRead() && !zip.Eof() )
        {
            zip.Read(tempbuf, BUFSIZE);
            size_t readlen = zip.LastRead();
            if ( readlen>0 )
            {
                buf.AppendData(tempbuf, readlen);
            }
        }

        if (buf.GetDataLen() > 0)
        {
            return true;
        }
    }

    return false;
}

wxString DataHandler::findZipDataFile(wxString regEx)
{
    wxRegEx fileToken(regEx, wxRE_EXTENDED | wxRE_ICASE);

    if (fileToken.IsValid())
    {
        for (int i = 0; i < (int)zipDataFileList.Count(); i++)
        {
            if (fileToken.Matches(zipDataFileList[i]))
                return zipDataFileList[i];
        }
    }

    return wxEmptyString;
}
