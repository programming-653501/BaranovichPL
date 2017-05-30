#include <vcl.h>
#pragma hdrstop

#include "FileManagerForm.h"
#include <windows.h>
#include <Shellapi.h>
#include <algorithm>

#pragma package(smart_init)
#pragma link "cdiroutl"
#pragma resource "*.dfm"

using namespace std;

TManagerForm *ManagerForm;
int leftPanelSelectedRow, rightPanelSelectedRow;
int selectedPanel = 1;


__fastcall TManagerForm::TManagerForm(TComponent* Owner)
	: TForm(Owner)
{
}



void __fastcall TManagerForm::LeftDirectoryListBoxChange(TObject *Sender)
{
    LeftDirectoryPath->Caption = LeftDirectoryListBox->Directory;
	LeftFileListBox->Directory = LeftDirectoryListBox->Directory;
	LeftPanel->RowCount = LeftDirectoryListBox->Count - LeftDirectoryListBox->ItemIndex + 1 + LeftFileListBox->Count;

    WIN32_FILE_ATTRIBUTE_DATA itemInformation;

    int numberOfFirstWriteItem = LeftDirectoryListBox->ItemIndex + 1;
    int numberOfLastWriteItem = LeftDirectoryListBox->Count - 1;
    String itemName;
    
    for (int i = numberOfFirstWriteItem; i <= numberOfLastWriteItem; i++)
    {
        LeftPanel->Cells[1][i - numberOfFirstWriteItem + 2] = LeftDirectoryListBox->Items->Strings[i];
        LeftPanel->Cells[2][i - numberOfFirstWriteItem + 2] = "";
        LeftPanel->Cells[3][i - numberOfFirstWriteItem + 2] = "<Папка>";
        itemName = LeftDirectoryListBox->GetItemPath(i);
        if(GetFileAttributesEx(itemName.c_str(), GetFileExInfoStandard, (LPVOID)&itemInformation)) 
        {
            SYSTEMTIME systemTime;

            if(FileTimeToSystemTime(&itemInformation.ftLastWriteTime, &systemTime))
            {
                TDateTime itemCreateTime = SystemTimeToDateTime(systemTime);
                itemCreateTime += 3.0 / 24;
                LeftPanel->Cells[4][i - numberOfFirstWriteItem + 2] = itemCreateTime.DateTimeString();
            }
        }
    }
    
    numberOfFirstWriteItem = numberOfLastWriteItem - numberOfFirstWriteItem + 3;
    numberOfLastWriteItem = LeftFileListBox->Count;
    int pointPosition;
    
    for (int i = 0; i < numberOfLastWriteItem; i++)
    {
        itemName = ExtractFileName(LeftFileListBox->Items->Strings[i]);
        pointPosition = LastDelimiter('.', itemName);
        itemName.Delete(pointPosition, itemName.Length() - pointPosition + 1);
        LeftPanel->Cells[1][i + numberOfFirstWriteItem] = itemName;
        LeftPanel->Cells[2][i + numberOfFirstWriteItem] = ExtractFileExt(LeftFileListBox->Items->Strings[i]);
        itemName = LeftDirectoryListBox->Directory + "\\" + LeftFileListBox->Items->Strings[i];
        
        if(GetFileAttributesEx(itemName.c_str(), GetFileExInfoStandard, (LPVOID)&itemInformation))
        {
            SYSTEMTIME systemTime;

            if(FileTimeToSystemTime(&itemInformation.ftLastWriteTime, &systemTime))
            {
                TDateTime itemCreateTime = SystemTimeToDateTime(systemTime);
                itemCreateTime += 3.0 / 24;
                LeftPanel->Cells[4][i + numberOfFirstWriteItem] = itemCreateTime.DateTimeString();
                LeftPanel->Cells[3][i + numberOfFirstWriteItem] = itemInformation.nFileSizeHigh * (MAXDWORD + 1) + itemInformation.nFileSizeLow;
            }
        }
    }
}



void __fastcall TManagerForm::Create(TDirectoryListBox *DirectoryListBoxFrom)
{
	String directoryPath = DirectoryListBoxFrom->GetItemPath(DirectoryListBoxFrom->ItemIndex);
    String folderName;
    folderName = InputBox("Создание папки", "Введите имя папки", "");
    String folderDirectoryPath = directoryPath + "\\" + folderName;

    if (!CreateDirectory(folderDirectoryPath.c_str() , NULL))
        MessageDlg("Каталог с данным именем уже существует.", mtError, TMsgDlgButtons() << mbOK, 0);

    UpdateComponents();
}



void __fastcall TManagerForm::ButtonCreateClick(TObject *Sender)
{
	if (selectedPanel == 1) 
    	Create(LeftDirectoryListBox);
    else 
    	Create(RightDirectoryListBox);    
}



void __fastcall TManagerForm::FormCreate(TObject *Sender)
{
    SHFILEINFO info;
    String temp = "";
  	DWORD ImageHandle = SHGetFileInfo(temp.c_str(), 0, &info, sizeof(info), SHGFI_ICON | SHGFI_SHELLICONSIZE | SHGFI_SYSICONINDEX);

    if (ImageHandle != 0)
  	{
    	ImageList->Handle = ImageHandle;
    	ImageList->ShareImages = true;
  	}

    LeftDirectoryPath->Caption = LeftDirectoryListBox->Directory;
    RightDirectoryPath->Caption = RightDirectoryListBox->Directory;

    LeftPanel->Cells[1][0] = "Имя";
    RightPanel->Cells[1][0] = "Имя";
    LeftPanel->Cells[2][0] = "Тип";
    RightPanel->Cells[2][0] = "Тип";
    LeftPanel->Cells[3][0] = "Размер";
    RightPanel->Cells[3][0] = "Размер";
    LeftPanel->Cells[4][0] = "Дата";
    RightPanel->Cells[4][0] = "Дата";
    LeftPanel->Cells[1][1] = "[..]";
    RightPanel->Cells[1][1] = "[..]";

    LeftPanel->ColCount = 5;
    RightPanel->ColCount = 5;
}



void __fastcall TManagerForm::UpdateComponents()
{
	LeftFileListBox->Update();
    RightFileListBox->Update();
    LeftDirectoryListBox->Update();
    RightDirectoryListBox->Update();
    LeftPanel->Repaint();
    RightPanel->Repaint();	
}



void __fastcall TManagerForm::Delete(TDirectoryListBox *DirectoryListBoxFrom, TDirectoryListBox *DirectoryListBoxTo, TStringGrid *PanelFrom, TFileListBox *FileListBoxFrom, TLabel *LabelTo)
{
    int topSelectedRow = max(PanelFrom->Selection.Top, 2);
    int bottomSelectedRow = PanelFrom->Selection.Bottom;
    bool updateFlag = false;
    String pathFrom, removedElements = "";

    for (int i = topSelectedRow; i <= bottomSelectedRow; ++i)
    {
    	if (PanelFrom->Cells[3][i] != "<Папка>")
        {
        	int j = i - 1 - DirectoryListBoxFrom->Count + DirectoryListBoxFrom->ItemIndex;
        	if (DirectoryListBoxFrom->ItemIndex == 0)
        		pathFrom = DirectoryListBoxFrom->GetItemPath(DirectoryListBoxFrom->ItemIndex) + ExtractFileName(FileListBoxFrom->Items->Strings[j]);
            else 
            	pathFrom = DirectoryListBoxFrom->GetItemPath(DirectoryListBoxFrom->ItemIndex) + "\\" + ExtractFileName(FileListBoxFrom->Items->Strings[j]);
        }
        else if (PanelFrom->Cells[3][i] == "<Папка>")
        {
        	if (DirectoryListBoxFrom->ItemIndex == 0)
        		pathFrom = DirectoryListBoxFrom->Directory + PanelFrom->Cells[1][i];
    		else 
            	pathFrom = DirectoryListBoxFrom->Directory + "\\" + PanelFrom->Cells[1][i];

        	String pathTo = LabelTo->Caption;
            bool entryFlag = true;

        	if (pathFrom.Length() == pathTo.Length()) 
            {
            	for (int j = 1; j <= pathFrom.Length(); ++j)
            		if (pathFrom[j] != pathTo[j]) entryFlag = false;
        	}
            else if (pathFrom.Length() < pathTo.Length()) 
            {
            	pathFrom += '\\';
            	for (int j = 1; j <= pathFrom.Length(); ++j)
            		if (pathFrom[j] != pathTo[j]) entryFlag = false;
                pathFrom.Delete(pathFrom.Length(), 1);    
        	}
        	else 
            	entryFlag = false;

            if (entryFlag) 
            	updateFlag = true;  
    	}
        removedElements += pathFrom + '\0';
    }

    removedElements += '\0';
    
    SHFILEOPSTRUCT operation;
    ZeroMemory(&operation, sizeof(operation));
    operation.hwnd  = ManagerForm->Handle;
    operation.wFunc = FO_DELETE;
    operation.pFrom = removedElements.c_str();
    operation.fFlags = FOF_ALLOWUNDO;
    SHFileOperation(&operation);

    if (updateFlag) 
    	DirectoryListBoxTo->Directory = DirectoryListBoxFrom->Directory;

    UpdateComponents();
}



void __fastcall TManagerForm::ButtonDeleteClick(TObject *Sender)
{
    if (selectedPanel == 1) 
    	Delete(LeftDirectoryListBox, RightDirectoryListBox, LeftPanel, LeftFileListBox, RightDirectoryPath);
    else 
    	Delete(RightDirectoryListBox, LeftDirectoryListBox, RightPanel, RightFileListBox, LeftDirectoryPath);
}



void __fastcall TManagerForm::Rename(TDirectoryListBox *DirectoryListBoxFrom, TDirectoryListBox *DirectoryListBoxTo, TStringGrid *PanelFrom, TFileListBox *FileListBoxFrom, TLabel *LabelTo)
{
	String oldItemPath, newItemPath, secondPanelPath, temp, newItemName;
    bool flag;
    int pathLength, selectedItemRow = PanelFrom->Selection.Top;
    
    if (PanelFrom->Cells[3][selectedItemRow] != "<Папка>")
	{
		int i = selectedItemRow - 1 - DirectoryListBoxFrom->Count + DirectoryListBoxFrom->ItemIndex;
        if (DirectoryListBoxFrom->ItemIndex == 0)
        	oldItemPath = DirectoryListBoxFrom->GetItemPath(DirectoryListBoxFrom->ItemIndex) + "\\" + ExtractFileName(FileListBoxFrom->Items->Strings[i]);
        else 
        	oldItemPath = DirectoryListBoxFrom->GetItemPath(DirectoryListBoxFrom->ItemIndex) + "\\" + ExtractFileName(FileListBoxFrom->Items->Strings[i]);

		newItemName = InputBox("Переименование файла", "Введите новое имя", "");

        if (DirectoryListBoxFrom->ItemIndex == 0)
        	newItemPath = DirectoryListBoxFrom->GetItemPath(DirectoryListBoxFrom->ItemIndex) + "\\" + newItemName + ExtractFileExt(FileListBoxFrom->Items->Strings[i]);
        else 
        	newItemPath = DirectoryListBoxFrom->GetItemPath(DirectoryListBoxFrom->ItemIndex) + "\\" + newItemName + ExtractFileExt(FileListBoxFrom->Items->Strings[i]);

        oldItemPath += '\0';
        newItemPath += '\0';
	}
	else if (PanelFrom->Cells[3][selectedItemRow] == "<Папка>")
    {
    	oldItemPath = DirectoryListBoxFrom->GetItemPath(DirectoryListBoxFrom->ItemIndex + selectedItemRow - 1);

    	newItemName = InputBox("Переименование папки", "Введите новое имя", "");

    	if (DirectoryListBoxFrom->ItemIndex == 0)
        	newItemPath = DirectoryListBoxFrom->GetItemPath(DirectoryListBoxFrom->ItemIndex) + newItemName;
        else 
        	newItemPath = DirectoryListBoxFrom->GetItemPath(DirectoryListBoxFrom->ItemIndex) + "\\" + newItemName;

    	secondPanelPath = LabelTo->Caption;
    	pathLength = oldItemPath.Length();

    	flag = true;
    	if (oldItemPath.Length() <= secondPanelPath.Length()) 
        {
    		for (int i = 1; i <= oldItemPath.Length(); ++i)
            	if (oldItemPath[i] != secondPanelPath[i]) flag = false;
    	}
    	else 
        	flag = false;

    	oldItemPath += '\0';
    	temp = newItemPath;
    	newItemPath += '\0';
    }

    SHFILEOPSTRUCT operation;
    ZeroMemory(&operation, sizeof(operation));
    operation.hwnd  = ManagerForm->Handle;
    operation.wFunc = FO_RENAME;
    operation.pFrom = oldItemPath.c_str();
    operation.pTo = newItemPath.c_str();
    operation.fFlags = 0;
    SHFileOperation(&operation);
    
    if (PanelFrom->Cells[3][selectedItemRow] == "<Папка>")
    {
        if (flag) 
        {
        	secondPanelPath.Delete(1, pathLength);
        	secondPanelPath = temp + "\\" + secondPanelPath;
    	}
    	DirectoryListBoxTo->Directory = secondPanelPath;
    }

    UpdateComponents();	
}


void __fastcall TManagerForm::ButtonRenameClick(TObject *Sender)
{
	if (selectedPanel == 1 && LeftPanel->Selection.Top > 1) 
    	Rename(LeftDirectoryListBox, RightDirectoryListBox, LeftPanel, LeftFileListBox, RightDirectoryPath);
    else if (LeftPanel->Selection.Top > 1)
    	Rename(RightDirectoryListBox, LeftDirectoryListBox, RightPanel, RightFileListBox, LeftDirectoryPath);
}



void __fastcall TManagerForm::LeftDriveComboBoxChange(TObject *Sender)
{
    LeftDirectoryListBox->Drive = LeftDriveComboBox->Drive;
    LeftDirectoryListBox->Directory = LeftDirectoryListBox->GetItemPath(0);
    LeftPanel->Repaint();
}



void __fastcall TManagerForm::RightDriveComboBoxChange(TObject *Sender)
{
    RightDirectoryListBox->Drive = RightDriveComboBox->Drive;
    RightDirectoryListBox->Directory = RightDirectoryListBox->GetItemPath(0);
    RightPanel->Repaint();
}



void __fastcall TManagerForm::RightDirectoryListBoxChange(TObject *Sender)
{
    RightDirectoryPath->Caption = RightDirectoryListBox->Directory;
	RightFileListBox->Directory = RightDirectoryListBox->Directory;
	RightPanel->RowCount = RightDirectoryListBox->Count - RightDirectoryListBox->ItemIndex + 1 + RightFileListBox->Count;

    WIN32_FILE_ATTRIBUTE_DATA itemInformation;

    int numberOfFirstWriteItem = RightDirectoryListBox->ItemIndex + 1;
    int numberOfLastWriteItem = RightDirectoryListBox->Count - 1;
    String itemName;
    
    for (int i = numberOfFirstWriteItem; i <= numberOfLastWriteItem; i++)
    {
        RightPanel->Cells[1][i - numberOfFirstWriteItem + 2] = RightDirectoryListBox->Items->Strings[i];
        RightPanel->Cells[2][i - numberOfFirstWriteItem + 2] = "";
        RightPanel->Cells[3][i - numberOfFirstWriteItem + 2] = "<Папка>";
        itemName = RightDirectoryListBox->GetItemPath(i);
        if(GetFileAttributesEx(itemName.c_str(), GetFileExInfoStandard, (LPVOID)&itemInformation)) 
        {
            SYSTEMTIME systemTime;

            if(FileTimeToSystemTime(&itemInformation.ftLastWriteTime, &systemTime))
            {
                TDateTime itemCreateTime = SystemTimeToDateTime(systemTime);
                itemCreateTime += 3.0 / 24;
                RightPanel->Cells[4][i - numberOfFirstWriteItem + 2] = itemCreateTime.DateTimeString();
            }
        }
    }
    
    numberOfFirstWriteItem = numberOfLastWriteItem - numberOfFirstWriteItem + 3;
    numberOfLastWriteItem = RightFileListBox->Count;
    int pointPosition;
    
    for (int i = 0; i < numberOfLastWriteItem; i++)
    {
        itemName = ExtractFileName(RightFileListBox->Items->Strings[i]);
        pointPosition = LastDelimiter('.', itemName);
        itemName.Delete(pointPosition, itemName.Length() - pointPosition + 1);
        RightPanel->Cells[1][i + numberOfFirstWriteItem] = itemName;
        RightPanel->Cells[2][i + numberOfFirstWriteItem] = ExtractFileExt(RightFileListBox->Items->Strings[i]);
        itemName = RightDirectoryListBox->Directory + "\\" + RightFileListBox->Items->Strings[i];
        
        if(GetFileAttributesEx(itemName.c_str(), GetFileExInfoStandard, (LPVOID)&itemInformation))
        {
            SYSTEMTIME systemTime;

            if(FileTimeToSystemTime(&itemInformation.ftLastWriteTime, &systemTime))
            {
                TDateTime itemCreateTime = SystemTimeToDateTime(systemTime);
                itemCreateTime += 3.0 / 24;
                RightPanel->Cells[4][i + numberOfFirstWriteItem] = itemCreateTime.DateTimeString();
                RightPanel->Cells[3][i + numberOfFirstWriteItem] = itemInformation.nFileSizeHigh * (MAXDWORD + 1) + itemInformation.nFileSizeLow;
            }
        }
    }
}



void __fastcall TManagerForm::LeftFilterComboBoxChange(TObject *Sender)
{
    LeftFileListBox->Mask = LeftFilterComboBox->Mask;
    LeftDirectoryListBoxChange(0);
}



void __fastcall TManagerForm::RightFilterComboBoxChange(TObject *Sender)
{
    RightFileListBox->Mask = RightFilterComboBox->Mask;
    RightDirectoryListBoxChange(0);
}



void __fastcall TManagerForm::LeftPanelSelectCell(TObject *Sender, int ACol, int ARow,
          bool &CanSelect)
{
    leftPanelSelectedRow = ARow;
}



void __fastcall TManagerForm::LeftPanelDblClick(TObject *Sender)
{
    selectedPanel = 1;
    if (leftPanelSelectedRow > 0 && leftPanelSelectedRow < LeftDirectoryListBox->Count - LeftDirectoryListBox->ItemIndex + 1)
    {
    	if (leftPanelSelectedRow == 1 && LeftDirectoryListBox->ItemIndex > 0)
        	LeftDirectoryListBox->Directory = LeftDirectoryListBox->GetItemPath(LeftDirectoryListBox->ItemIndex - 1);
    	else 
        	LeftDirectoryListBox->Directory = LeftDirectoryListBox->GetItemPath(LeftDirectoryListBox->ItemIndex + leftPanelSelectedRow - 1);
    }
    else if (leftPanelSelectedRow > 0)
    {
        String directoryPath = LeftFileListBox->Directory + "\\" + LeftFileListBox->Items->Strings[leftPanelSelectedRow - (LeftDirectoryListBox->Count - LeftDirectoryListBox->ItemIndex + 1)];
    	ShellExecute(ManagerForm->Handle, L"open", directoryPath.c_str(), NULL, NULL, SW_SHOWDEFAULT);
    }
    
    LeftPanel->Repaint();
}



void __fastcall TManagerForm::RightPanelSelectCell(TObject *Sender, int ACol, int ARow,
          bool &CanSelect)
{
    rightPanelSelectedRow = ARow;
}



void __fastcall TManagerForm::RightPanelDblClick(TObject *Sender)
{
    selectedPanel = 2;
    if (rightPanelSelectedRow > 0 && rightPanelSelectedRow < RightDirectoryListBox->Count - RightDirectoryListBox->ItemIndex + 1)
    {
    	if (rightPanelSelectedRow == 1 && RightDirectoryListBox->ItemIndex > 0)
        	RightDirectoryListBox->Directory = RightDirectoryListBox->GetItemPath(RightDirectoryListBox->ItemIndex - 1);
    	else 
        	RightDirectoryListBox->Directory = RightDirectoryListBox->GetItemPath(RightDirectoryListBox->ItemIndex + rightPanelSelectedRow - 1);
    }
    else if (rightPanelSelectedRow > 0)
    {
        String directoryPath = RightFileListBox->Directory + "\\" + RightFileListBox->Items->Strings[rightPanelSelectedRow - (RightDirectoryListBox->Count - RightDirectoryListBox->ItemIndex + 1)];
    	ShellExecute(ManagerForm->Handle, L"open", directoryPath.c_str(), NULL, NULL, SW_SHOWDEFAULT);
    }
    
    RightPanel->Repaint();
}



void __fastcall TManagerForm::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if (Key == 116) 
    	ButtonCopyClick(0);
	if (Key == 117) 
    	ButtonMoveClick(0);
    if (Key == 118) 
    	ButtonCreateClick(0);
	if (Key == 119) 
    	ButtonDeleteClick(0);
    if (Key == 120) 
    	ButtonRenameClick(0);
}



void __fastcall TManagerForm::ButtonExitClick(TObject *Sender)
{
    ManagerForm->Close();
}



void __fastcall TManagerForm::LeftPanelClick(TObject *Sender)
{
    selectedPanel = 1;
}



void __fastcall TManagerForm::RightPanelClick(TObject *Sender)
{
    selectedPanel = 2;
}



void __fastcall TManagerForm::LeftPanelDrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect,
          TGridDrawState State)
{
	Graphics::TBitmap * Bitmap = new Graphics::TBitmap;
    int itemIndex = LeftDirectoryListBox->ItemIndex;
    String directoryPath;
    SHFILEINFO info;
    DWORD result;
    
    if (ACol == 0 && ARow > 1)
    {
        if (ARow < LeftDirectoryListBox->Count - LeftDirectoryListBox->ItemIndex + 1)
            directoryPath = LeftDirectoryListBox->GetItemPath(itemIndex + ARow - 1);
        else 
        {
            if (LeftDirectoryListBox->ItemIndex > 0)
                directoryPath = LeftFileListBox->Directory + "\\" + LeftFileListBox->Items->Strings[ARow - (LeftDirectoryListBox->Count - LeftDirectoryListBox->ItemIndex + 1)];
            else 
            	directoryPath = LeftFileListBox->Directory + LeftFileListBox->Items->Strings[ARow - (LeftDirectoryListBox->Count - LeftDirectoryListBox->ItemIndex + 1)];
        }

        SHGetFileInfo(directoryPath.c_str(), 0, &info, sizeof(info), SHGFI_ICON | SHGFI_SHELLICONSIZE | SHGFI_SYSICONINDEX);

        ImageList->GetBitmap(info.iIcon, Bitmap);
        LeftPanel->Canvas->StretchDraw(Rect, Bitmap);
    }
}



void __fastcall TManagerForm::RightPanelDrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect,
          TGridDrawState State)
{
    Graphics::TBitmap * Bitmap = new Graphics::TBitmap;
    int itemIndex = RightDirectoryListBox->ItemIndex;
    String directoryPath;
    SHFILEINFO info;
    DWORD result;
    
    if (ACol == 0 && ARow > 1)
    {
        if (ARow < RightDirectoryListBox->Count - RightDirectoryListBox->ItemIndex + 1)
            directoryPath = RightDirectoryListBox->GetItemPath(itemIndex + ARow - 1);
        else 
        {
            if (RightDirectoryListBox->ItemIndex > 0)
                directoryPath = RightFileListBox->Directory + "\\" + RightFileListBox->Items->Strings[ARow - (RightDirectoryListBox->Count - RightDirectoryListBox->ItemIndex + 1)];
            else 
            	directoryPath = RightFileListBox->Directory + RightFileListBox->Items->Strings[ARow - (RightDirectoryListBox->Count - RightDirectoryListBox->ItemIndex + 1)];
        }

        SHGetFileInfo(directoryPath.c_str(), 0, &info, sizeof(info), SHGFI_ICON | SHGFI_SHELLICONSIZE | SHGFI_SYSICONINDEX);

        ImageList->GetBitmap(info.iIcon, Bitmap);
        RightPanel->Canvas->StretchDraw(Rect, Bitmap);
    }
}



void __fastcall TManagerForm::LeftPanelKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	String directoryPath = LeftDirectoryPath->Caption;

    if (Key == 13) 
    	LeftPanelDblClick(0);
    if (Key == 27 || Key == 8 && directoryPath.Length() > 3) 
    {
        leftPanelSelectedRow = 1;
        LeftPanelDblClick(0);
    }
}



void __fastcall TManagerForm::RightPanelKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	String directoryPath = RightDirectoryPath->Caption;

    if (Key == 13) 
    	RightPanelDblClick(0);
    if (Key == 27 || Key == 8 && directoryPath.Length() > 3) 
    {
        rightPanelSelectedRow = 1;
        RightPanelDblClick(0);
    }
}



void __fastcall TManagerForm::Move(TDirectoryListBox *DirectoryListBoxFrom, TStringGrid *PanelFrom, TFileListBox *FileListBoxFrom, TLabel *LabelTo)
{
    int topSelectedRow = max(PanelFrom->Selection.Top, 2);
    int bottomSelectedRow = PanelFrom->Selection.Bottom;
    String movedFrom = "";

    for (int i = topSelectedRow; i <= bottomSelectedRow; ++i)
    {
    	if (PanelFrom->Cells[3][i] != "<Папка>")
        {
        	int j = i - 1 - DirectoryListBoxFrom->Count + DirectoryListBoxFrom->ItemIndex;
        	if (DirectoryListBoxFrom->ItemIndex == 0)
        		movedFrom += DirectoryListBoxFrom->GetItemPath(DirectoryListBoxFrom->ItemIndex) + ExtractFileName(FileListBoxFrom->Items->Strings[j]);
            else 
            	movedFrom += DirectoryListBoxFrom->GetItemPath(DirectoryListBoxFrom->ItemIndex) + "\\" + ExtractFileName(FileListBoxFrom->Items->Strings[j]);
        }
        else if (PanelFrom->Cells[3][i] == "<Папка>")
        {
        	if (DirectoryListBoxFrom->ItemIndex == 0)
        		movedFrom += DirectoryListBoxFrom->Directory + PanelFrom->Cells[1][i];
    		else 
            	movedFrom += DirectoryListBoxFrom->Directory + "\\" + PanelFrom->Cells[1][i];
    	}
        movedFrom += '\0';
    }

    movedFrom += '\0';
    String movedTo = LabelTo->Caption + "\0\0";
    
    SHFILEOPSTRUCT operation;
    ZeroMemory(&operation, sizeof(operation));
    operation.hwnd  = ManagerForm->Handle;
    operation.wFunc = FO_MOVE;
    operation.pFrom = movedFrom.c_str();
    operation.pTo = movedTo.c_str();
    operation.fFlags = 0;
    SHFileOperation(&operation);

    UpdateComponents();
}



void __fastcall TManagerForm::ButtonMoveClick(TObject *Sender)
{
	if (selectedPanel == 1) 
    	Move(LeftDirectoryListBox, LeftPanel, LeftFileListBox, RightDirectoryPath);
    else 
    	Move(RightDirectoryListBox, RightPanel, RightFileListBox, LeftDirectoryPath);
}



void __fastcall TManagerForm::Copy(TDirectoryListBox *DirectoryListBoxFrom, TStringGrid *PanelFrom, TFileListBox *FileListBoxFrom, TLabel *LabelTo)
{
    int topSelectedRow = max(PanelFrom->Selection.Top, 2);
    int bottomSelectedRow = PanelFrom->Selection.Bottom;
    String copiedFrom = "";

    for (int i = topSelectedRow; i <= bottomSelectedRow; ++i)
    {
    	if (PanelFrom->Cells[3][i] != "<Папка>")
        {
        	int j = i - 1 - DirectoryListBoxFrom->Count + DirectoryListBoxFrom->ItemIndex;
        	if (DirectoryListBoxFrom->ItemIndex == 0)
        		copiedFrom += DirectoryListBoxFrom->GetItemPath(DirectoryListBoxFrom->ItemIndex) + ExtractFileName(FileListBoxFrom->Items->Strings[j]);
            else 
            	copiedFrom += DirectoryListBoxFrom->GetItemPath(DirectoryListBoxFrom->ItemIndex) + "\\" + ExtractFileName(FileListBoxFrom->Items->Strings[j]);
        }
        else if (PanelFrom->Cells[3][i] == "<Папка>")
        {
        	if (DirectoryListBoxFrom->ItemIndex == 0)
        		copiedFrom += DirectoryListBoxFrom->Directory + PanelFrom->Cells[1][i];
    		else 
            	copiedFrom += DirectoryListBoxFrom->Directory + "\\" + PanelFrom->Cells[1][i];
    	}
        copiedFrom += '\0';
    }

    copiedFrom += '\0';
    String copiedTo = LabelTo->Caption + "\0\0";
    
    SHFILEOPSTRUCT operation;
    ZeroMemory(&operation, sizeof(operation));
    operation.hwnd  = ManagerForm->Handle;
    operation.wFunc = FO_COPY;
    operation.pFrom = copiedFrom.c_str();
    operation.pTo = copiedTo.c_str();
    operation.fFlags = 0;
    SHFileOperation(&operation);

    UpdateComponents();
}



void __fastcall TManagerForm::ButtonCopyClick(TObject *Sender)
{
	if (selectedPanel == 1) 
    	Copy(LeftDirectoryListBox, LeftPanel, LeftFileListBox, RightDirectoryPath);
    else 
    	Copy(RightDirectoryListBox, RightPanel, RightFileListBox, LeftDirectoryPath);		
}
