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
#include <wx/statusbr.h>
//*)

struct CheckListItem
{
    wxString text;
    bool isChecked;
};

class Courseplay_EditorFrame: public wxFrame
{
    public:

        Courseplay_EditorFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~Courseplay_EditorFrame();


    public:
        void OnBtnFillOutDropdown   (wxAuiToolBarEvent& event);
        void OnBtnGameSelectDropdown(wxAuiToolBarEvent& event);
        void OnGameFS2011Select     (wxCommandEvent& event);
        void OnGameFS2013Select     (wxCommandEvent& event);

    private:
        bool            courseListSelectedAll;
        int             courseListSelectedIndex;
        wxPNGResource   res;

        wxBitmap TbIcon_FS2011;
        wxBitmap TbIcon_FS2013;

        static const long Game_FarmingSimulator2011;
        static const long Game_FarmingSimulator2013;

    private:

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
        //*)

        //(*Identifiers(Courseplay_EditorFrame)
        static const long ID_TLB1_BTN_NEW;
        static const long ID_TLB1_BTN_INSERT;
        static const long ID_TLB1_BTN_DELETE;
        static const long ID_TLB1_BTN_FILL;
        static const long ID_TLB1_BTN_GAME_SELECT;
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
        static const long ID_File_Load;
        static const long ID_File_Save;
        static const long idMenuQuit;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(Courseplay_EditorFrame)
        wxAuiManager* AuiManager1;
        wxCheckListBox* courseList;
        wxButton* moveCourseDown;
        wxButton* moveCourseUp;
        wxTextCtrl* wpPropPosX;
        wxStaticText* StaticText2;
        wxTextCtrl* wpPropAngle;
        wxPanel* panelCourseList;
        wxMenuItem* MenuItem4;
        wxTextCtrl* courseName;
        wxCheckBox* wpPropWaitPoint;
        wxButton* selectAllCourse;
        wxPanel* panelWpProp;
        wxStaticText* StaticText1;
        wxStaticText* StaticText3;
        wxScrolledWindow* mainWindow;
        wxMenuItem* MenuItem3;
        wxStaticText* StaticText5;
        wxStatusBar* StatusBar1;
        wxTextCtrl* wpPropSpeed;
        wxAuiToolBar* AuiTools1;
        wxTextCtrl* wpPropPosY;
        wxStaticText* StaticText4;
        wxCheckBox* wpPropCrossing;
        wxCheckBox* wpPropReverse;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // COURSEPLAY_EDITORMAIN_H
