object ManagerForm: TManagerForm
  Left = 0
  Top = 0
  Caption = 'File Manager'
  ClientHeight = 711
  ClientWidth = 1366
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  Position = poDesigned
  Visible = True
  WindowState = wsMaximized
  OnCreate = FormCreate
  OnKeyDown = FormKeyDown
  PixelsPerInch = 96
  TextHeight = 13
  object LeftDirectoryPath: TLabel
    Left = 8
    Top = 41
    Width = 85
    Height = 13
    Caption = 'LeftDirectoryPath'
  end
  object RightDirectoryPath: TLabel
    Left = 696
    Top = 41
    Width = 91
    Height = 13
    Caption = 'RightDirectoryPath'
  end
  object LeftDirectoryListBox: TDirectoryListBox
    Left = 8
    Top = 70
    Width = 145
    Height = 345
    ParentShowHint = False
    ShowHint = True
    TabOrder = 0
    OnChange = LeftDirectoryListBoxChange
  end
  object RightFileListBox: TFileListBox
    Left = 920
    Top = 70
    Width = 145
    Height = 97
    ItemHeight = 13
    TabOrder = 12
  end
  object LeftFileListBox: TFileListBox
    Left = 208
    Top = 70
    Width = 145
    Height = 163
    ItemHeight = 13
    TabOrder = 11
  end
  object RightDirectoryListBox: TDirectoryListBox
    Left = 696
    Top = 70
    Width = 169
    Height = 299
    TabOrder = 10
    OnChange = RightDirectoryListBoxChange
  end
  object ButtonCreate: TButton
    Left = 472
    Top = 670
    Width = 169
    Height = 25
    Caption = 'F7   '#1057#1086#1079#1076#1072#1090#1100
    TabOrder = 1
    OnClick = ButtonCreateClick
  end
  object ButtonDelete: TButton
    Left = 728
    Top = 670
    Width = 169
    Height = 25
    Caption = 'F8   '#1059#1076#1072#1083#1080#1090#1100
    TabOrder = 2
    OnClick = ButtonDeleteClick
  end
  object ButtonRename: TButton
    Left = 960
    Top = 670
    Width = 169
    Height = 25
    Caption = 'F9   '#1055#1077#1088#1077#1080#1084#1077#1085#1086#1074#1072#1090#1100
    TabOrder = 3
    OnClick = ButtonRenameClick
  end
  object LeftDriveComboBox: TDriveComboBox
    Left = 8
    Top = 8
    Width = 145
    Height = 19
    TabOrder = 4
    TextCase = tcUpperCase
    OnChange = LeftDriveComboBoxChange
  end
  object RightDriveComboBox: TDriveComboBox
    Left = 696
    Top = 8
    Width = 145
    Height = 19
    TabOrder = 7
    TextCase = tcUpperCase
    OnChange = RightDriveComboBoxChange
  end
  object LeftFilterComboBox: TFilterComboBox
    Left = 176
    Top = 8
    Width = 145
    Height = 21
    Filter = 
      #1042#1089#1077' '#1092#1072#1081#1083#1099'|*.*|.exe|*.exe|.com|*.com|.doc|*.doc|.xls|*.xls|.txt|*' +
      '.txt|.ppt|*.ppt|.rar|*.rar|.html|*.html|.mp4|*.mp4|.bmp|*.bmp|.j' +
      'pg|*.jpg|.gif|*.gif|.mp3|*.mp3|.mpeg|*.mpeg|.avi|*.avi|.zip|*.zi' +
      'p'
    TabOrder = 8
    OnChange = LeftFilterComboBoxChange
  end
  object RightFilterComboBox: TFilterComboBox
    Left = 864
    Top = 8
    Width = 145
    Height = 21
    Filter = 
      #1042#1089#1077' '#1092#1072#1081#1083#1099'|*.*|.exe|*.exe|.com|*.com|.doc|*.doc|.xls|*.xls|.txt|*' +
      '.txt|.ppt|*.ppt|.rar|*.rar|.html|*.html|.mp4|*.mp4|.bmp|*.bmp|.j' +
      'pg|*.jpg|.gif|*.gif|.mp3|*.mp3|.mpeg|*.mpeg|.avi|*.avi|.zip|*.zi' +
      'p'
    TabOrder = 9
    OnChange = RightFilterComboBoxChange
  end
  object ButtonExit: TButton
    Left = 1189
    Top = 670
    Width = 169
    Height = 25
    Caption = 'Alt+F4   '#1042#1099#1093#1086#1076
    TabOrder = 13
    OnClick = ButtonExitClick
  end
  object LeftPanel: TStringGrid
    Left = 8
    Top = 60
    Width = 665
    Height = 597
    FixedCols = 0
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goRowSelect]
    TabOrder = 5
    OnClick = LeftPanelClick
    OnDblClick = LeftPanelDblClick
    OnDrawCell = LeftPanelDrawCell
    OnKeyDown = LeftPanelKeyDown
    OnSelectCell = LeftPanelSelectCell
    ColWidths = (
      23
      337
      73
      83
      141)
    RowHeights = (
      24
      24
      24
      24
      24)
  end
  object RightPanel: TStringGrid
    Left = 693
    Top = 60
    Width = 665
    Height = 597
    FixedCols = 0
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goRowSelect]
    TabOrder = 6
    OnClick = RightPanelClick
    OnDblClick = RightPanelDblClick
    OnDrawCell = RightPanelDrawCell
    OnKeyDown = RightPanelKeyDown
    OnSelectCell = RightPanelSelectCell
    ColWidths = (
      23
      337
      73
      83
      141)
    RowHeights = (
      24
      24
      24
      24
      24)
  end
  object ButtonMove: TButton
    Left = 240
    Top = 670
    Width = 169
    Height = 25
    Caption = 'F6   '#1055#1077#1088#1077#1084#1077#1089#1090#1080#1090#1100
    TabOrder = 14
    OnClick = ButtonMoveClick
  end
  object ButtonCopy: TButton
    Left = 8
    Top = 670
    Width = 169
    Height = 25
    Caption = 'F5   '#1050#1086#1087#1080#1088#1086#1074#1072#1090#1100
    TabOrder = 15
    OnClick = ButtonCopyClick
  end
  object ImageList: TImageList
    Left = 344
    Top = 16
  end
end
