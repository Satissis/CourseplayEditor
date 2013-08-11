#ifndef SETTINGSFRAME_H
#define SETTINGSFRAME_H

#include <wx/config.h>
#include "wxPNGResource.h"
#include <wx/aui/aui.h>
#include "Variables.h"

//(*Headers(SettingsFrame)
#include <wx/notebook.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/checkbox.h>
#include <wx/listbox.h>
#include <wx/statbox.h>
#include <wx/panel.h>
#include <wx/button.h>
#include <wx/dirdlg.h>
#include <wx/frame.h>
//*)

class Settings; // Dummy

class SettingsFrame: public wxFrame
{
	public:

		SettingsFrame(Settings* conf, wxAuiManager *m_mgr, wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~SettingsFrame();

		void autoDetectPath(FSGames gameId);
		void updateBtnFS11AutoDetect();
		void updateBtnFS13AutoDetect();
		bool updateLanguageList();
		void updateTapPanels();

    private:
        Settings       *setup;
        wxAuiManager   *AuiMan;
        LangList        langList;

    public:

		//(*Declarations(SettingsFrame)
		wxButton* BtnResetUI;
		wxButton* BtnClose;
		wxStaticBox* StaticBox8;
		wxStaticBox* StaticBox5;
		wxButton* BtnSetLang;
		wxListBox* LanguageList;
		wxStaticBox* StaticBox7;
		wxDirDialog* SelectPathDialog;
		wxNotebook* SettingsTaps;
		wxTextCtrl* FS13SavePath;
		wxTextCtrl* FS11SavePath;
		wxPanel* LangSettings;
		wxPanel* ShortcutSettings;
		wxPanel* GeneralSettings;
		wxButton* BtnFS13SavePath;
		wxTextCtrl* FS13InstallPath;
		wxButton* BtnFS11AutoDetect;
		wxPanel* Panel1;
		wxStaticBox* StaticBox6;
		wxStaticText* StaticText1;
		wxCheckBox* chkBackupSavegame;
		wxStaticBox* StaticBox1;
		wxStaticBox* StaticBox9;
		wxButton* BtnFS2011InstallPath;
		wxTextCtrl* FS11InstallPath;
		wxCheckBox* ChkBoxFS13Enabled;
		wxStaticBox* StaticBox2;
		wxCheckBox* ChkLoadLastSavegame;
		wxPanel* FS2013Settings;
		wxCheckBox* ChkBoxFS11Enabled;
		wxPanel* FS2011Settings;
		wxStaticBox* StaticBox3;
		wxButton* BtnFS11SavePath;
		wxPanel* UISettings;
		wxButton* BtnFS13AutoDetect;
		wxButton* BtnFS2013InstallPath;
		wxStaticText* currentLangLabel;
		wxStaticBox* StaticBox4;
		//*)

	protected:

		//(*Identifiers(SettingsFrame)
		static const long ID_STATICBOX8;
		static const long ID_CHK_LOAD_LAST_SAVEGAME;
		static const long ID_STATICBOX9;
		static const long ID_CHK_BACKUP_SAVEGAME;
		static const long ID_TAP_GENERAL;
		static const long ID_STATICBOX2;
		static const long ID_LANGLIST;
		static const long ID_STATICBOX3;
		static const long ID_STATICTEXT2;
		static const long ID_BTN_SETLANG;
		static const long ID_TAP_LANG;
		static const long ID_STATICBOX1;
		static const long ID_BTN_RESETUI;
		static const long ID_STATICTEXT1;
		static const long ID_TAP_UI;
		static const long ID_TAP_SHORTCUT;
		static const long ID_STATICBOX5;
		static const long ID_STATICBOX4;
		static const long ID_TXTCTRL_FS11InstallPath;
		static const long ID_BTN_FS11InstallPath;
		static const long ID_BTN_FS11SavePath;
		static const long ID_TXTCTRL_FS11SavePath;
		static const long ID_CHKBOX_FS11Enabled;
		static const long ID_BTN_FS11AutoDetect;
		static const long ID_TAP_FS2011;
		static const long ID_STATICBOX7;
		static const long ID_CHKBOX_FS13Enabled;
		static const long ID_STATICBOX6;
		static const long ID_TXTCTRL_FS13SavePath;
		static const long ID_TXTCTRL_FS13InstallPath;
		static const long ID_BTN_FS13SavePath;
		static const long ID_BTN_FS13InstallPath;
		static const long ID_BTN_FS13AutoDetect;
		static const long ID_TAP_FS2013;
		static const long ID_SETTINGSTAPS;
		static const long ID_BTN_Close;
		static const long ID_PANEL1;
		//*)

	private:

		//(*Handlers(SettingsFrame)
		void OnPanel2Paint(wxPaintEvent& event);
		void OnBtnResetUIClick(wxCommandEvent& event);
		void OnSettingsTapsPageChanged(wxNotebookEvent& event);
		void OnMouseEnter(wxMouseEvent& event);
		void OnLangListSelect(wxCommandEvent& event);
		void OnBtnSetLangClick(wxCommandEvent& event);
		void OnTextCtrl1Text(wxCommandEvent& event);
		void OnChkBoxFS11EnabledClick(wxCommandEvent& event);
		void OnFS11SavePathTextChange(wxCommandEvent& event);
		void OnFS11InstallPathTextChange(wxCommandEvent& event);
		void OnBtnFS2011InstallPathClick(wxCommandEvent& event);
		void OnBtnFS11SavePathClick(wxCommandEvent& event);
		void OnBtnCloseClick(wxCommandEvent& event);
		void OnBtnFS11AutoDetectClick(wxCommandEvent& event);
		void OnChkBoxFS13EnabledClick(wxCommandEvent& event);
		void OnFS13InstallPathTextChange(wxCommandEvent& event);
		void OnFS13SavePathTextChange(wxCommandEvent& event);
		void OnBtnFS2013InstallPathClick(wxCommandEvent& event);
		void OnBtnFS13SavePathClick(wxCommandEvent& event);
		void OnBtnFS13AutoDetectClick(wxCommandEvent& event);
		void OnChkLoadLastSavegameClick(wxCommandEvent& event);
		void OnChkBackupSavegameClick(wxCommandEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
