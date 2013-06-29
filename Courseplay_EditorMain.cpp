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
#include "Settings.h"
#include "version.h"

//(*InternalHeaders(Courseplay_EditorFrame)
#include <wx/artprov.h>
#include <wx/bitmap.h>
#include <wx/intl.h>
#include <wx/image.h>
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
const long Courseplay_EditorFrame::ID_TLB1_BTN_INSERT = wxNewId();
const long Courseplay_EditorFrame::ID_TLB1_BTN_DELETE = wxNewId();
const long Courseplay_EditorFrame::ID_TLB1_BTN_FILL = wxNewId();
const long Courseplay_EditorFrame::ID_TOOL_UNDO = wxNewId();
const long Courseplay_EditorFrame::ID_TOOL_REDO = wxNewId();
const long Courseplay_EditorFrame::TLB_1 = wxNewId();
const long Courseplay_EditorFrame::ID_Main_Window = wxNewId();
const long Courseplay_EditorFrame::ID_COURSELISTBOX = wxNewId();
const long Courseplay_EditorFrame::BTN_SELECTALLCOURSE = wxNewId();
const long Courseplay_EditorFrame::BTN_MOVECOURSEUP = wxNewId();
const long Courseplay_EditorFrame::BTN_MOVECOURSEDOWN = wxNewId();
const long Courseplay_EditorFrame::ID_STATICTEXT1 = wxNewId();
const long Courseplay_EditorFrame::TXT_COURSENAME = wxNewId();
const long Courseplay_EditorFrame::ID_PANEL1 = wxNewId();
const long Courseplay_EditorFrame::ID_STATICTEXT2 = wxNewId();
const long Courseplay_EditorFrame::ID_TEXTCTRL1 = wxNewId();
const long Courseplay_EditorFrame::ID_STATICTEXT3 = wxNewId();
const long Courseplay_EditorFrame::ID_TEXTCTRL2 = wxNewId();
const long Courseplay_EditorFrame::ID_STATICTEXT5 = wxNewId();
const long Courseplay_EditorFrame::ID_TEXTCTRL3 = wxNewId();
const long Courseplay_EditorFrame::ID_STATICTEXT4 = wxNewId();
const long Courseplay_EditorFrame::ID_TEXTCTRL4 = wxNewId();
const long Courseplay_EditorFrame::ID_CHECKBOX1 = wxNewId();
const long Courseplay_EditorFrame::ID_CHECKBOX2 = wxNewId();
const long Courseplay_EditorFrame::ID_CHECKBOX3 = wxNewId();
const long Courseplay_EditorFrame::ID_PANEL2 = wxNewId();
const long Courseplay_EditorFrame::ID_TLB2_BTN_GAME_SELECT = wxNewId();
const long Courseplay_EditorFrame::ID_TLB2_COMBOX_SAVEGAMESELECT = wxNewId();
const long Courseplay_EditorFrame::ID_TLB2_BTN_RELOAD = wxNewId();
const long Courseplay_EditorFrame::ID_TLB2_BTN_SAVESAVEGAME = wxNewId();
const long Courseplay_EditorFrame::TLB_2 = wxNewId();
const long Courseplay_EditorFrame::idMenuQuit = wxNewId();
const long Courseplay_EditorFrame::ID_EDIT_Undo = wxNewId();
const long Courseplay_EditorFrame::ID_EDIT_Redo = wxNewId();
const long Courseplay_EditorFrame::ID_EDIT_Settings = wxNewId();
const long Courseplay_EditorFrame::ID_HELP_Manual = wxNewId();
const long Courseplay_EditorFrame::idMenuAbout = wxNewId();
const long Courseplay_EditorFrame::ID_STATUSBAR1 = wxNewId();
//*)

const long Courseplay_EditorFrame::Game_FarmingSimulator2011    = wxNewId();
const long Courseplay_EditorFrame::Game_FarmingSimulator2013    = wxNewId();
const long Courseplay_EditorFrame::RightClickMenu_Add           = wxNewId();
const long Courseplay_EditorFrame::RightClickMenu_Insert        = wxNewId();
const long Courseplay_EditorFrame::RightClickMenu_Delete        = wxNewId();
const long Courseplay_EditorFrame::RightClickMenu_FillOut       = wxNewId();

#define MENU_ICON_SIZE  16
#define TB_ICON_SIZE    16

BEGIN_EVENT_TABLE(Courseplay_EditorFrame,wxFrame)
    //(*EventTable(Courseplay_EditorFrame)
    //*)
    EVT_AUITOOLBAR_TOOL_DROPDOWN(ID_TLB1_BTN_FILL,          Courseplay_EditorFrame::OnBtnFillOutDropdown)
    EVT_AUITOOLBAR_TOOL_DROPDOWN(ID_TLB2_BTN_GAME_SELECT,   Courseplay_EditorFrame::OnBtnGameSelectDropdown)

    EVT_MENU                    (Game_FarmingSimulator2011, Courseplay_EditorFrame::OnGameFS2011Select)
    EVT_MENU                    (Game_FarmingSimulator2013, Courseplay_EditorFrame::OnGameFS2013Select)

    EVT_MENU                    (RightClickMenu_Add,        Courseplay_EditorFrame::OnRCMAddSelect)
    EVT_MENU                    (RightClickMenu_Insert,     Courseplay_EditorFrame::OnRCMInsertSelect)
    EVT_MENU                    (RightClickMenu_Delete,     Courseplay_EditorFrame::OnRCMDeleteSelect)
    EVT_MENU                    (RightClickMenu_FillOut,    Courseplay_EditorFrame::OnRCMFillSelect)
END_EVENT_TABLE()

Courseplay_EditorFrame::Courseplay_EditorFrame(wxWindow* parent,wxWindowID id)
{
    // set default variables
    courseListSelectedAll   = false;
    rightClickMenuOpen      = false;
    courseListSelectedIndex = -1;
    mousePosX               = 0;
    mousePosY               = 0;
    for (int i = 0; i < NumOfFSGames; i++)
    {
        TbIcon_Games[i] = wxNullBitmap;
    }

    // Create images to use.
    wxBitmap MenuIcon_Exit      = res.GetBitmap(wxT("btn_Exit"),        MENU_ICON_SIZE, MENU_ICON_SIZE);
    wxBitmap MenuIcon_Undo      = res.GetBitmap(wxT("btn_Undo"),        MENU_ICON_SIZE, MENU_ICON_SIZE);
    wxBitmap MenuIcon_Redo      = res.GetBitmap(wxT("btn_Redo"),        MENU_ICON_SIZE, MENU_ICON_SIZE);
    wxBitmap MenuIcon_Settings  = res.GetBitmap(wxT("btn_Settings"),    MENU_ICON_SIZE, MENU_ICON_SIZE);
    wxBitmap MenuIcon_Help      = res.GetBitmap(wxT("btn_Help"),        MENU_ICON_SIZE, MENU_ICON_SIZE);

    wxBitmap TbIcon_Reload      = res.GetBitmap(wxT("btn_Reload"),  TB_ICON_SIZE, TB_ICON_SIZE);
    wxBitmap TbIcon_Save        = res.GetBitmap(wxT("btn_Save"),    TB_ICON_SIZE, TB_ICON_SIZE);
    TbIcon_Add                  = res.GetBitmap(wxT("btn_Add"),     TB_ICON_SIZE, TB_ICON_SIZE);
    TbIcon_Insert               = res.GetBitmap(wxT("btn_Insert"),  TB_ICON_SIZE, TB_ICON_SIZE);
    TbIcon_Delete               = res.GetBitmap(wxT("btn_Delete"),  TB_ICON_SIZE, TB_ICON_SIZE);
    TbIcon_FillOut              = res.GetBitmap(wxT("btn_FillOut"), TB_ICON_SIZE, TB_ICON_SIZE);
    TbIcon_Games[FS2011]        = res.GetBitmap(wxT("FS2011"),      TB_ICON_SIZE, TB_ICON_SIZE);
    TbIcon_Games[FS2013]        = res.GetBitmap(wxT("FS2013"),      TB_ICON_SIZE, TB_ICON_SIZE);

    // Create a input text validator
    wxArrayString validatorIncludeList;
    validatorIncludeList.Alloc(127-32);
    // characters avalible in validator: 32, 40, 41, 43, 45-57, 65-90, 97-122
    validatorIncludeList.Add(wxString::Format(wxT("%c"), 32)); // " " space
    validatorIncludeList.Add(wxString::Format(wxT("%c"), 40)); // "("
    validatorIncludeList.Add(wxString::Format(wxT("%c"), 41)); // ")"
    validatorIncludeList.Add(wxString::Format(wxT("%c"), 43)); // "+"
    for (int i = 45; i <= 57; i++)  validatorIncludeList.Add(wxString::Format(wxT("%c"), i)); // "- . / 0-9"
    for (int i = 65; i <= 90; i++)  validatorIncludeList.Add(wxString::Format(wxT("%c"), i)); // "A-Z"
    for (int i = 97; i <= 122; i++) validatorIncludeList.Add(wxString::Format(wxT("%c"), i)); // "a-z"
    wxTextValidator courseNameValidator(wxFILTER_INCLUDE_CHAR_LIST);
    courseNameValidator.SetIncludes(validatorIncludeList);
    courseNameValidator.SetBellOnError();



    //(*Initialize(Courseplay_EditorFrame)
    wxBoxSizer* BoxSizer4;
    wxMenuItem* MenuItem2;
    wxMenuItem* MenuItem1;
    wxBoxSizer* BoxSizer2;
    wxMenu* Menu1;
    wxGridSizer* GridSizer1;
    wxBoxSizer* BoxSizer1;
    wxMenuBar* MenuBar1;
    wxFlexGridSizer* FlexGridSizer1;
    wxBoxSizer* BoxSizer3;
    wxMenu* Menu2;

    Create(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    SetClientSize(wxSize(1066,582));
    SetIcon(wxICON(appIcon));
    SetLabel(wxString::Format(_("Courseplay Editor - v%d.%d.%d"), EditorVersion::MAJOR, EditorVersion::MINOR, EditorVersion::BUILD));
    m_mgr = new wxAuiManager(this, wxAUI_MGR_TRANSPARENT_HINT|wxAUI_MGR_DEFAULT);
    AuiTools1 = new wxAuiToolBar(this, TLB_1, wxPoint(55,48), wxDefaultSize, wxAUI_TB_DEFAULT_STYLE);
    AuiTools1->AddTool(ID_TLB1_BTN_NEW, _("Add"), TbIcon_Add, wxNullBitmap, wxITEM_NORMAL, _("Add new waypoint."), _("Add new waypoint to the end of the route"), NULL);
    AuiTools1->AddTool(ID_TLB1_BTN_INSERT, _("Insert"), TbIcon_Insert, wxNullBitmap, wxITEM_NORMAL, _("Insert waypoint."), _("Insert a waypoint before the selected waypoint."), NULL);
    AuiTools1->AddTool(ID_TLB1_BTN_DELETE, _("Delete Waypoint"), TbIcon_Delete, wxNullBitmap, wxITEM_NORMAL, _("Delete selected waypoint."), wxEmptyString, NULL);
    AuiTools1->AddTool(ID_TLB1_BTN_FILL, _("Fill Out"), TbIcon_FillOut, wxNullBitmap, wxITEM_NORMAL, _("Fill Out"), _("Insert waypoints between the selected waypoint to the previus waypoint with a given distance."), NULL);
    AuiTools1->SetToolDropDown(ID_TLB1_BTN_FILL, true);
    AuiTools1->AddSeparator();
    AuiTools1->AddTool(ID_TOOL_UNDO, _("Undo"), MenuIcon_Undo, wxNullBitmap, wxITEM_NORMAL, _("Undo"), wxEmptyString, NULL);
    AuiTools1->AddTool(ID_TOOL_REDO, _("Redo"), MenuIcon_Redo, wxNullBitmap, wxITEM_NORMAL, _("Redo"), wxEmptyString, NULL);
    AuiTools1->Realize();
    m_mgr->AddPane(AuiTools1, wxAuiPaneInfo().Name(_T("TLB_1")).ToolbarPane().CloseButton(false).Layer(10).Top().LeftDockable(false).RightDockable(false).Gripper());
    mainWindow = new wxScrolledWindow(this, ID_Main_Window, wxPoint(367,283), wxDefaultSize, wxSTATIC_BORDER|wxVSCROLL|wxHSCROLL|wxALWAYS_SHOW_SB|wxFULL_REPAINT_ON_RESIZE, _T("ID_Main_Window"));
    m_mgr->AddPane(mainWindow, wxAuiPaneInfo().Name(_T("mainWindow")).CenterPane());
    panelCourseList = new wxPanel(this, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxSIMPLE_BORDER, _T("ID_PANEL1"));
    BoxSizer1 = new wxBoxSizer(wxVERTICAL);
    courseList = new wxCheckListBox(panelCourseList, ID_COURSELISTBOX, wxDefaultPosition, wxSize(200,124), 0, 0, wxVSCROLL|wxALWAYS_SHOW_SB, wxDefaultValidator, _T("ID_COURSELISTBOX"));
    courseList->Append(_("Course 1"));
    courseList->Append(_("Course 2"));
    courseList->Append(_("Course 3"));
    courseList->Append(_("Course 4"));
    courseList->Append(_("Course 5"));
    courseList->Append(_("Course 6"));
    courseList->Append(_("Course 7"));
    courseList->Append(_("Course 8"));
    courseList->Append(_("Course 9"));
    courseList->Append(_("Course 10"));
    BoxSizer1->Add(courseList, 1, wxTOP|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
    BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
    selectAllCourse = new wxButton(panelCourseList, BTN_SELECTALLCOURSE, _("(Un)Select All"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("BTN_SELECTALLCOURSE"));
    selectAllCourse->SetToolTip(_("Select or unselect all courses to show the courses on the map or not."));
    selectAllCourse->SetHelpText(_("Select or unselect all courses to show the courses on the map or not."));
    BoxSizer2->Add(selectAllCourse, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer2->Add(15,20,1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    moveCourseUp = new wxButton(panelCourseList, BTN_MOVECOURSEUP, _("Up"), wxDefaultPosition, wxSize(23,23), 0, wxDefaultValidator, _T("BTN_MOVECOURSEUP"));
    moveCourseUp->Disable();
    moveCourseUp->SetToolTip(_("Move course up in the list."));
    moveCourseUp->SetHelpText(_("Move course up in the list."));
    BoxSizer2->Add(moveCourseUp, 0, wxRIGHT|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 2);
    moveCourseDown = new wxButton(panelCourseList, BTN_MOVECOURSEDOWN, _("Dn"), wxDefaultPosition, wxSize(23,23), 0, wxDefaultValidator, _T("BTN_MOVECOURSEDOWN"));
    moveCourseDown->Disable();
    BoxSizer2->Add(moveCourseDown, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer1->Add(BoxSizer2, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
    StaticText1 = new wxStaticText(panelCourseList, ID_STATICTEXT1, _("Course Name:"), wxDefaultPosition, wxSize(69,16), 0, _T("ID_STATICTEXT1"));
    BoxSizer3->Add(StaticText1, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    courseName = new wxTextCtrl(panelCourseList, TXT_COURSENAME, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, courseNameValidator, _T("TXT_COURSENAME"));
    courseName->SetMaxLength(20);
    courseName->Disable();
    courseName->SetToolTip(_("Rename a course by changin it here after selecting it on the list."));
    BoxSizer3->Add(courseName, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer1->Add(BoxSizer3, 0, wxBOTTOM|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    panelCourseList->SetSizer(BoxSizer1);
    BoxSizer1->Fit(panelCourseList);
    BoxSizer1->SetSizeHints(panelCourseList);
    m_mgr->AddPane(panelCourseList, wxAuiPaneInfo().Name(_T("PaneName")).Caption(_("Course List")).CaptionVisible().CloseButton(false).Right().TopDockable(false).BottomDockable(false).Resizable(false));
    panelWpProp = new wxPanel(this, ID_PANEL2, wxPoint(952,334), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL2"));
    BoxSizer4 = new wxBoxSizer(wxVERTICAL);
    FlexGridSizer1 = new wxFlexGridSizer(4, 2, 0, 0);
    FlexGridSizer1->AddGrowableCol(1);
    StaticText2 = new wxStaticText(panelWpProp, ID_STATICTEXT2, _("Pos X"), wxDefaultPosition, wxSize(29,13), wxST_NO_AUTORESIZE, _T("ID_STATICTEXT2"));
    FlexGridSizer1->Add(StaticText2, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    wpPropPosX = new wxTextCtrl(panelWpProp, ID_TEXTCTRL1, wxEmptyString, wxDefaultPosition, wxSize(150,-1), 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
    wpPropPosX->Disable();
    FlexGridSizer1->Add(wpPropPosX, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    StaticText3 = new wxStaticText(panelWpProp, ID_STATICTEXT3, _("Pos Y"), wxDefaultPosition, wxDefaultSize, wxST_NO_AUTORESIZE, _T("ID_STATICTEXT3"));
    FlexGridSizer1->Add(StaticText3, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    wpPropPosY = new wxTextCtrl(panelWpProp, ID_TEXTCTRL2, wxEmptyString, wxDefaultPosition, wxSize(150,-1), 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
    wpPropPosY->Disable();
    FlexGridSizer1->Add(wpPropPosY, 0, wxTOP|wxBOTTOM|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 2);
    StaticText5 = new wxStaticText(panelWpProp, ID_STATICTEXT5, _("Angle"), wxDefaultPosition, wxDefaultSize, wxST_NO_AUTORESIZE, _T("ID_STATICTEXT5"));
    FlexGridSizer1->Add(StaticText5, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    wpPropAngle = new wxTextCtrl(panelWpProp, ID_TEXTCTRL3, wxEmptyString, wxDefaultPosition, wxSize(150,-1), 0, wxDefaultValidator, _T("ID_TEXTCTRL3"));
    wpPropAngle->Disable();
    FlexGridSizer1->Add(wpPropAngle, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    StaticText4 = new wxStaticText(panelWpProp, ID_STATICTEXT4, _("Speed"), wxDefaultPosition, wxDefaultSize, wxST_NO_AUTORESIZE, _T("ID_STATICTEXT4"));
    FlexGridSizer1->Add(StaticText4, 0, wxTOP|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    wpPropSpeed = new wxTextCtrl(panelWpProp, ID_TEXTCTRL4, wxEmptyString, wxDefaultPosition, wxSize(150,-1), 0, wxDefaultValidator, _T("ID_TEXTCTRL4"));
    wpPropSpeed->Disable();
    FlexGridSizer1->Add(wpPropSpeed, 0, wxTOP|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 2);
    BoxSizer4->Add(FlexGridSizer1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    GridSizer1 = new wxGridSizer(0, 2, 0, 0);
    wpPropReverse = new wxCheckBox(panelWpProp, ID_CHECKBOX1, _("Reverse"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
    wpPropReverse->SetValue(false);
    wpPropReverse->SetToolTip(_("A reverse waypoint, meaning the the vehiche should reverse at this waypoint."));
    GridSizer1->Add(wpPropReverse, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    wpPropWaitPoint = new wxCheckBox(panelWpProp, ID_CHECKBOX2, _("Waiting Point"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX2"));
    wpPropWaitPoint->SetValue(false);
    wpPropWaitPoint->SetToolTip(_("Set the waypoint as an waiting point.\nThis can be used to set a field start or end point and more."));
    GridSizer1->Add(wpPropWaitPoint, 1, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    wpPropCrossing = new wxCheckBox(panelWpProp, ID_CHECKBOX3, _("Crossing"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX3"));
    wpPropCrossing->SetValue(false);
    wpPropCrossing->SetToolTip(_("Crossing is used when combining 2 or more courses.\na course needs to have this set at the starting waypoint and ending waypoint."));
    GridSizer1->Add(wpPropCrossing, 1, wxTOP|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer4->Add(GridSizer1, 0, wxBOTTOM|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    panelWpProp->SetSizer(BoxSizer4);
    BoxSizer4->Fit(panelWpProp);
    BoxSizer4->SetSizeHints(panelWpProp);
    m_mgr->AddPane(panelWpProp, wxAuiPaneInfo().Name(_T("wpProperty")).DefaultPane().Caption(_("Waypoint Info & Property")).CloseButton(false).Right().TopDockable(false).BottomDockable(false).Resizable(false));
    AuiTools2 = new wxAuiToolBar(this, TLB_2, wxPoint(222,10), wxDefaultSize, wxAUI_TB_DEFAULT_STYLE);
    SavegameSelect = new wxComboBox(AuiTools2, ID_TLB2_COMBOX_SAVEGAMESELECT, wxEmptyString, wxPoint(32,20), wxSize(170,21), 0, 0, wxCB_SIMPLE|wxCB_READONLY|wxCB_DROPDOWN, wxDefaultValidator, _T("ID_TLB2_COMBOX_SAVEGAMESELECT"));
    SavegameSelect->SetSelection( SavegameSelect->Append(_("No savegame loaded")) );
    SavegameSelect->Append(_("01: Hagstad"));
    SavegameSelect->Append(_("02: Two Rivers"));
    AuiTools2->AddTool(ID_TLB2_BTN_GAME_SELECT, _("Item label"), TbIcon_Games[FS2013], wxNullBitmap, wxITEM_NORMAL, _("Game Select"), wxEmptyString, NULL);
    AuiTools2->SetToolDropDown(ID_TLB2_BTN_GAME_SELECT, true);
    AuiTools2->AddControl(SavegameSelect, _("Item label"));
    AuiTools2->AddTool(ID_TLB2_BTN_RELOAD, _("Reload"), TbIcon_Reload, wxNullBitmap, wxITEM_NORMAL, _("Reload Savegame"), wxEmptyString, NULL);
    AuiTools2->AddTool(ID_TLB2_BTN_SAVESAVEGAME, _("Save"), TbIcon_Save, wxNullBitmap, wxITEM_NORMAL, _("Save Savegame"), wxEmptyString, NULL);
    AuiTools2->Realize();
    m_mgr->AddPane(AuiTools2, wxAuiPaneInfo().Name(_T("TLB_2")).ToolbarPane().CloseButton(false).Layer(10).Top().LeftDockable(false).RightDockable(false).Gripper());
    m_mgr->Update();
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("E&xit\tAlt-F4"), _("Close Courseplay Editor"), wxITEM_NORMAL);
    MenuItem1->SetBitmap(MenuIcon_Exit);
    Menu1->Append(MenuItem1);
    MenuBar1->Append(Menu1, _("&File"));
    Menu3 = new wxMenu();
    Undo = new wxMenuItem(Menu3, ID_EDIT_Undo, _("Undo\tCtrl-z"), _("Undo last action"), wxITEM_NORMAL);
    Undo->SetBitmap(MenuIcon_Undo);
    Menu3->Append(Undo);
    Redo = new wxMenuItem(Menu3, ID_EDIT_Redo, _("Redo\tCtrl-Shift-z"), _("Redo last action"), wxITEM_NORMAL);
    Redo->SetBitmap(MenuIcon_Redo);
    Menu3->Append(Redo);
    Menu3->AppendSeparator();
    CPE_Settings = new wxMenuItem(Menu3, ID_EDIT_Settings, _("Settings"), _("Settings"), wxITEM_NORMAL);
    CPE_Settings->SetBitmap(MenuIcon_Settings);
    Menu3->Append(CPE_Settings);
    MenuBar1->Append(Menu3, _("&Edit"));
    Menu2 = new wxMenu();
    Manual = new wxMenuItem(Menu2, ID_HELP_Manual, _("Manual (Not implemented)"), _("Manual on how Courseplay Editor works"), wxITEM_NORMAL);
    Manual->SetBitmap(MenuIcon_Help);
    Menu2->Append(Manual);
    Menu2->AppendSeparator();
    MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
    MenuItem2->SetBitmap(wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_HELP")),wxART_MENU));
    Menu2->Append(MenuItem2);
    MenuBar1->Append(Menu2, _("Help"));
    SetMenuBar(MenuBar1);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, wxST_SIZEGRIP|wxFULL_REPAINT_ON_RESIZE, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[3] = { -1, 150, 150 };
    int __wxStatusBarStyles_1[3] = { wxSB_NORMAL, wxSB_NORMAL, wxSB_NORMAL };
    StatusBar1->SetFieldsCount(3,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(3,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);
    Center();

    Connect(ID_TOOL_UNDO,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&Courseplay_EditorFrame::OnUndoSelected);
    Connect(ID_TOOL_REDO,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&Courseplay_EditorFrame::OnRedoSelected);
    mainWindow->Connect(wxEVT_RIGHT_DOWN,(wxObjectEventFunction)&Courseplay_EditorFrame::OnMainWindowRightDown,0,this);
    Connect(ID_COURSELISTBOX,wxEVT_COMMAND_CHECKLISTBOX_TOGGLED,(wxObjectEventFunction)&Courseplay_EditorFrame::OnCourseListToggled);
    Connect(ID_COURSELISTBOX,wxEVT_COMMAND_LISTBOX_SELECTED,(wxObjectEventFunction)&Courseplay_EditorFrame::OnCourseListSelect);
    Connect(BTN_SELECTALLCOURSE,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&Courseplay_EditorFrame::OnSelectAllCourseClick);
    Connect(BTN_MOVECOURSEUP,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&Courseplay_EditorFrame::OnMoveCourseUpClick);
    Connect(BTN_MOVECOURSEDOWN,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&Courseplay_EditorFrame::OnMoveCourseDownClick);
    Connect(TXT_COURSENAME,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&Courseplay_EditorFrame::OnCourseNameEnter);
    Connect(ID_CHECKBOX1,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&Courseplay_EditorFrame::OnWpPropReverseClick);
    Connect(ID_CHECKBOX2,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&Courseplay_EditorFrame::OnWpPropWaitPointClick);
    Connect(ID_CHECKBOX3,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&Courseplay_EditorFrame::OnWpPropCrossingClick);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&Courseplay_EditorFrame::OnQuit);
    Connect(ID_EDIT_Undo,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&Courseplay_EditorFrame::OnUndoSelected);
    Connect(ID_EDIT_Redo,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&Courseplay_EditorFrame::OnRedoSelected);
    Connect(ID_EDIT_Settings,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&Courseplay_EditorFrame::OnSettingsSelected);
    Connect(ID_HELP_Manual,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&Courseplay_EditorFrame::OnManualSelected);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&Courseplay_EditorFrame::OnAbout);
    Connect(wxID_ANY,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&Courseplay_EditorFrame::OnClose);
    //*)

    // Init settings.
    settings = new Settings(this, m_mgr);
    settings->loadLocale();

    settings->saveDefaultLayout(m_mgr->SavePerspective());

    if (settings->Exists(_T("GUI/layout")))
        m_mgr->LoadPerspective(settings->Read(_T("GUI/layout")));

    // Make sure all toolbar2 is up to date
    updateToolbar2();
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

    // TODO: Make new about page.
}

void Courseplay_EditorFrame::OnClose(wxCloseEvent& event)
{
    //delete wxConfigBase::Set((wxConfigBase *) NULL);
    // TODO: Save all settings before closing.
    settings->Write(_T("GUI/layout"), m_mgr->SavePerspective());

    delete settings;
    Destroy();
}void Courseplay_EditorFrame::OnCourseListToggled(wxCommandEvent& event)
{
    courseListSelectedAll = true;

    for (int i = 0; i < (int)courseList->GetCount(); i++)
    {
        if (!courseList->IsChecked(i))
        {
            courseListSelectedAll = false;
            break;
        }
    }

    // TODO: Update drawArea to show or hide the route.
}

void Courseplay_EditorFrame::OnCourseListSelect(wxCommandEvent& event)
{
    courseListSelectedIndex = event.GetInt();

    moveCourseUp->Enable(courseListSelectedIndex != 0);
    moveCourseDown->Enable(courseListSelectedIndex < (int)courseList->GetCount() - 1);

    courseName->SetValue(courseList->GetString(courseListSelectedIndex));

    if (!courseName->IsEnabled())
        courseName->Enable();
    courseName->SetFocus();
    courseName->SetInsertionPointEnd();

}

void Courseplay_EditorFrame::OnSelectAllCourseClick(wxCommandEvent& event)
{
    for (int i = 0; i < (int)courseList->GetCount(); i++)
    {
        if (!courseListSelectedAll)
            courseList->Check(i, true);
        else
            courseList->Check(i, false);
    }

    courseListSelectedAll = (!courseListSelectedAll);
    //SetStatusText(wxString::Format(wxT("Index: %d"), (int)courseListSelectedAll),1);

    // TODO: Update drawArea to show or hide all routes
}

void Courseplay_EditorFrame::OnCourseNameEnter(wxCommandEvent& event)
{
    courseList->SetString(courseListSelectedIndex, courseName->GetValue());
    courseName->SetValue(wxT(""));
    courseName->Enable(false);
    courseList->Deselect(courseListSelectedIndex);
    courseListSelectedIndex = -1;

    moveCourseUp->Enable(false);
    moveCourseDown->Enable(false);
}

void Courseplay_EditorFrame::OnMoveCourseUpClick(wxCommandEvent& event)
{
    //int oldpos = courseListSelectedIndex; // need this for the list to update.

    CheckListItem item;
    item.text = courseList->GetString(courseListSelectedIndex);
    item.isChecked = courseList->IsChecked(courseListSelectedIndex);

    courseList->Delete(courseListSelectedIndex);

    courseListSelectedIndex--;

    courseList->Insert(item.text, courseListSelectedIndex);

    courseList->Check(courseListSelectedIndex, item.isChecked);
    courseList->SetSelection(courseListSelectedIndex);

    // TODO: Move the course up in the course list (The real course list).

    moveCourseUp->Enable(courseListSelectedIndex != 0);
    moveCourseDown->Enable(courseListSelectedIndex < (int)courseList->GetCount() - 1);
}

void Courseplay_EditorFrame::OnMoveCourseDownClick(wxCommandEvent& event)
{
    //int oldpos = courseListSelectedIndex; // need this for the list to update.

    CheckListItem item;
    item.text = courseList->GetString(courseListSelectedIndex);
    item.isChecked = courseList->IsChecked(courseListSelectedIndex);

    courseList->Delete(courseListSelectedIndex);

    courseListSelectedIndex++;

    if (courseListSelectedIndex == (int)courseList->GetCount())
        courseList->Append(item.text);
    else
        courseList->Insert(item.text, courseListSelectedIndex);

    courseList->Check(courseListSelectedIndex, item.isChecked);
    courseList->SetSelection(courseListSelectedIndex);

    // TODO: Move the course down in the course list (The real course list).

    moveCourseUp->Enable(courseListSelectedIndex != 0);
    moveCourseDown->Enable(courseListSelectedIndex < (int)courseList->GetCount() - 1);
 }

void Courseplay_EditorFrame::OnWpPropReverseClick(wxCommandEvent& event)
{
    // TODO: Implement Reverse check
}

void Courseplay_EditorFrame::OnWpPropWaitPointClick(wxCommandEvent& event)
{
    // TODO: Implement Waiting point check
}

void Courseplay_EditorFrame::OnWpPropCrossingClick(wxCommandEvent& event)
{
    // TODO: Implement Crossing check
}

void Courseplay_EditorFrame::OnBtnFillOutDropdown(wxAuiToolBarEvent& event)
{
    if (event.IsDropDownClicked())
    {
        //SetStatusText(wxT("Drop Down Clicked!"));
        wxAuiToolBar* tb = static_cast<wxAuiToolBar*>(event.GetEventObject());

        tb->SetToolSticky(event.GetId(), true);

        // create the popup menu
        wxMenu menuPopup;

        wxBitmap icon = res.GetBitmap(wxT("icon_Width"), 16, 16);
        //wxBitmap bmp = wxArtProvider::GetBitmap(wxART_QUESTION, wxART_OTHER, wxSize(16,16));

        wxMenuItem* m1 =  new wxMenuItem(&menuPopup, 101, _("5 meters"));
        m1->SetBitmap(icon);
        menuPopup.Append(m1);

        wxMenuItem* m2 =  new wxMenuItem(&menuPopup, 101, _("10 meters"));
        m2->SetBitmap(icon);
        menuPopup.Append(m2);

        wxMenuItem* m3 =  new wxMenuItem(&menuPopup, 101, _("20 meters"));
        m3->SetBitmap(icon);
        menuPopup.Append(m3);

        // line up our menu with the button
        wxRect rect = tb->GetToolRect(event.GetId());
        wxPoint pt = tb->ClientToScreen(rect.GetBottomLeft());
        pt = ScreenToClient(pt);


        PopupMenu(&menuPopup, pt);


        // make sure the button is "un-stuck"
        tb->SetToolSticky(event.GetId(), false);
    }
    else
    {
        //SetStatusText(wxT("Fill Out Clicked!"));
    }
}

void Courseplay_EditorFrame::OnBtnGameSelectDropdown(wxAuiToolBarEvent& event)
{
    if (event.IsDropDownClicked())
    {
        //SetStatusText(wxT("Drop Down Clicked!"));
        wxAuiToolBar* tb = static_cast<wxAuiToolBar*>(event.GetEventObject());

        tb->SetToolSticky(event.GetId(), true);

        // create the popup menu
        wxMenu menuPopup;

        wxMenuItem* m1 =  new wxMenuItem(&menuPopup, Game_FarmingSimulator2011, _("Farming Simulator 2011"));
        m1->SetBitmap(TbIcon_Games[FS2011]);
        menuPopup.Append(m1);
        if (!settings->gameIsEnabled[FS2011])
            m1->Enable(false);

        wxMenuItem* m2 =  new wxMenuItem(&menuPopup, Game_FarmingSimulator2013, _("Farming Simulator 2013"));
        m2->SetBitmap(TbIcon_Games[FS2013]);
        menuPopup.Append(m2);
        if (!settings->gameIsEnabled[FS2013])
            m2->Enable(false);

        // line up our menu with the button
        wxRect rect = tb->GetToolRect(event.GetId());
        wxPoint pt = tb->ClientToScreen(rect.GetBottomLeft());
        pt = ScreenToClient(pt);

        PopupMenu(&menuPopup, pt);

        // make sure the button is "un-stuck"
        tb->SetToolSticky(event.GetId(), false);
    }
}

void Courseplay_EditorFrame::OnGameFS2011Select(wxCommandEvent& event)
{
    settings->setGameId(FS2011);
    updateToolbar2();

    // TODO: Reset everything for game change to Farming Simulator 2011
}

void Courseplay_EditorFrame::OnGameFS2013Select(wxCommandEvent& event)
{
    settings->setGameId(FS2013);
    updateToolbar2();

    // TODO: Reset everything for game change to Farming Simulator 2013
}

void Courseplay_EditorFrame::updateToolbar2(void)
{
    if (settings->selectedGameId >= 0)
    {
        if (!TbIcon_Games[settings->selectedGameId].IsNull())
            AuiTools2->SetToolBitmap(ID_TLB2_BTN_GAME_SELECT, TbIcon_Games[settings->selectedGameId]);
        else
        {
            wxSize sizer(TB_ICON_SIZE, TB_ICON_SIZE);
            wxBitmap tempIcon = wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_MISSING_IMAGE")), wxART_OTHER, sizer);
            AuiTools2->SetToolBitmap(ID_TLB2_BTN_GAME_SELECT, tempIcon);
        }

        AuiTools2->EnableTool(ID_TLB2_BTN_GAME_SELECT, true);
    }
    else
    {
        AuiTools2->EnableTool(ID_TLB2_BTN_GAME_SELECT, false);
    }

    // Make sure the toolbar is up to date
    AuiTools2->Refresh();
}

void Courseplay_EditorFrame::OnMainWindowRightDown(wxMouseEvent& event)
{
    mousePosX = event.GetX();
    mousePosY = event.GetY();
    // create the popup menu
    wxMenu menuPopup;

    wxMenuItem* m1 =  new wxMenuItem(&menuPopup, RightClickMenu_Add, _("Add Waypoint"));
    m1->SetBitmap(TbIcon_Add);
    menuPopup.Append(m1);

    wxMenuItem* m2 =  new wxMenuItem(&menuPopup, RightClickMenu_Insert, _("Insert Waypoint"));
    m2->SetBitmap(TbIcon_Insert);
    menuPopup.Append(m2);

    wxMenuItem* m3 =  new wxMenuItem(&menuPopup, RightClickMenu_Delete, _("Delete Waypoint"));
    m3->SetBitmap(TbIcon_Delete);
    menuPopup.Append(m3);

    wxMenuItem* m4 =  new wxMenuItem(&menuPopup, RightClickMenu_FillOut, _("Fill Out"));
    m4->SetBitmap(TbIcon_FillOut);
    menuPopup.Append(m4);

    wxPoint pt(mousePosX - 50, mousePosY + 10);


    PopupMenu(&menuPopup, pt);
}

void Courseplay_EditorFrame::OnRCMAddSelect(wxCommandEvent& event)
{
    // TODO: Implement right click menu Add Select
}

void Courseplay_EditorFrame::OnRCMInsertSelect(wxCommandEvent& event)
{
    // TODO: Implement right click menu Insert Select
}

void Courseplay_EditorFrame::OnRCMDeleteSelect(wxCommandEvent& event)
{
    // TODO: Implement right click menu Delete Select
}

void Courseplay_EditorFrame::OnRCMFillSelect(wxCommandEvent& event)
{
    // TODO: Implement right click menu Fill Out Select
}

void Courseplay_EditorFrame::OnUndoSelected(wxCommandEvent& event)
{
    // TODO: Implement undo
    SetStatusText(wxT("Undo"));
}

void Courseplay_EditorFrame::OnRedoSelected(wxCommandEvent& event)
{
    // TODO: Implement redo
    SetStatusText(wxT("Redo"));
}

void Courseplay_EditorFrame::OnSettingsSelected(wxCommandEvent& event)
{
    settings->showSettings();
}

void Courseplay_EditorFrame::OnManualSelected(wxCommandEvent& event)
{
    // TODO: Add manual
}

