object Form1: TForm1
  Left = 403
  Top = 259
  Width = 496
  Height = 310
  HorzScrollBar.Visible = False
  VertScrollBar.Visible = False
  Caption = 'Form1'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnClose = FormClose
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Debug: TMemo
    Left = 480
    Top = 16
    Width = 201
    Height = 113
    Lines.Strings = (
      'Debug')
    ReadOnly = True
    ScrollBars = ssBoth
    TabOrder = 0
    Visible = False
  end
  object GroupBox1: TGroupBox
    Left = 87
    Top = 35
    Width = 305
    Height = 201
    Caption = 'Logowanie'
    TabOrder = 1
    object Label1: TLabel
      Left = 24
      Top = 40
      Width = 29
      Height = 13
      Caption = 'Login:'
    end
    object Label2: TLabel
      Left = 24
      Top = 72
      Width = 32
      Height = 13
      Caption = 'Has'#322'o:'
    end
    object Label3: TLabel
      Left = 16
      Top = 160
      Width = 117
      Height = 13
      Caption = 'Nie masz jeszcze konta?'
    end
    object Edit1: TEdit
      Left = 64
      Top = 40
      Width = 129
      Height = 21
      TabOrder = 0
    end
    object MaskEdit1: TMaskEdit
      Left = 64
      Top = 72
      Width = 129
      Height = 21
      PasswordChar = '*'
      TabOrder = 1
    end
    object BitBtn1: TBitBtn
      Left = 64
      Top = 104
      Width = 129
      Height = 25
      Caption = 'Zaloguj'
      TabOrder = 2
      OnClick = BitBtn1Click
    end
    object BitBtn2: TBitBtn
      Left = 144
      Top = 160
      Width = 137
      Height = 17
      Caption = 'Zarejstruj si'#281
      TabOrder = 3
      OnClick = BitBtn2Click
    end
  end
  object GroupBox2: TGroupBox
    Left = 88
    Top = 36
    Width = 305
    Height = 201
    Caption = 'Rejestracja'
    TabOrder = 2
    Visible = False
    object Label4: TLabel
      Left = 64
      Top = 24
      Width = 29
      Height = 13
      Caption = 'Login:'
    end
    object Label5: TLabel
      Left = 64
      Top = 56
      Width = 32
      Height = 13
      Caption = 'Has'#322'o:'
    end
    object Label6: TLabel
      Left = 24
      Top = 88
      Width = 71
      Height = 13
      Caption = 'Powt'#243'rz has'#322'o:'
    end
    object Label7: TLabel
      Left = 64
      Top = 120
      Width = 28
      Height = 13
      Caption = 'Email:'
    end
    object Edit2: TEdit
      Left = 104
      Top = 24
      Width = 137
      Height = 21
      TabOrder = 0
    end
    object Edit3: TEdit
      Left = 104
      Top = 120
      Width = 137
      Height = 21
      TabOrder = 3
    end
    object MaskEdit2: TMaskEdit
      Left = 104
      Top = 56
      Width = 137
      Height = 21
      PasswordChar = '*'
      TabOrder = 1
    end
    object MaskEdit3: TMaskEdit
      Left = 104
      Top = 88
      Width = 137
      Height = 21
      PasswordChar = '*'
      TabOrder = 2
    end
    object BitBtn3: TBitBtn
      Left = 104
      Top = 160
      Width = 137
      Height = 25
      Caption = 'Zarejstruj'
      TabOrder = 4
      OnClick = BitBtn3Click
    end
  end
  object GroupBox3: TGroupBox
    Left = 12
    Top = 8
    Width = 457
    Height = 257
    Caption = 'Chat'
    TabOrder = 3
    Visible = False
    object Label8: TLabel
      Left = 272
      Top = 16
      Width = 119
      Height = 13
      Caption = 'Zalogowani u'#380'ytkownicy:'
    end
    object Label9: TLabel
      Left = 24
      Top = 16
      Width = 61
      Height = 13
      Caption = 'Wiadomo'#347'ci:'
    end
    object Edit4: TEdit
      Left = 16
      Top = 216
      Width = 241
      Height = 21
      MaxLength = 500
      TabOrder = 0
      OnKeyPress = Edit4KeyPress
    end
    object BitBtn4: TBitBtn
      Left = 272
      Top = 216
      Width = 97
      Height = 25
      Caption = 'Wy'#347'lij'
      TabOrder = 1
      OnClick = BitBtn4Click
    end
    object Memo1: TMemo
      Left = 16
      Top = 40
      Width = 233
      Height = 153
      ReadOnly = True
      TabOrder = 2
    end
    object ListBox1: TListBox
      Left = 264
      Top = 40
      Width = 177
      Height = 153
      ExtendedSelect = False
      ItemHeight = 13
      PopupMenu = PopupMenu1
      Sorted = True
      TabOrder = 3
      OnContextPopup = ListBox1ContextPopup
    end
  end
  object ClientSocket1: TClientSocket
    Active = False
    ClientType = ctNonBlocking
    Port = 0
    OnRead = ClientSocket1Read
    OnError = ClientSocket1Error
    Left = 520
    Top = 24
  end
  object PopupMenu1: TPopupMenu
    AutoPopup = False
    Left = 576
    Top = 176
    object Szept1: TMenuItem
      Caption = 'Szept'
      OnClick = Szept1Click
    end
  end
end
