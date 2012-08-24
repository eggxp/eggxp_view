object frmBlock: TfrmBlock
  Left = 0
  Top = 0
  Caption = 'Block'
  ClientHeight = 380
  ClientWidth = 880
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 13
  object Splitter1: TSplitter
    Left = 709
    Top = 0
    Height = 380
    Align = alRight
    ExplicitLeft = 672
    ExplicitTop = 144
    ExplicitHeight = 100
  end
  object lvAll: TListView
    Left = 0
    Top = 0
    Width = 709
    Height = 380
    Align = alClient
    Columns = <
      item
        Caption = 'Index'
      end
      item
        Caption = 'Time'
        Width = 100
      end
      item
        Caption = 'Dir'
      end
      item
        Caption = 'Len'
      end
      item
        Caption = 'OPcode'
        Width = 100
      end
      item
        Caption = 'Data'
        Width = 800
      end>
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = #23435#20307
    Font.Style = []
    GridLines = True
    MultiSelect = True
    OwnerData = True
    OwnerDraw = True
    ReadOnly = True
    RowSelect = True
    ParentFont = False
    PopupMenu = PopupMenu1
    TabOrder = 0
    ViewStyle = vsReport
    OnClick = lvAllClick
    OnCustomDrawItem = lvAllCustomDrawItem
    OnCustomDrawSubItem = lvAllCustomDrawSubItem
    OnData = lvAllData
  end
  object Panel1: TPanel
    Left = 712
    Top = 0
    Width = 168
    Height = 380
    Align = alRight
    TabOrder = 1
    object btNext: TButton
      Left = 24
      Top = 40
      Width = 75
      Height = 25
      Caption = 'Next'
      TabOrder = 0
      OnClick = btNextClick
    end
    object btJmp: TButton
      Left = 24
      Top = 120
      Width = 75
      Height = 25
      Caption = 'JMP'
      TabOrder = 1
      OnClick = btJmpClick
    end
    object cbBlockOnly: TCheckBox
      Left = 6
      Top = 198
      Width = 147
      Height = 17
      Caption = 'Block Only'
      TabOrder = 2
      OnClick = cbBlockOnlyClick
    end
    object btResetBlockOnly: TButton
      Left = 24
      Top = 221
      Width = 105
      Height = 25
      Caption = 'btResetBlockOnly'
      TabOrder = 3
      OnClick = btResetBlockOnlyClick
    end
    object edtNextCount: TCSpinEdit
      Left = 24
      Top = 92
      Width = 121
      Height = 22
      MaxValue = 9999
      MinValue = 1
      TabOrder = 4
      Value = 1
    end
    object StaticText1: TStaticText
      Left = 24
      Top = 71
      Width = 59
      Height = 17
      Caption = 'Next Count'
      TabOrder = 5
    end
  end
  object Timer1: TTimer
    OnTimer = Timer1Timer
    Left = 448
    Top = 48
  end
  object PopupMenu1: TPopupMenu
    Left = 376
    Top = 160
    object miCopy: TMenuItem
      Caption = #22797#21046
      object CopyDetail1: TMenuItem
        Caption = 'CopyDetail'
        OnClick = CopyDetail1Click
      end
      object CopyLine1: TMenuItem
        Caption = 'CopyLine'
        OnClick = CopyLine1Click
      end
      object CopyCVS1: TMenuItem
        Caption = 'CopyCVS'
        OnClick = CopyCVS1Click
      end
    end
    object N1: TMenuItem
      Caption = '-'
    end
    object miMoveHere: TMenuItem
      Caption = #36208#21040#36825#37324
      OnClick = miMoveHereClick
    end
    object miJumpHere: TMenuItem
      Caption = #36339#21040#36825#37324
      OnClick = miJumpHereClick
    end
    object miProcessCurrent: TMenuItem
      Caption = #22788#29702#36825#20010
      OnClick = miProcessCurrentClick
    end
  end
end
