//---------------------------------------------------------------------------

#ifndef FileManagerFormH
#define FileManagerFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.FileCtrl.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.Outline.hpp>
#include <Vcl.TabNotBk.hpp>
#include <Vcl.WinXCtrls.hpp>
#include "cdiroutl.h"
#include <System.Actions.hpp>
#include <Vcl.ActnList.hpp>
#include <Vcl.Samples.DirOutln.hpp>
#include <Vcl.Menus.hpp>
#include <System.ImageList.hpp>
#include <Vcl.ImgList.hpp>

class TManagerForm : public TForm
{
__published:	// IDE-managed Components
	TDirectoryListBox *LeftDirectoryListBox;
	TLabel *LeftDirectoryPath;
	TButton *ButtonCreate;
	TButton *ButtonDelete;
	TButton *ButtonRename;
	TDriveComboBox *LeftDriveComboBox;
	TStringGrid *LeftPanel;
	TStringGrid *RightPanel;
	TDriveComboBox *RightDriveComboBox;
	TLabel *RightDirectoryPath;
	TFilterComboBox *LeftFilterComboBox;
	TFilterComboBox *RightFilterComboBox;
	TDirectoryListBox *RightDirectoryListBox;
	TFileListBox *LeftFileListBox;
	TFileListBox *RightFileListBox;
	TButton *ButtonExit;
	TImageList *ImageList;
	TButton *ButtonMove;
	TButton *ButtonCopy;
    
	void __fastcall LeftDirectoryListBoxChange(TObject *Sender);
	void __fastcall ButtonCreateClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall ButtonDeleteClick(TObject *Sender);
	void __fastcall ButtonRenameClick(TObject *Sender);
	void __fastcall LeftDriveComboBoxChange(TObject *Sender);
	void __fastcall RightDriveComboBoxChange(TObject *Sender);
	void __fastcall RightDirectoryListBoxChange(TObject *Sender);
	void __fastcall LeftFilterComboBoxChange(TObject *Sender);
	void __fastcall RightFilterComboBoxChange(TObject *Sender);
	void __fastcall LeftPanelSelectCell(TObject *Sender, int ACol, int ARow, bool &CanSelect);
	void __fastcall LeftPanelDblClick(TObject *Sender);
	void __fastcall RightPanelSelectCell(TObject *Sender, int ACol, int ARow, bool &CanSelect);
	void __fastcall RightPanelDblClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall ButtonExitClick(TObject *Sender);
	void __fastcall LeftPanelClick(TObject *Sender);
	void __fastcall RightPanelClick(TObject *Sender);
	void __fastcall LeftPanelDrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect, TGridDrawState State);
	void __fastcall RightPanelDrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect, TGridDrawState State);
	void __fastcall LeftPanelKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall RightPanelKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall ButtonMoveClick(TObject *Sender);
    void __fastcall UpdateComponents();
    void __fastcall Delete(TDirectoryListBox *DirectoryListBoxFrom, TDirectoryListBox *DirectoryListBoxTo, TStringGrid *PanelFrom, TFileListBox *FileListBoxFrom, TLabel *LabelTo);
    void __fastcall Move(TDirectoryListBox *DirectoryListBoxFrom, TStringGrid *PanelFrom, TFileListBox *FileListBoxFrom, TLabel *LabelTo);
	void __fastcall ButtonCopyClick(TObject *Sender);
    void __fastcall Copy(TDirectoryListBox *DirectoryListBoxFrom, TStringGrid *PanelFrom, TFileListBox *FileListBoxFrom, TLabel *LabelTo);
    void __fastcall Rename(TDirectoryListBox *DirectoryListBoxFrom, TDirectoryListBox *DirectoryListBoxTo, TStringGrid *PanelFrom, TFileListBox *FileListBoxFrom, TLabel *LabelTo);
    void __fastcall Create(TDirectoryListBox *DirectoryListBoxFrom);
private:	// User declarations
public:		// User declarations
	__fastcall TManagerForm(TComponent* Owner);
};

extern PACKAGE TManagerForm *ManagerForm;

#endif
