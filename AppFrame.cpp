#include <iostream>

// Include precompiled headers
#include "stdwx.h"

// AppFrame class
#include "AppFrame.h"

// Event Handler
BEGIN_EVENT_TABLE(AppFrame, wxFrame)
	EVT_MENU	( MHELP_ABOUT, AppFrame::OnHelpMenuAbout )
	EVT_MENU	( MFILE_EXIT, AppFrame::OnFileMenuExit )
END_EVENT_TABLE()

// The main frame app
AppFrame::AppFrame(const wxString &title, const wxPoint &pos, const wxSize &size) 
:  wxFrame((wxFrame *)NULL, -1, title, pos, size)
{
	//--------------------------------------
	// Top Menu
	//--------------------------------------
	// Create a menu bar
	wxMenuBar *menu_bar = new wxMenuBar;
	
	// Create "File" dropdown menu
	wxMenu *menuFile = new wxMenu;
	// Add elements to "File" menu
	menuFile->Append(MFILE_OPEN, "&Open");
	menuFile->Append(MFILE_SAVE, "&Save");
	menuFile->AppendSeparator();
	menuFile->Append(MFILE_SETTINGS, "&Settings");
	menuFile->AppendSeparator();
	menuFile->Append(MFILE_EXIT, "E&xit");

	// Create "Edit" dropdown menu
	wxMenu *menuEdit = new wxMenu;
	// Add elements to "Edit" menu
	menuEdit->Append(MEDIT_UNDO, "&Undo");
	menuEdit->Append(MEDIT_REDO, "&Redo");
	
	// Create "Tools" dropdown menu
	wxMenu *menuTools = new wxMenu;
	// Add elements to "Tools" menu
	menuTools->Append(MTOOL_MOVE, "&Move");
	
	// Create "Help" dropdown menu
	wxMenu *menuHelp = new wxMenu;
	// Add elements to "Help" menu
	menuHelp->Append(MHELP_ABOUT, "About");
	
	// Add menus to menu bar
	menu_bar->Append(menuFile, "&File");
	menu_bar->Append(menuEdit, "&Edit");
	menu_bar->Append(menuTools, "&Tools");
	menu_bar->Append(menuHelp, "Help");
	
	// Show the menu bar
	SetMenuBar(menu_bar);
}

// Show about help info
void AppFrame::OnHelpMenuAbout(wxCommandEvent &event)
{
	wxString con = wxT("");
	wxMessageBox(
		wxT("Courseplay Editor\n")+ con +
		wxT("Version: ") + con + CP_EDITOR_VERSION + con + wxT("\n") + con + 
		wxT("By: Satis")
		, wxT("About Courseplay Editor"));
}

// Exit the program
void AppFrame::OnFileMenuExit(wxCommandEvent &event)
{
	Close(true);
}