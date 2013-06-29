/***************************************************************
 * Name:      Courseplay_EditorMain.h
 * Purpose:   Defines Application Frame
 * Author:    Claus G. Pedersen aka Satis (satissis@gmail.com)
 * Created:   2013-06-08
 * Copyright: Claus G. Pedersen aka Satis (https://github.com/Satissis/CourseplayEditor)
 * License:
 **************************************************************/

#ifndef COURSEPLAY_EDITORMAIN_H
#define COURSEPLAY_EDITORMAIN_H

#include "wxPNGResource.h"
#include "Variables.h"

//(*Headers(Courseplay_EditorFrame)
#include <wx/scrolwin.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/menu.h>
#include <wx/textctrl.h>
#include <wx/checklst.h>
#include <wx/checkbox.h>
#include <wx/aui/aui.h>
#include <wx/panel.h>
#include <wx/button.h>
#include <wx/frame.h>
#include <wx/combobox.h>
#include <wx/statusbr.h>
//*)

struct CheckListItem
{
    wxString text;
    bool isChecked;
};

class Settings;

class Courseplay_EditorFrame: public wxFrame
{
    public: // Functions

        Courseplay_EditorFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~Courseplay_EditorFrame();

        void updateToolbar2(void);


    public: // Event Functions
        void OnBtnFillOutDropdown   (wxAuiToolBarEvent& event);
        void OnBtnGameSelectDropdown(wxAuiToolBarEvent& event);
        void OnGameFS2011Select     (wxCommandEvent& event);
        void OnGameFS2013Select     (wxCommandEvent& event);
        void OnRCMAddSelect         (wxCommandEvent& event);
        void OnRCMInsertSelect      (wxCommandEvent& event);
        void OnRCMDeleteSelect      (wxCommandEvent& event);
        void OnRCMFillSelect        (wxCommandEvent& event);

    public: // Variables

    private: // Functions

    private: // Variables
        Settings *settings;
        wxString defaultLayout;

        bool            courseListSelectedAll;
        bool            rightClickMenuOpen;

        int             courseListSelectedIndex;
        int             mousePosX;
        int             mousePosY;

        wxPNGResource   res;

        wxBitmap TbIcon_Add;
        wxBitmap TbIcon_Insert;
        wxBitmap TbIcon_Delete;
        wxBitmap TbIcon_FillOut;
        wxBitmap TbIcon_Games[NumOfFSGames];

        static const long Game_FarmingSimulator2011;
        static const long Game_FarmingSimulator2013;
        static const long RightClickMenu_Add;
        static const long RightClickMenu_Insert;
        static const long RightClickMenu_Delete;
        static const long RightClickMenu_FillOut;

    private: // Code::Block handles this section.

        //(*Handlers(Courseplay_EditorFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnClose(wxCloseEvent& event);
        void OnCourseListToggled(wxCommandEvent& event);
        void OnCourseListSelect(wxCommandEvent& event);
        void OnSelectAllCourseClick(wxCommandEvent& event);
        void OnCourseNameEnter(wxCommandEvent& event);
        void OnMoveCourseUpClick(wxCommandEvent& event);
        void OnMoveCourseDownClick(wxCommandEvent& event);
        void OnWpPropReverseClick(wxCommandEvent& event);
        void OnWpPropWaitPointClick(wxCommandEvent& event);
        void OnWpPropCrossingClick(wxCommandEvent& event);
        void OnMainWindowRightDown(wxMouseEvent& event);
        void OnUndoSelected(wxCommandEvent& event);
        void OnRedoSelected(wxCommandEvent& event);
        void OnSettingsSelected(wxCommandEvent& event);
        void OnManualSelected(wxCommandEvent& event);
        //*)

        //(*Identifiers(Courseplay_EditorFrame)
        static const long ID_TLB1_BTN_NEW;
        static const long ID_TLB1_BTN_INSERT;
        static const long ID_TLB1_BTN_DELETE;
        static const long ID_TLB1_BTN_FILL;
        static const long ID_TOOL_UNDO;
        static const long ID_TOOL_REDO;
        static const long TLB_1;
        static const long ID_Main_Window;
        static const long ID_COURSELISTBOX;
        static const long BTN_SELECTALLCOURSE;
        static const long BTN_MOVECOURSEUP;
        static const long BTN_MOVECOURSEDOWN;
        static const long ID_STATICTEXT1;
        static const long TXT_COURSENAME;
        static const long ID_PANEL1;
        static const long ID_STATICTEXT2;
        static const long ID_TEXTCTRL1;
        static const long ID_STATICTEXT3;
        static const long ID_TEXTCTRL2;
        static const long ID_STATICTEXT5;
        static const long ID_TEXTCTRL3;
        static const long ID_STATICTEXT4;
        static const long ID_TEXTCTRL4;
        static const long ID_CHECKBOX1;
        static const long ID_CHECKBOX2;
        static const long ID_CHECKBOX3;
        static const long ID_PANEL2;
        static const long ID_TLB2_BTN_GAME_SELECT;
        static const long ID_TLB2_COMBOX_SAVEGAMESELECT;
        static const long ID_TLB2_BTN_RELOAD;
        static const long ID_TLB2_BTN_SAVESAVEGAME;
        static const long TLB_2;
        static const long idMenuQuit;
        static const long ID_EDIT_Undo;
        static const long ID_EDIT_Redo;
        static const long ID_EDIT_Settings;
        static const long ID_HELP_Manual;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(Courseplay_EditorFrame)
        wxCheckListBox* courseList;
        wxButton* moveCourseDown;
        wxButton* moveCourseUp;
        wxAuiManager* m_mgr;
        wxTextCtrl* wpPropPosX;
        wxStaticText* StaticText2;
        wxTextCtrl* wpPropAngle;
        wxMenu* Menu3;
        wxPanel* panelCourseList;
        wxTextCtrl* courseName;
        wxCheckBox* wpPropWaitPoint;
        wxButton* selectAllCourse;
        wxPanel* panelWpProp;
        wxStaticText* StaticText1;
        wxStaticText* StaticText3;
        wxScrolledWindow* mainWindow;
        wxMenuItem* Manual;
        wxMenuItem* Redo;
        wxStaticText* StaticText5;
        wxStatusBar* StatusBar1;
        wxTextCtrl* wpPropSpeed;
        wxAuiToolBar* AuiTools1;
        wxMenuItem* CPE_Settings;
        wxComboBox* SavegameSelect;
        wxTextCtrl* wpPropPosY;
        wxStaticText* StaticText4;
        wxMenuItem* Undo;
        wxCheckBox* wpPropCrossing;
        wxAuiToolBar* AuiTools2;
        wxCheckBox* wpPropReverse;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // COURSEPLAY_EDITORMAIN_H
