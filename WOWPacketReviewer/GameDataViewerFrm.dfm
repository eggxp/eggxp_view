object FrmGameDataViewer: TFrmGameDataViewer
  Left = 0
  Top = 0
  Caption = 'FrmGameDataViewer'
  ClientHeight = 392
  ClientWidth = 478
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Splitter1: TSplitter
    Left = 0
    Top = 197
    Width = 478
    Height = 3
    Cursor = crVSplit
    Align = alBottom
    ExplicitTop = 0
    ExplicitWidth = 249
  end
  object Panel1: TPanel
    Left = 0
    Top = 200
    Width = 478
    Height = 192
    Align = alBottom
    TabOrder = 0
    object Panel3: TPanel
      Left = 1
      Top = 1
      Width = 476
      Height = 41
      Align = alTop
      TabOrder = 0
      object btReset: TButton
        Left = 8
        Top = 6
        Width = 75
        Height = 25
        Caption = 'btReset'
        TabOrder = 0
        OnClick = btResetClick
      end
      object btUp: TButton
        Left = 89
        Top = 6
        Width = 75
        Height = 25
        Caption = 'btUp'
        TabOrder = 1
        OnClick = btUpClick
      end
      object btGo: TButton
        Left = 392
        Top = 6
        Width = 75
        Height = 25
        Caption = 'btGo'
        TabOrder = 2
        OnClick = btGoClick
      end
      object btReload: TButton
        Left = 264
        Top = 6
        Width = 75
        Height = 25
        Caption = 'btReload'
        TabOrder = 3
        OnClick = btReloadClick
      end
      object btClearData: TButton
        Left = 169
        Top = 6
        Width = 75
        Height = 25
        Caption = 'btClearData'
        TabOrder = 4
        OnClick = btClearDataClick
      end
    end
    object lvFiberState: TListView
      Left = 1
      Top = 42
      Width = 476
      Height = 149
      Align = alClient
      Columns = <
        item
          Caption = 'FiberName'
          Width = 100
        end
        item
          Caption = 'WaitState'
          Width = 200
        end
        item
          Caption = 'waittime'
          Width = 100
        end
        item
          Caption = 'Active'
        end>
      GridLines = True
      HideSelection = False
      MultiSelect = True
      OwnerData = True
      ReadOnly = True
      RowSelect = True
      TabOrder = 1
      ViewStyle = vsReport
      OnData = lvFiberStateData
    end
  end
  object Panel2: TPanel
    Left = 0
    Top = 0
    Width = 478
    Height = 197
    Align = alClient
    TabOrder = 1
    object lvAll: TListView
      Left = 1
      Top = 1
      Width = 476
      Height = 195
      Align = alClient
      Columns = <
        item
          Caption = 'Key'
          Width = 100
        end
        item
          Caption = 'Value'
          Width = 100
        end
        item
          Caption = 'cnt'
        end
        item
          Caption = 'Path'
          Width = 150
        end>
      GridLines = True
      HideSelection = False
      MultiSelect = True
      OwnerData = True
      ReadOnly = True
      RowSelect = True
      PopupMenu = pmMenu
      TabOrder = 0
      ViewStyle = vsReport
      OnData = lvAllData
      OnDblClick = lvAllDblClick
    end
  end
  object Timer1: TTimer
    OnTimer = Timer1Timer
    Left = 120
    Top = 72
  end
  object pmMenu: TPopupMenu
    Left = 344
    Top = 128
    object miCopy: TMenuItem
      Caption = #22797#21046
      OnClick = miCopyClick
    end
  end
end
