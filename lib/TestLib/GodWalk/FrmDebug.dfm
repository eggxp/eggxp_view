object DebugFrm: TDebugFrm
  Left = 0
  Top = 0
  Caption = 'DebugFrm'
  ClientHeight = 431
  ClientWidth = 528
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Splitter1: TSplitter
    Left = 0
    Top = 0
    Width = 528
    Height = 3
    Cursor = crVSplit
    Align = alTop
    ExplicitTop = 273
    ExplicitWidth = 121
  end
  object PageControl1: TPageControl
    Left = 0
    Top = 3
    Width = 528
    Height = 282
    ActivePage = TabSheet1
    Align = alClient
    TabOrder = 0
    object TabSheet1: TTabSheet
      Caption = 'Send'
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object memSend: TMemo
        Left = 0
        Top = 0
        Width = 520
        Height = 254
        Align = alClient
        ScrollBars = ssBoth
        TabOrder = 0
      end
    end
    object TabSheet2: TTabSheet
      Caption = 'Recv'
      ImageIndex = 1
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object memRecv: TMemo
        Left = 0
        Top = 0
        Width = 520
        Height = 254
        Align = alClient
        ScrollBars = ssBoth
        TabOrder = 0
      end
    end
    object TabSheet5: TTabSheet
      Caption = 'All'
      ImageIndex = 2
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object memAll: TMemo
        Left = 0
        Top = 0
        Width = 520
        Height = 254
        Align = alClient
        ScrollBars = ssBoth
        TabOrder = 0
      end
    end
  end
  object cbEnableDebug: TCheckBox
    Left = 431
    Top = 8
    Width = 97
    Height = 17
    Caption = 'Enable'
    Checked = True
    State = cbChecked
    TabOrder = 1
  end
  object PageControl2: TPageControl
    Left = 0
    Top = 285
    Width = 528
    Height = 146
    ActivePage = TabSheet3
    Align = alBottom
    TabOrder = 2
    object TabSheet3: TTabSheet
      Caption = 'Send'
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object memUnShowSend: TMemo
        Left = 0
        Top = 0
        Width = 520
        Height = 118
        Align = alClient
        TabOrder = 0
      end
    end
    object TabSheet4: TTabSheet
      Caption = 'Recv'
      ImageIndex = 1
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object memUnShowRecv: TMemo
        Left = 0
        Top = 0
        Width = 520
        Height = 118
        Align = alClient
        TabOrder = 0
      end
    end
    object TabSheet6: TTabSheet
      Caption = #27169#25311#25509#25910
      ImageIndex = 2
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object Label1: TLabel
        Left = 16
        Top = 16
        Width = 203
        Height = 13
        Caption = #23436#25972#26126#30721#23553#21253'(HEX:'#38271#24230'+'#21629#20196#22836'+'#20869#23481')'
      end
      object edtVRecvData: TEdit
        Left = 16
        Top = 46
        Width = 473
        Height = 21
        TabOrder = 0
      end
      object Button1: TButton
        Left = 16
        Top = 78
        Width = 89
        Height = 25
        Caption = #27169#25311#21457#36865
        TabOrder = 1
        OnClick = Button1Click
      end
    end
  end
  object btClear: TButton
    Left = 357
    Top = 1
    Width = 67
    Height = 25
    Caption = #28165#31354
    TabOrder = 3
    OnClick = btClearClick
  end
  object cbUnShow: TCheckBox
    Left = 191
    Top = 8
    Width = 97
    Height = 17
    Caption = #21551#29992#23631#34109
    TabOrder = 4
  end
  object cbDisUnShow: TCheckBox
    Left = 274
    Top = 8
    Width = 75
    Height = 17
    Caption = #36870#21521#23631#34109
    TabOrder = 5
  end
end
