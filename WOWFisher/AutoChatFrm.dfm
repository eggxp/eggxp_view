object FrmAutoChat: TFrmAutoChat
  Left = 0
  Top = 0
  ClientHeight = 483
  ClientWidth = 719
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 719
    Height = 41
    Align = alTop
    TabOrder = 0
    object btActive: TButton
      Left = 600
      Top = 11
      Width = 75
      Height = 25
      Caption = #21551#21160'/'#20572#27490
      TabOrder = 0
      OnClick = btActiveClick
    end
    object edtText: TEdit
      Left = 16
      Top = 11
      Width = 409
      Height = 21
      TabOrder = 1
    end
    object btSet: TButton
      Left = 431
      Top = 9
      Width = 75
      Height = 25
      Caption = 'btSet'
      TabOrder = 2
      OnClick = btSetClick
    end
  end
  object Panel2: TPanel
    Left = 0
    Top = 41
    Width = 719
    Height = 442
    Align = alClient
    TabOrder = 1
    object Splitter1: TSplitter
      Left = 313
      Top = 1
      Height = 440
      ExplicitLeft = 240
      ExplicitTop = 128
      ExplicitHeight = 100
    end
    object gbAll: TGroupBox
      Left = 316
      Top = 1
      Width = 402
      Height = 440
      Align = alClient
      Caption = 'gbAll'
      TabOrder = 0
      object lvAll: TListView
        Left = 2
        Top = 15
        Width = 398
        Height = 423
        Align = alClient
        Columns = <
          item
            Caption = 'Index'
          end
          item
            Caption = 'PlayerName'
            Width = 100
          end
          item
            Caption = 'GuildName'
          end
          item
            Caption = '1v1'
          end
          item
            Caption = 'Class'
          end
          item
            Caption = 'Race'
          end
          item
            Caption = 'ZoneID'
          end>
        GridLines = True
        HideSelection = False
        MultiSelect = True
        OwnerData = True
        ReadOnly = True
        RowSelect = True
        TabOrder = 0
        ViewStyle = vsReport
        OnData = lvAllData
      end
    end
    object gbProcessing: TGroupBox
      Left = 1
      Top = 1
      Width = 312
      Height = 440
      Align = alLeft
      Caption = 'GroupBox1'
      TabOrder = 1
      object lvProcess: TListView
        Left = 2
        Top = 15
        Width = 308
        Height = 423
        Align = alClient
        Columns = <
          item
            Caption = 'Index'
          end
          item
            Caption = 'AreaName'
            Width = 100
          end
          item
            Caption = 'PlayerCnt'
          end
          item
            Caption = 'ProcessCnt'
          end
          item
            Caption = 'Expired'
          end>
        GridLines = True
        HideSelection = False
        MultiSelect = True
        OwnerData = True
        ReadOnly = True
        RowSelect = True
        TabOrder = 0
        ViewStyle = vsReport
        OnData = lvProcessData
      end
    end
  end
  object Timer1: TTimer
    OnTimer = Timer1Timer
    Left = 512
    Top = 240
  end
end
