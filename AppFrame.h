#ifndef APPFRAME_H
#define APPFRAME_H

#define CP_EDITOR_VERSION wxT("0.0.1")

#include "wx/wx.h"

enum ID_List
{
	///////////////////////////////////////
	// Menu Bar Id's
	///////////////////////////////////////
	
	// File
	MFILE_OPEN = 200,
	MFILE_SAVE,
	MFILE_SETTINGS,
	MFILE_EXIT,
	
	// Edit
	MEDIT_UNDO,
	MEDIT_REDO,

	// Tools
	MTOOL_MOVE,

	// Help
	MHELP_ABOUT,
};

class AppFrame : public wxFrame
{
public:
	AppFrame(const wxString &title, const wxPoint &pos, const wxSize &size);

	void OnHelpMenuAbout(wxCommandEvent &event);
	void OnFileMenuExit(wxCommandEvent &event);
	
private:

private:
	DECLARE_EVENT_TABLE()
};

#endif