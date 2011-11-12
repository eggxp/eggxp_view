object FrmDBCViewer: TFrmDBCViewer
  Left = 0
  Top = 0
  Caption = 'FrmDBCViewer'
  ClientHeight = 521
  ClientWidth = 846
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 13
  object CGauge1: TCGauge
    Left = 0
    Top = 504
    Width = 846
    Height = 17
    Align = alBottom
  end
  object labMsg: TLabel
    Left = 16
    Top = 505
    Width = 4
    Height = 13
    Caption = '-'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clYellow
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object Panel3: TPanel
    Left = 0
    Top = 0
    Width = 846
    Height = 504
    Align = alClient
    TabOrder = 0
    object Splitter1: TSplitter
      Left = 186
      Top = 1
      Height = 502
      ExplicitLeft = 304
      ExplicitTop = 136
      ExplicitHeight = 100
    end
    object Panel1: TPanel
      Left = 1
      Top = 1
      Width = 185
      Height = 502
      Align = alLeft
      TabOrder = 0
      object lvDataNames: TListView
        Left = 1
        Top = 1
        Width = 183
        Height = 500
        Align = alClient
        Columns = <
          item
            Caption = 'Name'
            Width = 100
          end
          item
            Caption = 'Cnt'
          end>
        GridLines = True
        HideSelection = False
        ReadOnly = True
        RowSelect = True
        TabOrder = 0
        ViewStyle = vsReport
        OnClick = lvDataNamesClick
      end
    end
    object Panel2: TPanel
      Left = 189
      Top = 1
      Width = 656
      Height = 502
      Align = alClient
      TabOrder = 1
      object lvDatas: TListView
        Left = 1
        Top = 1
        Width = 654
        Height = 500
        Align = alClient
        Columns = <
          item
            Caption = 'Name'
            Width = 200
          end>
        GridLines = True
        HideSelection = False
        OwnerData = True
        ReadOnly = True
        RowSelect = True
        PopupMenu = pmOutput
        TabOrder = 0
        ViewStyle = vsReport
        OnData = lvDatasData
      end
    end
  end
  object pmOutput: TPopupMenu
    Left = 200
    Top = 192
    object miOutput: TMenuItem
      Caption = #23548#20986#21040#25991#20214
      OnClick = miOutputClick
    end
  end
end
