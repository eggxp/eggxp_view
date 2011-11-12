object FrmValuesUpdate: TFrmValuesUpdate
  Left = 0
  Top = 0
  Caption = 'ValuesUpdateFrm'
  ClientHeight = 525
  ClientWidth = 689
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
    Left = 485
    Top = 0
    Height = 525
    Align = alRight
    ExplicitLeft = 216
    ExplicitTop = 160
    ExplicitHeight = 100
  end
  object Panel1: TPanel
    Left = 488
    Top = 0
    Width = 201
    Height = 525
    Align = alRight
    TabOrder = 0
    object memComment: TMemo
      Left = 1
      Top = 1
      Width = 199
      Height = 405
      Align = alClient
      Color = clInfoBk
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGreen
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      ScrollBars = ssBoth
      TabOrder = 0
    end
    object Panel6: TPanel
      Left = 1
      Top = 406
      Width = 199
      Height = 118
      Align = alBottom
      TabOrder = 1
      object btPackOutput: TButton
        Left = 5
        Top = 16
        Width = 145
        Height = 25
        Caption = #35299#26512'->'#23553#21253
        TabOrder = 0
        OnClick = btPackOutputClick
      end
    end
  end
  object Panel2: TPanel
    Left = 0
    Top = 0
    Width = 485
    Height = 525
    Align = alClient
    TabOrder = 1
    object GroupBox1: TGroupBox
      Left = 1
      Top = 400
      Width = 483
      Height = 124
      Align = alBottom
      Caption = #23553#21253#36755#20837
      TabOrder = 0
      object edtPack: TMemo
        Left = 2
        Top = 42
        Width = 479
        Height = 80
        Align = alBottom
        ScrollBars = ssBoth
        TabOrder = 0
        OnDblClick = edtPackDblClick
      end
      object cbPackHead: TComboBox
        Left = 1
        Top = 15
        Width = 233
        Height = 21
        TabOrder = 1
      end
      object btPackInput: TButton
        Left = 296
        Top = 13
        Width = 145
        Height = 25
        Caption = #23553#21253'->'#35299#26512
        TabOrder = 2
        OnClick = btPackInputClick
      end
    end
    object Panel3: TPanel
      Left = 1
      Top = 1
      Width = 483
      Height = 399
      Align = alClient
      TabOrder = 1
      object Panel4: TPanel
        Left = 1
        Top = 129
        Width = 481
        Height = 269
        Align = alClient
        TabOrder = 0
        object lvValues: TListView
          Left = 1
          Top = 1
          Width = 479
          Height = 267
          Align = alClient
          Columns = <
            item
              Caption = 'Name'
              Width = 100
            end
            item
              Caption = 'Value'
              Width = 200
            end
            item
              Caption = 'Pos'
              Width = 100
            end>
          GridLines = True
          HideSelection = False
          MultiSelect = True
          OwnerData = True
          ReadOnly = True
          RowSelect = True
          PopupMenu = pmWrite
          TabOrder = 0
          ViewStyle = vsReport
          OnData = lvValuesData
        end
      end
      object Panel5: TPanel
        Left = 1
        Top = 1
        Width = 481
        Height = 128
        Align = alTop
        TabOrder = 1
        object Panel7: TPanel
          Left = 1
          Top = 1
          Width = 479
          Height = 126
          Align = alClient
          TabOrder = 0
          object lvBlocks: TListView
            Left = 1
            Top = 1
            Width = 477
            Height = 124
            Align = alClient
            Columns = <
              item
                Caption = 'Blocks'
              end
              item
                Caption = 'UpdateType'
                Width = 100
              end
              item
                Caption = 'PosStart'
                Width = 100
              end
              item
                Caption = 'PosEnd'
                Width = 100
              end
              item
                Caption = 'ValueCnt'
                Width = 100
              end
              item
                Caption = 'MaskPos'
                Width = 100
              end
              item
                Caption = 'MaskSize'
                Width = 100
              end>
            GridLines = True
            HideSelection = False
            MultiSelect = True
            OwnerData = True
            ReadOnly = True
            RowSelect = True
            TabOrder = 0
            ViewStyle = vsReport
            OnClick = lvBlocksClick
            OnData = lvBlocksData
          end
        end
      end
    end
  end
  object pmWrite: TPopupMenu
    Left = 336
    Top = 232
    object miWriteInt: TMenuItem
      Caption = #20889#20837#25972#25968
      OnClick = miWriteIntClick
    end
    object miWriteFloat: TMenuItem
      Caption = #20889#20837#28014#28857
      OnClick = miWriteFloatClick
    end
    object miWriteByte: TMenuItem
      Caption = #20889#20837'Byte'
      OnClick = miWriteByteClick
    end
    object miChangeIndex: TMenuItem
      Caption = #20462#25913'index'
      OnClick = miChangeIndexClick
    end
    object N1: TMenuItem
      Caption = '-'
    end
    object miAddValue: TMenuItem
      Caption = #28155#21152
      OnClick = miAddValueClick
    end
    object miDelete: TMenuItem
      Caption = #21024#38500
      OnClick = miDeleteClick
    end
  end
end
