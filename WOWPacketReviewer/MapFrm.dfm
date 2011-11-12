object FrmMap: TFrmMap
  Left = 0
  Top = 0
  Caption = 'FrmMap'
  ClientHeight = 1007
  ClientWidth = 1299
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  WindowState = wsMaximized
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Splitter1: TSplitter
    Left = 0
    Top = 813
    Width = 1299
    Height = 3
    Cursor = crVSplit
    Align = alBottom
    ExplicitTop = 217
    ExplicitWidth = 320
  end
  object Panel1: TPanel
    Left = 0
    Top = 816
    Width = 1299
    Height = 191
    Align = alBottom
    TabOrder = 0
    object CGauge1: TCGauge
      Left = 1
      Top = 176
      Width = 1297
      Height = 14
      Align = alBottom
    end
    object PageControl1: TPageControl
      Left = 1
      Top = 1
      Width = 1297
      Height = 175
      ActivePage = TabSheet1
      Align = alClient
      TabOrder = 0
      object TabSheet1: TTabSheet
        Caption = 'Map'
        ExplicitLeft = 0
        ExplicitTop = 0
        ExplicitWidth = 0
        ExplicitHeight = 0
        object lvMaps: TListView
          Left = 0
          Top = 0
          Width = 1289
          Height = 147
          Align = alClient
          Columns = <>
          GridLines = True
          HideSelection = False
          OwnerData = True
          ReadOnly = True
          RowSelect = True
          PopupMenu = pmMaps
          TabOrder = 0
          ViewStyle = vsReport
          OnClick = lvMapsClick
          OnData = lvMapsData
        end
      end
      object TabSheet2: TTabSheet
        Caption = 'Calc'
        ImageIndex = 1
        ExplicitLeft = 0
        ExplicitTop = 0
        ExplicitWidth = 0
        ExplicitHeight = 0
        object labCurXY: TLabel
          Left = 376
          Top = 56
          Width = 43
          Height = 13
          Caption = 'labCurXY'
        end
        object labRegionInfo: TLabel
          Left = 376
          Top = 88
          Width = 67
          Height = 13
          Caption = 'labRegionInfo'
        end
        object edtPosx: TEdit
          Left = 16
          Top = 16
          Width = 121
          Height = 21
          TabOrder = 0
          Text = 'edtPosx'
        end
        object edtPosy: TEdit
          Left = 168
          Top = 16
          Width = 121
          Height = 21
          TabOrder = 1
          Text = 'edtPosy'
        end
        object btCalc: TButton
          Left = 279
          Top = 14
          Width = 75
          Height = 25
          Caption = 'btCalc'
          TabOrder = 2
          OnClick = btCalcClick
        end
        object memOutput: TMemo
          Left = 16
          Top = 43
          Width = 338
          Height = 94
          Color = clInfoBk
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clGreen
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
          ScrollBars = ssBoth
          TabOrder = 3
        end
        object edtgx: TEdit
          Left = 376
          Top = 16
          Width = 121
          Height = 21
          TabOrder = 4
          Text = 'edtgx'
        end
        object edtgy: TEdit
          Left = 528
          Top = 16
          Width = 121
          Height = 21
          TabOrder = 5
          Text = 'edtgy'
        end
        object btGoto: TButton
          Left = 647
          Top = 14
          Width = 75
          Height = 25
          Caption = 'btGoto'
          TabOrder = 6
          OnClick = btGotoClick
        end
      end
    end
  end
  object Panel2: TPanel
    Left = 0
    Top = 0
    Width = 1299
    Height = 813
    Align = alClient
    TabOrder = 1
    object Splitter2: TSplitter
      Left = 395
      Top = 1
      Height = 811
      ExplicitLeft = 288
      ExplicitTop = 112
      ExplicitHeight = 100
    end
    object ScrollBox2: TScrollBox
      Left = 398
      Top = 1
      Width = 900
      Height = 811
      Align = alClient
      TabOrder = 0
      object imgObsMap: TImage
        Left = 0
        Top = 0
        Width = 641
        Height = 512
        AutoSize = True
        OnMouseMove = imgObsMapMouseMove
      end
    end
    object Panel3: TPanel
      Left = 1
      Top = 1
      Width = 394
      Height = 811
      Align = alLeft
      TabOrder = 1
      object dgVMap: TDrawGrid
        Left = 1
        Top = 393
        Width = 392
        Height = 417
        Align = alClient
        ColCount = 64
        DefaultColWidth = 5
        DefaultRowHeight = 5
        FixedCols = 0
        RowCount = 64
        FixedRows = 0
        TabOrder = 0
        OnDrawCell = dgVMapDrawCell
      end
      object dgMap: TDrawGrid
        Left = 1
        Top = 1
        Width = 392
        Height = 392
        Align = alTop
        ColCount = 64
        DefaultColWidth = 5
        DefaultRowHeight = 5
        FixedCols = 0
        RowCount = 64
        FixedRows = 0
        TabOrder = 1
        OnDrawCell = dgMapDrawCell
        OnSelectCell = dgMapSelectCell
      end
    end
  end
  object pmMaps: TPopupMenu
    Left = 344
    Top = 696
    object miOutput: TMenuItem
      Caption = #23548#20986
      OnClick = miOutputClick
    end
  end
  object Timer1: TTimer
    OnTimer = Timer1Timer
    Left = 168
    Top = 600
  end
end
