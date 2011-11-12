object MainFrm: TMainFrm
  Left = 0
  Top = 0
  Caption = 'MainFrm'
  ClientHeight = 301
  ClientWidth = 554
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  PixelsPerInch = 96
  TextHeight = 13
  object PageControl1: TPageControl
    Left = 0
    Top = 0
    Width = 554
    Height = 301
    ActivePage = TabSheet5
    Align = alClient
    TabOrder = 0
    object TabSheet1: TTabSheet
      Caption = #29983#25104#20805#20540#21345
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object labThreadState: TLabel
        Left = 40
        Top = 160
        Width = 74
        Height = 13
        Caption = 'labThreadState'
      end
      object GroupBox1: TGroupBox
        Left = 3
        Top = 3
        Width = 246
        Height = 134
        Caption = #20805#20540#21345#29983#25104
        TabOrder = 0
        object Label1: TLabel
          Left = 16
          Top = 24
          Width = 64
          Height = 13
          Caption = #20805#20540#21345#31867#22411':'
        end
        object Label2: TLabel
          Left = 16
          Top = 59
          Width = 64
          Height = 13
          Caption = #20805#20540#21345#25968#37327':'
        end
        object btCreateCare: TButton
          Left = 158
          Top = 106
          Width = 75
          Height = 25
          Caption = #29983#25104
          TabOrder = 0
          OnClick = btCreateCareClick
        end
        object cbCardType: TComboBox
          Left = 102
          Top = 21
          Width = 115
          Height = 21
          Style = csDropDownList
          ItemIndex = 0
          TabOrder = 1
          Text = #20813#36153#21345'(7'#22825')'
          Items.Strings = (
            #20813#36153#21345'(7'#22825')'
            #20813#36153#21345'(1'#22825')'
            #25910#36153#21345'(7'#22825')'
            #25910#36153#21345'(1'#22825')')
        end
        object edtCardCount: TCSpinEdit
          Left = 102
          Top = 56
          Width = 115
          Height = 22
          TabOrder = 2
          Value = 100
        end
      end
      object btQueryCard: TButton
        Left = 400
        Top = 232
        Width = 115
        Height = 25
        Caption = #25968#25454#24211#24635#21345#37327#26597#35810
        TabOrder = 1
        OnClick = btQueryCardClick
      end
      object btRefreshCardTypes: TButton
        Left = 272
        Top = 22
        Width = 97
        Height = 25
        Caption = #21047#26032#21345#31867#22411#33756#21333
        TabOrder = 2
        OnClick = btRefreshCardTypesClick
      end
    end
    object TabSheet5: TTabSheet
      Caption = #21462#20805#20540#21345
      ImageIndex = 4
      object GroupBox2: TGroupBox
        Left = 0
        Top = 0
        Width = 546
        Height = 134
        Align = alTop
        Caption = #21462#20805#20540#21345
        TabOrder = 0
        object Label4: TLabel
          Left = 16
          Top = 24
          Width = 64
          Height = 13
          Caption = #20805#20540#21345#31867#22411':'
        end
        object Label5: TLabel
          Left = 16
          Top = 59
          Width = 52
          Height = 13
          Caption = #21462#20986#25968#37327':'
        end
        object btGetCard: TButton
          Left = 158
          Top = 98
          Width = 75
          Height = 25
          Caption = #21462#20986
          TabOrder = 0
          OnClick = btGetCardClick
        end
        object cbGetCardType: TComboBox
          Left = 102
          Top = 21
          Width = 115
          Height = 21
          Style = csDropDownList
          ItemIndex = 0
          TabOrder = 1
          Text = #20813#36153#21345'(7'#22825')'
          Items.Strings = (
            #20813#36153#21345'(7'#22825')'
            #20813#36153#21345'(1'#22825')'
            #25910#36153#21345'(7'#22825')'
            #25910#36153#21345'(1'#22825')')
        end
        object edtGetCardNum: TCSpinEdit
          Left = 102
          Top = 56
          Width = 115
          Height = 22
          TabOrder = 2
          Value = 1
        end
      end
      object memGetResult: TMemo
        Left = 0
        Top = 134
        Width = 546
        Height = 139
        Align = alClient
        Color = clMoneyGreen
        Font.Charset = ANSI_CHARSET
        Font.Color = clMaroon
        Font.Height = -13
        Font.Name = #23435#20307
        Font.Style = []
        ParentFont = False
        ReadOnly = True
        ScrollBars = ssBoth
        TabOrder = 1
      end
    end
    object TabSheet3: TTabSheet
      Caption = #32473#29992#25143#20805#20540
      ImageIndex = 2
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object Label3: TLabel
        Left = 16
        Top = 32
        Width = 135
        Height = 13
        Caption = #20174'ChargeList'#20013#32473#29609#23478#20805#20540
      end
      object btCharge: TButton
        Left = 176
        Top = 27
        Width = 75
        Height = 25
        Caption = #20805#20540
        TabOrder = 0
        OnClick = btChargeClick
      end
    end
    object TabSheet4: TTabSheet
      Caption = 'Info'
      ImageIndex = 3
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object memLog: TMemo
        Left = 0
        Top = 0
        Width = 546
        Height = 273
        Align = alClient
        Color = clMoneyGreen
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clMaroon
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
        ReadOnly = True
        ScrollBars = ssBoth
        TabOrder = 0
      end
    end
    object TabSheet2: TTabSheet
      Caption = 'Thread'
      ImageIndex = 1
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object lvThread: TListView
        Left = 0
        Top = 0
        Width = 546
        Height = 273
        Align = alClient
        Columns = <
          item
            Caption = 'ThreadID'
            Width = 100
          end
          item
            Caption = 'Name'
            Width = 100
          end
          item
            Caption = 'State'
            Width = 200
          end>
        GridLines = True
        HideSelection = False
        MultiSelect = True
        OwnerData = True
        ReadOnly = True
        RowSelect = True
        TabOrder = 0
        ViewStyle = vsReport
        OnData = lvThreadData
      end
    end
  end
  object Timer1: TTimer
    OnTimer = Timer1Timer
    Left = 512
    Top = 176
  end
  object ApplicationEvents1: TApplicationEvents
    OnMinimize = ApplicationEvents1Minimize
    Left = 520
    Top = 80
  end
  object TrayIcon1: TTrayIcon
    Visible = True
    OnDblClick = TrayIcon1DblClick
    OnMouseUp = TrayIcon1MouseUp
    Left = 512
    Top = 128
  end
  object pmTray: TPopupMenu
    Left = 520
    Top = 32
    object miCloseWnd: TMenuItem
      Caption = #20851#38381
      OnClick = miCloseWndClick
    end
  end
end
