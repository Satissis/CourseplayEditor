/***************************************************************
 * Name:      Courseplay_EditorMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Claus G. Pedersen aka Satis (satissis@gmail.com)
 * Created:   2013-06-08
 * Copyright: Claus G. Pedersen aka Satis (https://github.com/Satissis/CourseplayEditor)
 * License:
 **************************************************************/

#include "Courseplay_EditorMain.h"
#include <wx/msgdlg.h>

//(*InternalHeaders(Courseplay_EditorFrame)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(Courseplay_EditorFrame)
const long Courseplay_EditorFrame::ID_TLB1_BTN_NEW = wxNewId();
const long Courseplay_EditorFrame::TLB_1 = wxNewId();
const long Courseplay_EditorFrame::ID_Main_Window = wxNewId();
const long Courseplay_EditorFrame::ID_File_Load = wxNewId();
const long Courseplay_EditorFrame::ID_File_Save = wxNewId();
const long Courseplay_EditorFrame::idMenuQuit = wxNewId();
const long Courseplay_EditorFrame::idMenuAbout = wxNewId();
const long Courseplay_EditorFrame::ID_STATUSBAR1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(Courseplay_EditorFrame,wxFrame)
    //(*EventTable(Courseplay_EditorFrame)
    //*)
END_EVENT_TABLE()

Courseplay_EditorFrame::Courseplay_EditorFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(Courseplay_EditorFrame)
    wxMenuItem* MenuItem2;
    wxMenuItem* MenuItem1;
    wxMenu* Menu1;
    wxMenuBar* MenuBar1;
    wxMenu* Menu2;

    Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("id"));
    SetClientSize(wxSize(677,408));
    AuiManager1 = new wxAuiManager(this, wxAUI_MGR_DEFAULT);
    Aui_Toolbar1 = new wxAuiToolBar(this, TLB_1, wxPoint(55,48), wxSize(236,24), wxAUI_TB_DEFAULT_STYLE);
    Aui_Toolbar1->AddTool(ID_TLB1_BTN_NEW, _("Add"), wxNullBitmap, wxNullBitmap, wxITEM_NORMAL, _("Add new waypoint"), _("Add new waypoint to the end of the route"), NULL);
    Aui_Toolbar1->Realize();
    AuiManager1->AddPane(Aui_Toolbar1, wxAuiPaneInfo().Name(_T("TLB_1")).ToolbarPane().Caption(_("Pane caption")).CloseButton(false).Layer(10).Top().BestSize(wxSize(236,24)).Gripper());
    mainWindow = new wxScrolledWindow(this, ID_Main_Window, wxPoint(367,283), wxDefaultSize, wxSTATIC_BORDER|wxVSCROLL|wxHSCROLL|wxALWAYS_SHOW_SB|wxFULL_REPAINT_ON_RESIZE, _T("ID_Main_Window"));
    AuiManager1->AddPane(mainWindow, wxAuiPaneInfo().Name(_T("mainWindow")).CenterPane().Caption(_("Pane caption")));
    AuiManager1->Update();
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem3 = new wxMenuItem(Menu1, ID_File_Load, _("&Load Route"), _("Load route from a savegame"), wxITEM_NORMAL);
    Menu1->Append(MenuItem3);
    MenuItem4 = new wxMenuItem(Menu1, ID_File_Save, _("&Save Routes"), _("Save the loaded routes"), wxITEM_NORMAL);
    Menu1->Append(MenuItem4);
    MenuItem4->Enable(false);
    MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("E&xit\tAlt-F4"), _("Close Courseplay Editor"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuBar1->Append(Menu1, _("&File"));
    Menu2 = new wxMenu();
    MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    MenuBar1->Append(Menu2, _("Help"));
    SetMenuBar(MenuBar1);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, wxST_SIZEGRIP|wxFULL_REPAINT_ON_RESIZE, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[3] = { -1, 150, 150 };
    int __wxStatusBarStyles_1[3] = { wxSB_NORMAL, wxSB_NORMAL, wxSB_NORMAL };
    StatusBar1->SetFieldsCount(3,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(3,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);

    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&Courseplay_EditorFrame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&Courseplay_EditorFrame::OnAbout);
    Connect(wxID_ANY,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&Courseplay_EditorFrame::OnClose);
    //*)
}

Courseplay_EditorFrame::~Courseplay_EditorFrame()
{
    //(*Destroy(Courseplay_EditorFrame)
    //*)
}

void Courseplay_EditorFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void Courseplay_EditorFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}

void Courseplay_EditorFrame::OnClose(wxCloseEvent& event)
{
    Destroy();
}
