#ifndef XMLPARSER_H
#define XMLPARSER_H

#include <wx/wx.h>
#include <wx/xml/xml.h>
#include "Variables.h"
#include <map>

class Settings; // Dummy

class DataHandler
{
    public: // Functions
        DataHandler(Settings *settings);
        ~DataHandler();

        bool getSavegames(); // Update the list of savegames from the current selected game

        bool loadSavegame();
        bool saveSavegame();

    public: // Variables
        Savegames *savegameList;

    protected: // Functions
        wxString buildSearchString(wxArrayString arrayStr, wxString tokenizer);
        wxString findModDataFile(wxString path, wxString regEx);
        wxString getMapName(wxString mapID);
        wxString getModMapName(wxString mapID);
        wxString getMapFile(wxString mapID);
        wxString getModMapFile(wxString mapID);
        bool     getMapSize(int &width, int &height, wxString mapID);
        bool     getModMapSize(int &width, int &height, wxString mapID);
        wxString getCurrentModDir();
        wxString getCurrentFS11ModDir();
        wxString getCurrentFS13ModDir();
        bool     isMod(wxString mapID);
        bool     readFileData(wxMemoryBuffer &buf, wxString file);

        // XML Handling
        wxString    getXmlStringData(wxMemoryBuffer &buf);
        wxXmlNode*  getXmlElement(wxXmlNode *root, wxString elementToFind);
        bool        XmlElementExists(wxXmlNode *root, wxString elementToFind);
        long        getNumOfXmlElements(wxXmlNode *root);
        bool        hasChildren(wxXmlNode *root);

        // Zip Handling
        bool            isZip(wxString mapID);
        wxString        getZipFile(wxString mapID);
        void            updateZipDataFileList(wxString mapID);
        wxArrayString   getZipInfo(wxString mapID);
        bool            zipDataFileExists(wxString file);
        wxString        getZipDataFile(wxArrayString files);
        bool            getZipData(wxMemoryBuffer &buf, wxString mapID, wxString file);
        wxString        findZipDataFile(wxString regEx);


    private:
        Settings        *setup;
        wxArrayString   zipDataFileList;

        std::map<int, int> mapSizes;
};

#endif // XMLPARSER_H
