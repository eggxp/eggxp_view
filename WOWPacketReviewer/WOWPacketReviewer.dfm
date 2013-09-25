object WOWReviewerMainFrm: TWOWReviewerMainFrm
  Left = 0
  Top = 263
  Caption = 'Eggxp'#39's WOW Packet Reviewer'
  ClientHeight = 494
  ClientWidth = 789
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesigned
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  PixelsPerInch = 96
  TextHeight = 13
  object Splitter1: TSplitter
    Left = 0
    Top = 491
    Width = 789
    Height = 3
    Cursor = crVSplit
    Align = alBottom
    ExplicitTop = 332
    ExplicitWidth = 44
  end
  object Splitter2: TSplitter
    Left = 0
    Top = 261
    Width = 789
    Height = 3
    Cursor = crVSplit
    Align = alBottom
    ExplicitTop = 153
    ExplicitWidth = 79
  end
  object pcMainControl: TPageControl
    Left = 0
    Top = 41
    Width = 789
    Height = 220
    ActivePage = tsAll
    Align = alClient
    TabOrder = 0
    object tsSend: TTabSheet
      Caption = 'Send'
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object lvSend: TListView
        Left = 0
        Top = 0
        Width = 781
        Height = 192
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
        GridLines = True
        HideSelection = False
        MultiSelect = True
        OwnerData = True
        ReadOnly = True
        RowSelect = True
        PopupMenu = pmAll
        TabOrder = 0
        ViewStyle = vsReport
        OnClick = lvAllClick
        OnData = lvSendData
      end
    end
    object tsRecv: TTabSheet
      Caption = 'Recv'
      ImageIndex = 1
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object lvRecv: TListView
        Left = 0
        Top = 0
        Width = 781
        Height = 192
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
        GridLines = True
        HideSelection = False
        MultiSelect = True
        OwnerData = True
        ReadOnly = True
        RowSelect = True
        PopupMenu = pmAll
        TabOrder = 0
        ViewStyle = vsReport
        OnClick = lvAllClick
        OnData = lvRecvData
      end
    end
    object tsAll: TTabSheet
      Caption = 'All'
      ImageIndex = 3
      object lvAll: TListView
        Left = 0
        Top = 0
        Width = 781
        Height = 192
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
        GridLines = True
        HideSelection = False
        MultiSelect = True
        OwnerData = True
        ReadOnly = True
        RowSelect = True
        PopupMenu = pmAll
        TabOrder = 0
        ViewStyle = vsReport
        OnClick = lvAllClick
        OnData = lvAllData
      end
    end
    object TabSheet3: TTabSheet
      Caption = 'Msg'
      ImageIndex = 2
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object memOutput: TMemo
        Left = 0
        Top = 0
        Width = 781
        Height = 192
        Align = alClient
        ReadOnly = True
        ScrollBars = ssBoth
        TabOrder = 0
      end
    end
    object TabSheet14: TTabSheet
      Caption = 'Func'
      ImageIndex = 4
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object labCnt: TLabel
        Left = 19
        Top = 176
        Width = 31
        Height = 13
        Caption = 'labCnt'
      end
      object btTimeBitToString: TButton
        Left = 146
        Top = 24
        Width = 35
        Height = 25
        Caption = '->'
        TabOrder = 0
        OnClick = btTimeBitToStringClick
      end
      object edtInputTimeBit: TEdit
        Left = 19
        Top = 26
        Width = 121
        Height = 21
        TabOrder = 1
        Text = 'TimeBitToString'
      end
      object edtTimeBitString: TEdit
        Left = 187
        Top = 26
        Width = 121
        Height = 21
        TabOrder = 2
        Text = 'TimeBitToString'
      end
      object edtUTF8BIN: TEdit
        Left = 19
        Top = 64
        Width = 121
        Height = 21
        TabOrder = 3
        Text = 'edtUTF8BIN'
      end
      object btUTF8ToAnsi: TButton
        Left = 146
        Top = 62
        Width = 35
        Height = 25
        Caption = '->'
        TabOrder = 4
        OnClick = btUTF8ToAnsiClick
      end
      object edtUTF8Output: TEdit
        Left = 187
        Top = 64
        Width = 121
        Height = 21
        TabOrder = 5
        Text = 'edtUTF8BIN'
      end
      object edtFloatToTime: TEdit
        Left = 19
        Top = 93
        Width = 121
        Height = 21
        TabOrder = 6
        Text = 'edtDWORDToTime'
      end
      object btFloatToTime: TButton
        Left = 146
        Top = 91
        Width = 35
        Height = 25
        Caption = '->'
        TabOrder = 7
        OnClick = btFloatToTimeClick
      end
      object edtFloatToTimeResult: TEdit
        Left = 187
        Top = 93
        Width = 121
        Height = 21
        TabOrder = 8
        Text = 'edtDWORDToTime'
      end
      object btShowMaps: TButton
        Left = 575
        Top = 120
        Width = 75
        Height = 25
        Caption = 'ShowMaps'
        TabOrder = 9
        OnClick = btShowMapsClick
      end
      object btDataViewer: TButton
        Left = 471
        Top = 120
        Width = 75
        Height = 25
        Caption = 'DataViewer'
        TabOrder = 10
        OnClick = btDataViewerClick
      end
      object edtServerMSTimeMuti: TEdit
        Left = 448
        Top = 26
        Width = 121
        Height = 21
        TabOrder = 12
        Text = '2.3'
      end
      object btStartAI: TButton
        Left = 575
        Top = 147
        Width = 75
        Height = 25
        Caption = 'GameWorld'
        TabOrder = 11
        OnClick = btStartAIClick
      end
      object btSetServerMSTimeMuti: TButton
        Left = 575
        Top = 24
        Width = 122
        Height = 25
        Caption = #35774#32622#26381#21153#22120#26102#38388#20493#29575
        TabOrder = 13
        OnClick = btSetServerMSTimeMutiClick
      end
      object btOrgToUTF8: TButton
        Left = 314
        Top = 62
        Width = 35
        Height = 25
        Caption = '<-'
        TabOrder = 14
        OnClick = btOrgToUTF8Click
      end
      object edtAnsiStr: TEdit
        Left = 19
        Top = 120
        Width = 121
        Height = 21
        TabOrder = 15
        Text = 'edtAnsiStr'
      end
      object btAnsiToUTF8Bin: TButton
        Left = 146
        Top = 118
        Width = 35
        Height = 25
        Caption = '->'
        TabOrder = 16
        OnClick = btAnsiToUTF8BinClick
      end
      object edtAnsiToUTF8Bin: TEdit
        Left = 187
        Top = 120
        Width = 121
        Height = 21
        TabOrder = 17
        Text = 'edtAnsiToUTF8Bin'
      end
      object btUpdateObject: TButton
        Left = 471
        Top = 147
        Width = 75
        Height = 25
        Caption = 'UpdateObject'
        TabOrder = 18
        OnClick = btUpdateObjectClick
      end
      object btMapDrawer: TButton
        Left = 390
        Top = 120
        Width = 75
        Height = 25
        Caption = 'MapDrawer'
        TabOrder = 19
        OnClick = btMapDrawerClick
      end
      object btReloadResource: TButton
        Left = 569
        Top = 62
        Width = 90
        Height = 25
        Caption = 'ReloadResource'
        TabOrder = 20
        OnClick = btReloadResourceClick
      end
      object btDisconnect: TButton
        Left = 674
        Top = 147
        Width = 75
        Height = 25
        Caption = 'btDisconnect'
        TabOrder = 21
        OnClick = btDisconnectClick
      end
      object edtFloatCalc: TEdit
        Left = 19
        Top = 149
        Width = 121
        Height = 21
        TabOrder = 22
        Text = 'edtFloatCalc'
        OnChange = edtFloatCalcChange
      end
      object edtFloatCalcResult: TEdit
        Left = 187
        Top = 149
        Width = 121
        Height = 21
        TabOrder = 23
        Text = 'edtFloatCalcResult'
      end
      object btSaveSpellData: TButton
        Left = 674
        Top = 91
        Width = 75
        Height = 25
        Caption = 'SaveSpellData'
        TabOrder = 24
        OnClick = btSaveSpellDataClick
      end
    end
    object TabSheet6: TTabSheet
      Caption = 'DataInfo'
      ImageIndex = 5
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object memPosInfo: TMemo
        Left = 0
        Top = 0
        Width = 781
        Height = 192
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
    end
    object TabSheet7: TTabSheet
      Caption = 'MemView'
      ImageIndex = 6
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object lvMemView: TListView
        Left = 0
        Top = 0
        Width = 781
        Height = 192
        Align = alClient
        Columns = <
          item
            Caption = 'HostProcessID'
            Width = 100
          end
          item
            Caption = 'DestProcessID'
            Width = 100
          end
          item
            Caption = 'HostPortNumber'
            Width = 100
          end
          item
            Caption = 'WatchPort'
            Width = 100
          end
          item
            Caption = 'BaseAddr'
            Width = 100
          end
          item
            Caption = 'BaseAddrOffset'
            Width = 100
          end
          item
            Caption = 'FrmName'
            Width = 100
          end
          item
            Caption = 'ForbiddenAnyMortConnection'
          end
          item
            Caption = 'ClientConnectIndex'
          end>
        GridLines = True
        HideSelection = False
        MultiSelect = True
        OwnerData = True
        ReadOnly = True
        RowSelect = True
        TabOrder = 0
        ViewStyle = vsReport
        OnData = lvMemViewData
      end
    end
    object TabSheet9: TTabSheet
      Caption = 'Cheat'
      ImageIndex = 8
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object btFlySet: TButton
        Left = 202
        Top = 70
        Width = 75
        Height = 25
        Caption = #39134#32724'/'#21462#28040#39134#32724
        TabOrder = 0
        OnClick = btFlySetClick
      end
      object btGameObjectFind: TButton
        Left = 297
        Top = 22
        Width = 75
        Height = 25
        Caption = #29289#20214#30417#27979
        TabOrder = 1
        OnClick = btGameObjectFindClick
      end
      object btCreatureFind: TButton
        Left = 202
        Top = 22
        Width = 75
        Height = 25
        Caption = #29983#29289#30417#27979
        TabOrder = 2
        OnClick = btCreatureFindClick
      end
      object btIncSpeed: TButton
        Left = 297
        Top = 70
        Width = 75
        Height = 25
        Caption = #21152#36895'/'#21462#28040#21152#36895
        TabOrder = 3
        OnClick = btIncSpeedClick
      end
      object btWaterwalking: TButton
        Left = 394
        Top = 22
        Width = 75
        Height = 25
        Caption = #27700#19978#34892#36208'/'#21462#28040
        TabOrder = 4
        OnClick = btWaterwalkingClick
      end
    end
    object TabSheet11: TTabSheet
      Caption = 'Threat'
      ImageIndex = 9
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object memThreat: TMemo
        Left = 0
        Top = 0
        Width = 781
        Height = 192
        Align = alClient
        Color = clInfoBk
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clGreen
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
        TabOrder = 0
      end
    end
    object TabSheet12: TTabSheet
      Caption = 'msTimeInfo'
      ImageIndex = 10
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object memMSTimeInfo: TMemo
        Left = 0
        Top = 0
        Width = 781
        Height = 192
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
    end
    object TabSheet13: TTabSheet
      Caption = 'DebugTest'
      ImageIndex = 11
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object labProxyCount: TLabel
        Left = 32
        Top = 25
        Width = 71
        Height = 13
        Caption = 'labProxyCount'
      end
      object btDirectModel: TButton
        Left = 301
        Top = 20
        Width = 87
        Height = 25
        Caption = #30452#25509#27169#24335','#21247#28857
        TabOrder = 0
        OnClick = btDirectModelClick
      end
      object Button1: TButton
        Left = 592
        Top = 80
        Width = 75
        Height = 25
        Caption = 'Button1'
        TabOrder = 1
        OnClick = Button1Click
      end
    end
    object TabSheet8: TTabSheet
      Caption = 'Thread'
      ImageIndex = 7
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object lvThread: TListView
        Left = 0
        Top = 0
        Width = 781
        Height = 192
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
        PopupMenu = pmAll
        TabOrder = 0
        ViewStyle = vsReport
        OnData = lvThreadData
      end
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 789
    Height = 41
    Align = alTop
    TabOrder = 1
    object cbShowHead: TCheckBox
      Left = 421
      Top = 7
      Width = 97
      Height = 17
      Caption = #19981#26174#31034#23553#21253#22836
      Checked = True
      State = cbChecked
      TabOrder = 0
      OnClick = cbShowHeadClick
    end
    object cbWatchType: TComboBox
      Left = 5
      Top = 5
      Width = 145
      Height = 21
      Style = csDropDownList
      ItemIndex = 1
      TabOrder = 1
      Text = 'World1'
      OnSelect = cbWatchTypeSelect
      Items.Strings = (
        'Realmd'
        'World1')
    end
    object cbHandlerPacket: TCheckBox
      Left = 515
      Top = 7
      Width = 97
      Height = 17
      Caption = 'HandlePacket'
      Checked = True
      State = cbChecked
      TabOrder = 2
      OnClick = cbHandlerPacketClick
    end
    object cbShowOrgPack: TCheckBox
      Left = 611
      Top = 7
      Width = 97
      Height = 17
      Caption = 'ShowOrgPack'
      TabOrder = 3
      OnClick = cbShowOrgPackClick
    end
    object cbNoRefresh: TCheckBox
      Left = 703
      Top = 7
      Width = 97
      Height = 17
      Caption = #20572#27490#21047#26032
      TabOrder = 4
    end
    object ToolBar1: TToolBar
      Left = 173
      Top = 3
      Width = 241
      Height = 30
      Align = alCustom
      AutoSize = True
      ButtonHeight = 27
      ButtonWidth = 54
      Caption = 'ToolBar1'
      DrawingStyle = dsGradient
      List = True
      ShowCaptions = True
      TabOrder = 5
      object tbClearAll: TToolButton
        Left = 0
        Top = 0
        Caption = 'ClearAll'
        ImageIndex = 0
        OnClick = tbClearAllClick
      end
      object tbBlock: TToolButton
        Left = 54
        Top = 0
        Caption = 'Block'
        ImageIndex = 1
        OnClick = tbBlockClick
      end
      object btDock: TToolButton
        Left = 108
        Top = 0
        Caption = 'btDock'
        ImageIndex = 3
        OnClick = btDockClick
      end
      object tbStartGame: TToolButton
        Left = 162
        Top = 0
        Caption = 'Start'
        DropdownMenu = pmStartMenu
        ImageIndex = 2
        Style = tbsDropDown
        OnClick = tbStartGameClick
      end
    end
  end
  object PageControl2: TPageControl
    Left = 0
    Top = 264
    Width = 789
    Height = 227
    ActivePage = TabSheet5
    Align = alBottom
    TabOrder = 2
    TabPosition = tpBottom
    object TabSheet4: TTabSheet
      Caption = #23553#21253#20998#26512
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object GroupBox2: TGroupBox
        Left = 0
        Top = 0
        Width = 368
        Height = 201
        Align = alLeft
        Caption = #25910#21457#21253#27979#35797'('#19981#21152#23553#21253#22836')'
        TabOrder = 0
        object labSendMsg: TLabel
          Left = 16
          Top = 174
          Width = 4
          Height = 13
          Caption = '-'
          Color = clBtnFace
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clMaroon
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentColor = False
          ParentFont = False
        end
        object Label1: TLabel
          Left = 272
          Top = 20
          Width = 39
          Height = 13
          Caption = 'Version:'
        end
        object cbPackHead: TComboBox
          Left = 16
          Top = 17
          Width = 233
          Height = 21
          TabOrder = 0
        end
        object btSendToClient: TButton
          Left = 16
          Top = 143
          Width = 81
          Height = 25
          Caption = '<-'#36865#32473#23458#25143#31471
          TabOrder = 1
          OnClick = btSendToClientClick
        end
        object btSendToServer: TButton
          Left = 272
          Top = 142
          Width = 81
          Height = 25
          Caption = #36865#32473#26381#21153#31471'->'
          TabOrder = 2
          OnClick = btSendToServerClick
        end
        object btParseRecv: TButton
          Left = 103
          Top = 142
          Width = 81
          Height = 25
          Caption = #35299#35835'(RCV)'
          TabOrder = 3
          OnClick = btParseRecvClick
        end
        object btParseSend: TButton
          Left = 190
          Top = 142
          Width = 81
          Height = 25
          Caption = #35299#35835'(SND)'
          TabOrder = 4
          OnClick = btParseSendClick
        end
        object edtSendPack: TMemo
          Left = 16
          Top = 44
          Width = 337
          Height = 89
          ScrollBars = ssBoth
          TabOrder = 5
          OnDblClick = edtSendPackDblClick
        end
        object edtVersion: TCSpinEdit
          Left = 323
          Top = 17
          Width = 30
          Height = 22
          TabOrder = 6
          Value = 2
        end
        object edtTick: TEdit
          Left = 146
          Top = 173
          Width = 207
          Height = 21
          TabOrder = 7
          Text = 'edtTick'
        end
      end
      object memComment: TMemo
        Left = 368
        Top = 0
        Width = 413
        Height = 201
        Align = alClient
        Color = clInfoBk
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clGreen
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
        PopupMenu = pmMemo
        ScrollBars = ssBoth
        TabOrder = 1
      end
    end
    object TabSheet5: TTabSheet
      Caption = #23553#21253#22836#36807#28388
      ImageIndex = 1
      object Panel2: TPanel
        Left = 0
        Top = 137
        Width = 781
        Height = 64
        Align = alBottom
        TabOrder = 0
        object Label2: TLabel
          Left = 229
          Top = 40
          Width = 36
          Height = 13
          Caption = #30340#23553#21253
        end
        object cbFilter: TCheckBox
          Left = 0
          Top = 16
          Width = 97
          Height = 17
          Caption = #36807#28388
          TabOrder = 0
          OnClick = cbFilterClick
        end
        object cbReverseFilter: TCheckBox
          Left = 92
          Top = 16
          Width = 97
          Height = 17
          Caption = #36870#21521#36807#28388
          TabOrder = 1
          OnClick = cbFilterClick
        end
        object cbAddFilter: TComboBox
          Left = 281
          Top = 14
          Width = 233
          Height = 21
          TabOrder = 2
        end
        object btAddFilter: TButton
          Left = 584
          Top = 36
          Width = 75
          Height = 25
          Caption = #28155#21152'Filter'
          TabOrder = 3
          OnClick = btAddFilterClick
        end
        object btClearFilter: TButton
          Left = 700
          Top = 36
          Width = 75
          Height = 25
          Caption = #28165#31354'Filter'
          TabOrder = 4
          OnClick = btClearFilterClick
        end
        object edtFilterGuid: TEdit
          Left = 560
          Top = 14
          Width = 217
          Height = 21
          TabOrder = 5
        end
        object cbFilterAllCreature: TCheckBox
          Left = 0
          Top = 39
          Width = 121
          Height = 17
          Caption = #36807#28388#25152#26377'Creature'
          TabOrder = 6
          OnClick = cbFilterClick
        end
        object cbFilterPacketSize: TCheckBox
          Left = 112
          Top = 39
          Width = 65
          Height = 17
          Caption = #36807#28388#23567#20110
          TabOrder = 7
          OnClick = cbFilterPacketSizeClick
        end
        object edtFilterPacketSize: TCSpinEdit
          Left = 183
          Top = 39
          Width = 40
          Height = 22
          TabOrder = 8
          Value = 2
        end
      end
      object lvPackFilter: TListView
        Left = 0
        Top = 0
        Width = 781
        Height = 137
        Align = alClient
        Columns = <
          item
            Caption = 'OPCODE'
            Width = 200
          end
          item
            Caption = 'Guid'
            Width = 100
          end>
        GridLines = True
        HideSelection = False
        MultiSelect = True
        OwnerData = True
        ReadOnly = True
        RowSelect = True
        PopupMenu = pmFilter
        TabOrder = 1
        ViewStyle = vsReport
        OnData = lvPackFilterData
      end
    end
  end
  object Timer1: TTimer
    OnTimer = Timer1Timer
    Left = 696
    Top = 24
  end
  object pmAll: TPopupMenu
    Left = 360
    Top = 128
    object miAllCopy: TMenuItem
      Caption = 'Copy'
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
      object miCopyToFile: TMenuItem
        Caption = 'CopyToFile'
        OnClick = miCopyToFileClick
      end
    end
    object miAllAddToFilter: TMenuItem
      Caption = 'AddToFilter'
      OnClick = miAllAddToFilterClick
    end
  end
  object TimeLogic: TTimer
    Interval = 100
    OnTimer = TimeLogicTimer
    Left = 464
    Top = 104
  end
  object pmMemo: TPopupMenu
    Left = 688
    Top = 112
    object miCommentCopyAll: TMenuItem
      Caption = #22797#21046#25152#26377
      OnClick = miCommentCopyAllClick
    end
    object miCommentWatch: TMenuItem
      Caption = #26032#31383#21475#20013#26597#30475
      OnClick = miCommentWatchClick
    end
  end
  object pmFilter: TPopupMenu
    Left = 504
    Top = 144
    object miDeleteFilter: TMenuItem
      Caption = #21024#38500#36825#20010
      OnClick = miDeleteFilterClick
    end
  end
  object TimeInfo: TTimer
    Interval = 2000
    OnTimer = TimeInfoTimer
    Left = 216
    Top = 200
  end
  object tmCloseFreeRefresh: TTimer
    OnTimer = tmCloseFreeRefreshTimer
    Left = 128
    Top = 136
  end
  object pmStartMenu: TPopupMenu
    Left = 280
    Top = 144
  end
  object ImageList1: TImageList
    Height = 32
    Width = 32
    Left = 168
    Top = 200
    Bitmap = {
      494C010119001B002C0120002000FFFFFFFFFF10FFFFFFFFFFFFFFFF424D3600
      000000000000360000002800000080000000E0000000010020000000000000C0
      010000000000000000000000000000000000000000000000000000000000BDBD
      BD00CECECE00525252008C8C8C008484840073737300737373006B6B6B006B6B
      6B00292929007B0000007B000000000000000000000000000000000000007B00
      00007B0000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000CECE
      CE008C8C8C009C9C9C00A5A5A5009C9C9C008C8C8C008C8C8C00737373006B6B
      6B006B6B6B007B0000007B0000007B0000007B0000007B0000007B0000007B00
      00007B0000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000BDBD
      BD00CECECE00B5B5B500B5B5B500A5A5A500A5A5A5009C9C9C008C8C8C007373
      73006B6B6B007B0000007B0000007B0000007B0000007B0000007B0000007B00
      00007B0000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000BDDE
      BD00FFFFFF00BDBDBD00BDBDBD00BDBDBD00B5B5B500A5A5A5008C8C8C008484
      84006B6B6B00424242007B000000BDBDBD009C9C9C007B0000007B0000007B00
      00007B0000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000BDDE
      BD00FFFFFF00D6D6D600D6D6D600CECECE00BDBDBD00B5B5B500A5A5A5008C8C
      8C0073737300424242007B000000BDDEBD00CECECE005A5A5A007B0000007B00
      000000000000000000000000000000000000000000007B000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000D6D6
      D600FFFFFF00D6D6FF00D6DEFF00FFFFFF00EFF7FF00BDBDBD00A5A5A5009C9C
      9C00848484007B0000007B000000BDBDBD00CECECE00EFEFEF00B5B5B500B5B5
      B500BDBDBD0000000000000000007B0000007B0000007B000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000D6D6
      D600CECECE00BDBDBD00D6DEFF00FFFFFF00FFFFFF00ADC6FF00BDBDBD00A5A5
      A5008C8C8C007B000000BDBDBD00BDBDBD00FFFFFF00B5B5B500D6D6D600FFFF
      FF00FFFFFF00D6D6D600A5A5A5007B0000007B0000007B000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000D6D6D600BDBDBD00D6DEFF00D6DEFF00D6DEFF00CECECE00BDBDBD00A5A5
      A5007B0000007B000000BDDEBD00B5B5B500A5A5A500A5A5A500FFFFFF00CECE
      CE00A5A5A500EFEFEF00D6D6D6008C8C8C007B0000007B000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000CECECE00D6D6D600D6DEFF00CECECE00B5B5B5007B00
      00007B0000007B0000007B0000007B000000A5A5A500FFFFFF00FFFFFF00B5B5
      B500FFFFFF00EFEFEF00CECECE00D6D6D6007B0000007B000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000B5B5B500B5B5B500B5B5B500A5A5
      A5006B0021007B0000007B0000007B0000007B000000FFFFFF00D6D6D600A59C
      9C00FFFFFF00FFFFFF00FFFFFF00848484007B00000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000BDBDBD00BDBDBD00BDBDBD00BDBDBD00ADC6FF00BDBDBD00BDBD
      BD00B5B5B500B5B5B5009C9C9C007B0000007B000000BDBDBD008C8C8C007373
      7300FFFFFF00EFEFEF00EFEFEF00EFEFEF00E7E7E70000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000BDBDBD00BDBDBD00ADC6FF00D6DEFF00D6DEFF00D6DEFF00D6DEFF00CECE
      CE00CECECE00CECECE00BDBDBD00A5A5A5007B000000FFFFFF00D6D6D600FFFF
      FF00D6D6D600EFEFEF00FFFFFF008C8C8C000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000CECE
      CE00B5B5B500B5B5B500D6DEFF00D6DEFF00D6DEFF00D6DEFF00D6DEFF00D6DE
      FF00D6DEFF00BDBDBD00CECECE00BDBDBD009C9C9C00FFFFFF00FFFFFF00A5A5
      A500FFFFFF00FFFFFF00FFFFFF00BDBDBD000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000008C8C8C000808
      080039393900B5B5B500D6DEFF00D6DEFF00D6DEFF00D6DEFF00D6DEFF00D6DE
      FF00D6DEFF00D6D6FF00BDBDBD00A5A5A500B5B5B5007B000000FFFFFF00BDBD
      BD007B000000B5B5B500A5A5A500000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000E7E7E700BDBDBD00FFFFFF00FFFFFF00FFFFFF00FFFFFF00B5B5
      B500D6DEFF00D6DEFF00BDBDBD00CECECE00B5B5B5007B0000007B0000007B00
      00007B000000EFEFEF00FFFFFF00A5A5A5000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000029292900FFFFFF00FFFFFF000000
      0000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00D6D6
      D600A59C9C00ADC6FF00ADDEFF00ADC6FF008C8C8C007B0000007B0000007B00
      00007B0000007B000000FFFFFF00FFFFFF00CECECE005A5A5A007B0000007B00
      00007B0000007B00000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FFFFFF00FFFFFF00D6D6
      D60000000000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF000000
      0000BDBDBD007B0000007B0000007B0000007B0000007B0000007B0000007B00
      00007B0000007B0000007B000000FFFFFF00FFFFFF00D6D6D600A5A5A5007B00
      00007B0000007B00000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000073737300FFFFFF004242
      420000000000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF000000
      0000B5B5B500A5A5A5007B0000007B0000007B0000007B0000007B0000007B00
      00007B0000007B0000007B0000007B000000FFFFFF00FFFFFF00EFEFEF007B00
      00007B0000007B00000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000007B000000FFFFFF004242
      42007B0000007B000000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF000000
      000073737300B5B5B5007B0000007B0000007B0000007B0000007B0000007B00
      00007B0000007B0000007B0000007B0000007B000000EFEFEF00D6D6D6007B00
      00007B0000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000007B000000FFFFFF00FFFF
      FF007B0000007B000000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00A59C
      9C00B5B5B500BDBDBD007B0000007B0000007B0000007B0000007B0000007B00
      00007B0000007B0000007B0000007B0000007B0000007B0000007B0000007B00
      0000940029000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000007B000000FFFFFF00FFFF
      FF007B0000007B00000084848400FFFFFF00FFFFFF00FFFFFF00FFFFFF008C8C
      8C00FFFFFF00CECECE007B0000007B0000007B0000007B0000007B0000007B00
      00007B0000007B0000007B0000007B0000007B0000007B0000007B0000007B00
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000007B000000FFFFFF00FFFF
      FF007B0000007B0000007B000000D6D6D600FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00CECECE005A5A5A007B0000007B0000007B0000007B0000007B00
      00007B0000007B0000007B0000007B0000007B0000007B000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000007B000000D6D6D6004242
      42007B0000007B0000007B0000007B000000FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00CECECE007B0000007B0000007B0000007B0000007B0000007B00
      00007B0000007B0000007B0000007B0000009400290000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000094002900424242007B00
      00007B0000007B0000007B0000007B0000005A5A5A00D6D6D600FFFFFF00FFFF
      FF00FFFFFF00B5B5B5007B0000007B0000007B0000007B0000007B0000007B00
      00007B0000007B00000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000007B0000007B00
      00007B0000007B0000007B0000007B0000007B0000007B000000A5A5A500BDBD
      BD00B5B5B5005A5A5A007B0000007B0000007B0000007B0000007B0000007B00
      00007B0000007B0000007B000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000007B0000007B0000007B00
      00007B0000007B0000007B0000007B0000007B0000007B0000007B0000007B00
      00007B0000007B0000007B0000007B0000007B000000D6DEFF007B0000007B00
      00007B0000007B0000007B0000007B0000007B00000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000007B0000007B0000007B00
      00007B0000007B0000007B0000007B0000007B0000007B0000007B0000007B00
      00007B0000007B0000007B0000006B002100D6DEFF00ADDEFF007B0000007B00
      00007B0000007B0000007B0000007B0000007B0000007B0000007B0000007B00
      00007B0000007B00000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000007B0000007B0000007B00
      00007B0000007B0000007B0000007B0000007B0000007B0000007B0000007B00
      00007B0000007B0000007B000000BDBDBD00CECECE00ADDEFF007B0000007B00
      00007B0000007B0000007B0000007B0000007B0000007B0000007B0000007B00
      00007B0000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000007B0000007B0000007B00
      00007B0000007B0000007B0000007B0000007B0000007B0000007B0000007B00
      00007B0000007B0000007B0000007B0000009C9C9C00BDBDBD007B0000007B00
      00007B0000007B0000007B0000007B0000007B0000007B0000007B0000007B00
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000007B0000007B0000007B00
      00007B0000000000000000000000000000007B0000007B0000007B0000007B00
      00007B0000007B0000007B0000007B0000007B0000007B0000007B0000007B00
      00007B0000007B0000007B0000007B0000007B0000007B0000007B0000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000006B0021007B00
      00007B0000007B0000007B0000007B0000007B0000007B0000007B0000007B00
      00007B0000007B0000007B0000007B0000007B00000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000006B6B6B007B0000007B0000007B0000007B0000007B0000007B00
      00007B0000007B00000052525200000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000FFFFFF00F7FFFF00F7FFFF00F7FF
      FF00F7FFFF00FFFFFF00000000000000000000000000FFFFFF00F7FFFF00F7FF
      FF00F7FFFF00F7FFFF00F7FFFF00F7FFFF00FFFFFF0000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000FFFFFF00EFEFEF00EFEFEF00EFEFEF00EFEFEF00EFEF
      EF00EFEFEF00EFEFEF00EFEFEF00EFEFEF00F7F7F70000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000FFFFFF00F7FFFF00F7FFFF00FFFFFF000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000FFFFFF00EFF7F700DEE7E700D6E7DE00D6DEDE00D6DE
      DE00D6DEDE00DEE7E700EFF7F700F7FFFF00F7F7F700E7EFEF00D6E7DE00D6DE
      DE00D6DEDE00D6DEDE00D6DEDE00DEE7E700E7EFEF00F7F7F700000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000F7F7FF00C6C6
      EF008484DE006363D6004242CE004242CE004242CE004242CE006363D6007B7B
      DE00C6C6EF00F7F7FF0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000F7F7F700C6CEC600949C9C00848C8C00848C8400848C8400848C
      8400848C8400848C8400848C84008C949400BDBDBD00EFEFEF00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000FFFFFF00F7FFF700F7F7F700F7FFF700FFFF
      FF0000000000000000000000000000000000000000000000000000000000F7FF
      F700E7EFEF00D6E7DE00D6E7DE00E7EFEF00F7F7F70000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000FFFFFF00E7EFEF00C6D6D600A5BDBD008CADAD0084ADA50084AD
      A5008CADAD00A5BDBD00D6DEDE00E7EFEF00D6E7E700ADC6C60094B5AD0084AD
      A50084ADA50084ADA50084ADA50094B5B500B5CEC600DEE7E700F7FFFF000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000F7F7FF009C9CE7004242CE007373
      D600A5A5DE00C6C6DE00DEDEE700E7E7E700E7E7E700E7E7E700C6C6DE00ADAD
      DE007373D6004242CE009494E700F7F7FF000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000DEDEDE00297BBD000094FF000094FF000094FF000094FF000094
      FF000094FF000094FF00009CFF00009CFF001084D600C6CECE0000000000FFFF
      FF00F7F7F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7F700FFFFFF000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000FFFFFF00EFF7F700DEE7E700CEDEDE00CEDED600CEDEDE00DEE7
      E700EFF7F700FFFFFF0000000000000000000000000000000000FFFFFF00E7EF
      EF00BDCECE0094ADAD008CADAD00ADC6C600DEE7E700F7F7F700000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000F7F7F700CED6D600949C84009C6B3100AD5A1800AD5A1800AD5A
      1800C6844A00C6733100B5BDAD00DEE7E700BDD6CE00AD733900B55A1800AD5A
      1800AD5A1800AD5A1800AD5A1800B55A1800A57B5200C6D6D600EFF7F7000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000B5B5EF004A4ACE008C8CD600D6D6DE00DEDE
      DE00E7E7E700E7E7E700E7E7E700EFEFEF00EFEFEF00EFEFEF00E7E7E700E7E7
      E700E7E7E700E7E7E7009494DE004A4ACE00ADADEF0000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000D6D6D60000A5FF0000B5FF0000B5FF0000B5FF0000B5FF0000B5
      FF0000B5FF0008BDFF0010C6FF0018CEFF0018C6FF007BA5C600E7E7E700BDC6
      C600ADB5B500ADB5B500ADB5B500ADB5B500ADB5B500ADADB500B5BDBD00E7E7
      E700000000000000000000000000000000000000000000000000000000000000
      0000F7FFF700E7EFEF00C6D6CE009CB5B50084A59C007B9C940084A59C009CBD
      B500C6D6CE00E7EFEF00F7FFFF00000000000000000000000000F7FFFF00D6DE
      DE00849C94006B7B73005A736B00738C8400BDCECE00EFEFEF00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000F7FFFF00E7EFEF00ADBDB500CE631000FFAD3900FFAD3100FFA52900FFA5
      2900FFA52900FF941800B5947300D6E7E700B5AD9400EF842100FFB54A00FFA5
      2900FFA52900FFA52900FFA52900FFAD3100E7842900ADAD9C00E7EFEF000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000FFFFFF008C8CDE007B7BD600BDBDDE00DEDEDE00E7E7E700EFEF
      EF00EFEFF700E7E7F700DEDEF700D6D6F700D6D6F700D6D6F700E7E7F700F7F7
      F700EFEFEF00E7E7E700EFEFEF00CECEE7008484DE007B7BDE00FFFFFF000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000D6D6D60000A5FF0000B5FF0000ADFF0052C6FF0063CEFF0073D6
      FF008CDEFF009CE7FF00ADEFFF0021D6FF0021CEFF00739CBD00A5AD9C005284
      10004A8408004A8400004A8400004A8400004A8400004A8400005284080094A5
      8400F7F7F700000000000000000000000000000000000000000000000000F7FF
      FF00DEE7E700ADC6C600739C94005A7B73005A736B0063736B005A736B005A7B
      73007BA59C00B5CEC600E7EFEF00F7FFFF000000000000000000F7F7F700C6D6
      D6006B847B00DEEFDE00CEDECE00A5ADA5009CADA500E7EFEF00000000000000
      0000000000000000000000000000000000000000000000000000FFFFFF00EFF7
      F700DEE7E700BDD6CE0094947B00F77B0000FF8C0000FF8C0000FF8C0000FF8C
      0000FF8C0000EF6B0000ADAD9C00D6DEDE00B5C6BD00E76B0000FF8C0000FF8C
      0000FF8C0000FF8C0000FF8C0000FF8C0000FF840000A59C8400E7EFEF000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000007B7BDE008484D600DEDEDE00E7E7E700EFEFEF00EFEFF700D6D6
      F700B5B5F7007B7BE7006363E7005252DE005A5ADE005A5ADE007B7BE7009C9C
      EF00C6C6F700F7F7F700EFEFEF00EFEFEF00EFEFEF008C8CDE007373DE000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000D6D6D60000A5FF0000B5FF00009CFF0084ADC600A5CEE700A5CE
      E700A5C6E7008CB5CE001094E70039EFFF0031D6FF006B94B5006B84420042CE
      180042D618008CE76300A5E77300B5E78400C6EFA50063BD000063BD00006B8C
      3900EFEFEF000000000000000000000000000000000000000000FFFFFF00E7EF
      EF00B5C6C6006B948C0063736B00BDBDB500EFE7E700E7E7E700D6D6D600949C
      940063736B00739C9400B5CEC600E7EFEF00F7FFFF0000000000F7F7F700BDCE
      CE00848C8400E7F7E700DEEFE700ADB5AD0094ADA500E7EFEF00000000000000
      00000000000000000000000000000000000000000000FFFFFF00E7EFEF00C6D6
      D600A5BDBD0084A5A5008C6B3900F7840000FF8C0000FF8C0000FF8C0000FF8C
      0000FF8C0000AD52080084ADAD00ADC6BD0094B5AD00945A2900FF8C0000FF8C
      0000FF8C0000FF8C0000FF8C0000FF8C0000FF840000A59C8C00E7EFEF000000
      0000000000000000000000000000000000000000000000000000000000000000
      00009C9CE7008484D600DEDEDE00E7E7E700EFEFEF00DEDEF700BDBDF7005252
      DE000808CE000000CE000000CE000000CE000000CE000000CE000000CE001818
      D6004A4ADE008484E700DEDEF700F7F7F700EFEFEF00EFEFEF008C8CDE009494
      E700000000000000000000000000000000000000000000000000000000000000
      000000000000D6D6D60000A5FF0000B5FF0000A5FF00D6D6D600000000000000
      000000000000E7E7E7001894DE004AF7FF0042DEFF006B94B5006B84390039D6
      210042CE18005294100063A521006BA521006394180063AD000063BD00006B8C
      3900EFEFEF000000000000000000000000000000000000000000EFF7F700C6D6
      D6007B9C9C006B736B00EFEFE700EFF7EF00CEDED600D6DED600EFF7EF000000
      0000ADADA50063736B00739C9400B5C6C600DEE7E700F7F7F700EFF7EF00B5C6
      C600949C9400E7F7E700DEF7E700ADB5AD0094ADA500E7EFEF00000000000000
      00000000000000000000000000000000000000000000EFF7F700BDD6CE008C9C
      8C009C6B3900A55A21007B5A2900EF7B0000FF940000FF8C0000FF8C0000FF8C
      0000FF940000C65A0800637B6B005A8C8C005A7B7300B55A0800FF940000FF8C
      0000FF8C0000FF8C0000FF8C0000FF940000E76B0000A59C8400E7EFEF000000
      000000000000000000000000000000000000000000000000000000000000C6C6
      EF006B6BD600D6D6DE00E7E7E700EFEFF700D6D6F7006B6BE7000808CE000000
      CE000000CE000000CE000000CE000000CE000000CE000000CE000000CE000808
      D6000808D6002929D6006B6BE700C6C6F700F7F7F700EFEFEF00EFEFEF008484
      DE00BDBDEF000000000000000000000000000000000000000000000000000000
      000000000000D6D6D60000A5FF0000BDFF0000ADFF00D6D6D600000000000000
      000000000000E7E7E700219CE70063FFFF0052E7FF007394B5006B8439009CF7
      9C00DEFFD60094A58400F7F7F70000000000CECED60063AD000063C600006B8C
      4200EFEFEF0000000000000000000000000000000000FFFFFF00DEE7E7009CBD
      B5006B7B7300CECECE00DEE7E700C6D6C600CED6CE00D6DED600CEDECE00DEE7
      DE0000000000A5A59C0063736B006B948C00ADBDBD00D6DEDE00D6DEDE009CB5
      B500ADB5AD00E7F7EF00DEEFDE00ADBDAD008CA59C00DEE7E700FFFFFF000000
      000000000000000000000000000000000000FFFFFF00DEE7E7009CA59C00CE5A
      0000FF9C1000FF9C0800E76B0000E7730000FF940000FF940000FF940000FF94
      0000FF940800FF9C2100DE6B0000D65A0000D66B0000FFB55A00FF940800FF94
      0000FF940000FF940000FF940000FF940000E7730000A59C8C00E7EFEF000000
      0000000000000000000000000000000000000000000000000000FFFFFF005A5A
      D600B5B5DE00DEDEDE00EFEFEF00D6D6F7006B6BE7000000CE000000CE000000
      CE000000CE000000CE00000000000000000000000000000000000000CE000808
      D6000808D6000808D6002121D6005A5ADE00CECEF700F7F7F700EFEFEF00CECE
      E7005252D600F7F7FF0000000000000000000000000000000000000000000000
      000000000000D6D6D60000A5FF0008C6FF0008ADFF00CECECE00FFFFFF00F7F7
      F700FFFFFF00EFEFEF0029A5F700B5FFFF00E7FFFF008CB5D6008C9C63006BC6
      180063AD1800B5C6A5000000000000000000D6D6D6005AAD08005AC608006B8C
      4200EFEFEF0000000000000000000000000000000000F7F7F700C6D6D6007394
      8C009C9C9C00F7F7F700BDCEC600BDCEC600CEDECE00D6DED600CED6CE00C6CE
      C600EFEFEF00FFFFFF00949C94006B736B005A8C84008CADA5009CBDB5007B94
      8C00B5BDB500B5C6B500B5C6BD00A5B5AD00849C9400CEDEDE00EFF7F700FFFF
      FF0000000000000000000000000000000000F7FFFF00CEDEDE00AD6B3100FF8C
      0000FF940000FF940000FF940000FF940000FF940000FF940000FF940000FF94
      0000FF940000F79C2100EFB55A00E7AD5200E7BD7B00EF9C1800F78C0000FF94
      0000FF940000FF940000FF940000FF940000E7730000A59C8400DEE7E700F7F7
      F700FFFFFF000000000000000000000000000000000000000000B5B5EF008484
      D600DEDEDE00E7E7E700E7E7F7007373E7000000CE000000CE000000CE000000
      CE000000CE000000CE00000000000000000000000000000000000808D6001010
      D6001010D6001010D6001010D6002929D6005A5ADE00EFEFF700F7F7F700F7F7
      F7009494DE00A5A5E70000000000000000000000000000000000000000000000
      000000000000D6D6D60008ADFF0010CEFF0008B5FF008C8C8C00ADB5AD00ADAD
      AD00BDBDBD00E7E7E700BDD6EF000073E7000073E700EFEFF700F7F7F700E7E7
      E700E7E7E700F7F7F700F7F7F700E7E7E700B5B5BD0052B508004ACE10006B8C
      4200EFEFEF0000000000000000000000000000000000E7EFEF00ADC6BD006B7B
      7300EFE7E700C6CEC600B5C6BD00BDC6BD00BDCEBD00CED6CE00C6CECE00B5BD
      B500ADB5AD0000000000D6DED6009CA59C00737B7300527B6B0052847B00527B
      7300B5BDB500B5C6BD00B5CEBD00B5C6BD0063847B009CBDB500C6D6D600DEE7
      E700F7F7F700000000000000000000000000F7FFF700CEDEDE00B5631800FF9C
      0000FF940000FF940000FF940000FF940000FF940000FF940000FF940000F794
      0000E78C0000CE840800AD7B10009C7B2100A57B2100BD7B0800D68C0800EF8C
      0000F7940000FF940000FF940000FF940000E77300008C8C7B00B5CECE00CEDE
      DE00E7EFEF00F7F7F700000000000000000000000000000000006363D600C6C6
      DE00E7E7E700EFEFF700C6C6F7002121D6000000CE000000CE000000CE000000
      CE000808D6000000CE00000000000000000000000000000000000808D6001010
      D6001010D6001818D6001818D6001818D6003131DE009494EF00F7F7F700F7F7
      F700DEDEEF005252D60000000000000000000000000000000000000000000000
      000000000000D6D6D60008ADFF0021D6FF0018C6FF001084CE00108CD600188C
      D6001894E70094B5CE0000000000000000000000000000000000000000000000
      000000000000FFFFFF00C6CEBD006B845A004A5A39004AB5080039CE18006B8C
      3900EFEFEF00000000000000000000000000FFFFFF00DEE7E7008CADA5008C8C
      8400F7F7F700B5BDB500B5C6B500B5C6B500B5C6B500ADBDAD00ADB5AD009CAD
      A5008C9C8C00EFEFE700DEDEDE00B5C6B500ADB5AD008C9484006B736B00526B
      6300A5B5AD00B5C6BD00B5CEBD00C6D6C6005A736B0052847B007B9C9400A5BD
      B500CEDEDE00EFF7F7000000000000000000FFFFFF00D6E7E700BD6B2900FFA5
      1000FF9C0000FF940000FF940000FF940000FF940000FF940000FF940000E78C
      0000B58410009C844A007B734A00D6CED600BDBDBD007B6B3900A58C4A00C684
      0800E7940000FF940000FF9C0000FF9C0000E773000063735A006B9C940084AD
      A500ADC6C600DEE7E700F7F7F7000000000000000000E7E7F7005252CE00E7E7
      E700E7E7E700DEDEF7006B6BE7000000CE000000CE000000CE000000CE000808
      D6000808D6000808D6007373E7006363E7006363E7007373E7001010D6001818
      DE001818DE001818DE001818DE001818DE002121DE004242DE00EFEFF700F7F7
      F700F7F7F7006363D600D6D6F700000000000000000000000000000000000000
      000000000000D6DEDE0010B5FF0029DEFF0039EFFF004AF7FF005AFFFF0073FF
      FF0063EFFF000073E70000000000000000000000000000000000000000000000
      000000000000F7F7F7009CAD8400EFFFDE00C6FFB5008CEF73005ADE42007394
      4200EFEFEF00000000000000000000000000F7F7F700CEDEDE00738C8400BDBD
      B500D6D6D600ADBDAD00ADBDAD00ADBDAD00ADBDAD00A5B5AD0094A594007B8C
      84006B7B6B00BDC6BD00F7EFEF009CAD9C00ADB5AD00B5C6B500ADBDAD00B5C6
      B500BDCEBD00BDD6C600C6D6C600C6D6CE00949C9400737B730063736B006384
      7B0094B5AD00D6DEDE00F7F7F7000000000000000000E7EFEF00BD733900FFAD
      4A00FFC66B00FFB53900FFB53900FFCE8400FF9C0800FF9C0000F7940000C68C
      0800948C7B00EFE7EF00A59C9C00F7EFF700D6CECE00C6BDBD00EFE7EF009484
      5A00CE8C0800F7940000FF9C0000FF9C0000E7730000A55A1800EF730000E773
      0000947B5A00B5C6C600E7EFEF000000000000000000A5A5E7008C8CD600E7E7
      E700EFEFEF00C6C6F7002929D6000000CE000000CE000000CE000808D6000808
      D6000808D6001010D6002929DE002929DE002929DE002121D6001818DE002121
      DE002121DE002121DE002121DE002121DE002121DE002929DE00B5B5EF00F7F7
      F700F7F7F700A5A5E7009C9CE700000000000000000000000000000000000000
      000000000000EFF7F70010A5FF008CEFFF00A5F7FF00BDFFFF00D6FFFF00E7FF
      FF00F7FFFF000073E70000000000000000000000000000000000000000000000
      000000000000FFFFFF00C6CEBD007B9C63006B8C4A006B84520073946300A5BD
      9400FFFFFF00000000000000000000000000F7F7F700C6D6D6006B7B7300E7E7
      E700ADB5AD00A5B5AD00ADB5AD00ADB5AD00ADB5AD00A5ADA5008C9C8C008494
      8C00738473008C9C9400FFFFFF00A5ADA5009CA59C00A5AD9C00ADB5AD00ADBD
      B500C6D6C600C6D6CE00C6D6CE00C6D6CE00CED6CE00B5C6B500A5ADA500848C
      84006B847B00B5C6C600E7EFEF000000000000000000F7FFFF00DEDEDE00D65A
      0000F7A53900F7BD6B00DE945200F7940800FF9C0000FF9C0000E7940000A57B
      100084847300EFE7EF00EFE7E700C6BDBD00C6BDBD00F7EFF700DED6D6007373
      5200B5841000EF940000FF9C0000FF9C0000FF9C0000FFA50000FFA50000FFA5
      0000F78400009C8C7300D6E7DE00F7FFFF00000000008484DE00ADADDE00E7E7
      E700F7F7F700B5B5F7000000CE000000CE000000CE000808D6000808D6001010
      D6001010D6001010D6007B7BE70000000000000000007B7BE7001818DE002121
      DE002929DE002929DE002929DE002929DE002929DE002929DE008484E700F7F7
      F700F7F7F700C6C6EF007373DE00000000000000000000000000000000000000
      0000F7F7F700E7E7E700B5C6D60073ADD6005AA5DE005AA5DE005AA5DE005A9C
      DE005AA5E700CEDEEF0000000000000000000000000000000000000000000000
      00000000000000000000EFEFEF00CED6D600C6CECE00CED6D600DEE7E700F7F7
      F70000000000000000000000000000000000F7F7F700BDCECE006B7B7300F7F7
      EF00ADB5AD00ADB5AD00ADBDAD008CAD94007BA58400BDCEC600BDC6BD00ADBD
      B5009CAD9C00ADB5AD00FFFFFF00ADB5AD009CA59C009CA59C009CAD9C009CAD
      9C00A5B5A500B5C6B500B5C6B500BDC6BD00BDCEC600BDCEBD00B5BDB500B5BD
      B5007B847B008CADA500DEE7E700FFFFFF000000000000000000F7FFF700E7E7
      DE00CE9C7B00B58C5A009C633100F78C0000FFA50000FF9C0000D69408009484
      6300B5ADAD00CEC6C600B5A58C00F78C0000EF8C0000BDB5B500BDB5B500B5B5
      AD008C7B3900DE940000FF9C0000FF9C0000FF9C0000FF9C0000FFA50000FFA5
      0000FFA50000B5632100CEDEDE00F7FFF700000000006B6BD600BDBDDE00E7E7
      E700EFEFF7009494EF000000CE000000CE000808D6000808D6001010D6001010
      D6001010D6001010D6008C8CEF0000000000000000008C8CEF001818DE002929
      E7002929E7003131E7003131E7003131E7003131E7002929DE006363E700FFFF
      FF00F7F7F700D6D6EF006363D60000000000000000000000000000000000F7F7
      F700BDC6C600525A8C00424A7B004A527B004A527B004A527B004A527B00424A
      7B005A638C00C6C6CE00FFFFFF00000000000000000000000000000000000000
      00000000000000000000D6DEDE0094A5A500849494009CA5A500DEDEDE000000
      000000000000000000000000000000000000F7F7F700BDCECE00737B7300F7FF
      FF00B5C6B500B5C6B500BDC6BD0029733900005A1000B5BDB500A5B5AD009CAD
      9C0084948C007B8C7B00FFF7F700ADB5AD009CADA500A5ADA500A5ADA500A5AD
      A500A5ADA500ADB5AD00ADB5AD00ADB5AD00ADB5AD00ADB5AD00A5ADA500ADB5
      AD00949C94007B948C00CEDEDE00F7FFF7000000000000000000000000000000
      0000EFF7F700CEDEDE009C734A00F7940000FFA50000F7A50000D69408009C94
      7B0000000000FFF7FF00BD9C6B00FFAD0000FFAD0000B5A58C0000000000FFFF
      FF008C7B4200DE940000FFA50000FFA50000FFA50000FFA50000FFA50000FFA5
      0000FFA50000BD6B1800CEDEDE00F7FFFF00000000006363D600C6C6DE00E7E7
      E700EFEFF7008C8CEF000000CE000808D6000808D6000808D6001010D6001010
      D6001818DE001010D600BDBDF7000000000000000000BDBDF7001818DE003131
      E7003131E7003131E7003131E7003131E7003131E7003131E7005A5ADE00FFFF
      FF00F7F7F700E7E7F7005252D60000000000000000000000000000000000E7E7
      E7003139AD002118EF002929F7003131F7003939F7004242FF005252FF005A5A
      FF004A4AF7007B84BD00F7F7F700000000000000000000000000000000000000
      000000000000F7F7F700C6A58400FF940000FF9C0000FF7B0000AD9C8400F7F7
      F70000000000000000000000000000000000F7F7F700BDCECE0084847B00FFFF
      FF00BDCEBD00BDCEBD00C6CEC600217B3900005A0800C6D6CE00BDC6BD00ADBD
      AD0094A5940084948400F7F7F700B5BDB500ADB5AD00ADBDB500B5BDB500B5BD
      B500B5BDB500B5BDB500ADB5AD00ADB5AD00ADB5AD00ADB5A500A5B5A500A5B5
      A5009CAD9C0073847B00CED6D600F7F7F7000000000000000000000000000000
      0000F7FFFF00D6E7E700A5734A00F7940000FFA50000FFA50000DE9C0000947B
      29006B6B4A00C6BDBD00CEC6C600BD9C3900B5945200DED6D600A59C94007373
      5200A5842900E79C0000FFA50000FFB51800FFBD3900FFA50000FFA50000FFA5
      0000FFBD2900B55A1800DEE7E700FFFFFF00000000006363D600C6C6DE00E7E7
      E700EFEFF7008C8CEF000000CE000808D6000808D6001010D6001010D6001818
      DE001818DE001010D600DEDEFF000000000000000000DEDEFF001818DE003939
      E7003939E7003939E7003939E7003939E7003939E7003131E7006363DE00FFFF
      FF00F7F7F700DEDEF7005A5AD60000000000000000000000000000000000DEE7
      E7001018C6002929F7003131F7003939F7007B7BFF009494FF00A5A5FF00BDBD
      FF00BDBDFF00848CBD00FFFFFF00000000000000000000000000000000000000
      000000000000FFFFFF00CEAD8C00FFBD0000FFC60000FFAD0000C67B3900EFEF
      EF0000000000000000000000000000000000F7F7F700BDCECE008C8C84000000
      0000C6CEC600C6D6C600C6D6CE00529C6300428C5200DEE7DE00CEE7D600C6D6
      C600ADBDAD00ADBDB500EFE7E700BDC6BD00B5C6B500BDC6BD00BDCEC600C6CE
      C600C6CEC600C6CEC600C6CEC600C6CEC600C6CEC600BDC6BD00B5BDB500B5C6
      B500ADB5AD0073847B00CED6D600F7F7F7000000000000000000000000000000
      0000F7FFFF00D6E7E700A5734A00F7940000FFAD0000FFA50000EFA50000BD8C
      0800A5A59C0000000000DED6D600F7EFF700E7DEDE00EFE7E70000000000948C
      7300CE940800F7A50000FFA50000FFAD0000F7AD3900FFDE9C00FFDE8400FFDE
      9400EFA56300C69C7B00EFF7F70000000000000000007373DE00B5B5DE00E7E7
      E700F7F7F7009C9CEF000808D6000808D6001010D6001010D6001818DE001818
      DE002121DE001010D600000000000000000000000000000000001818DE003939
      EF004242EF004242EF004242EF004242EF004242EF003131DE007B7BE700FFFF
      FF00F7F7F700D6D6EF006363D60000000000000000000000000000000000DEE7
      E7001018BD002921EF002929EF001018CE002931CE003131D6003131D6003939
      D6003131DE00B5B5DE00E7E7E700DEDEDE00E7E7E700F7F7F700EFF7F700DEE7
      E700E7E7E700F7F7F700F7E7D600D68C5200FFA50000FFB50000C6733900EFEF
      EF0000000000000000000000000000000000F7F7F700BDCECE007B7B73000000
      0000C6D6CE00C6D6CE00CED6CE00D6DED600D6E7DE00DEEFE700DEF7E700D6E7
      DE00C6D6C600C6D6C600E7DEDE00CED6CE00CED6CE00D6DED600D6DED600D6DE
      DE00D6E7DE00DEE7DE00DEE7DE00D6E7DE00D6DED600D6DED600CED6CE00C6CE
      C600B5BDB50073847B00CEDEDE00F7FFFF000000000000000000000000000000
      0000FFFFFF00DEE7E700A57B4A00F7940000FFAD0000FFAD0000FFA50000DE9C
      00009C843100B5B5B50084736B0000000000E7DEE7008C847B00BDBDB500AD8C
      1800E79C0000FFAD0000FFAD0000FFAD0000CE630000BD632100E7944200E77B
      1800CE845200E7EFEF00FFFFFF0000000000000000009494E7009C9CDE00E7E7
      E700EFEFEF00ADADEF002929D6000808D6001010D6001818D6001818DE002121
      DE002121DE003131DE00000000000000000000000000000000003939DE003939
      EF004242EF004A4AEF004A4AEF004A4AEF004A4AEF002121D600C6C6F700FFFF
      FF00FFFFFF00B5B5EF008484DE0000000000000000000000000000000000DEE7
      E7001018BD002121EF001818E7003942A500E7EFE7000000000000000000FFFF
      FF0000000000E7E7E7005A639C00394A7B005A639C00D6D6D600BDAD9C009473
      5200947B5A00C6C6BD00F7F7F700CECED600FF9C0000FFBD0000C67B3900EFEF
      EF0000000000000000000000000000000000F7F7F700C6D6D600737B7300FFFF
      FF00CEDED600CEDED600CEDED600CEDED600C6D6CE00BDCEBD00ADBDAD00ADBD
      B500B5CEBD00D6DED600E7D6D600D6DED600D6DED600D6E7DE00DEE7DE00DEE7
      DE00DEE7DE00E7EFE700E7EFE700E7EFE700DEEFE700DEE7DE00CEDED600CED6
      CE00B5C6BD007B847B00DEE7E700FFFFFF000000000000000000000000000000
      000000000000E7EFEF00AD7B5200F79C0000FFAD0000FFAD0000FFAD0000F7AD
      0000DE9C0000BD9408009C842900A5947B009C946B009C842100BD8C1000DE9C
      0000F7AD0000FFAD0000FFAD0000FFB50000D6630000A5C6C600D6BDAD00E7DE
      D600F7F7F700FFFFFF00000000000000000000000000BDBDEF007B7BD600E7E7
      E700EFEFEF00CECEF7005252DE001010D6001010D6001818DE002121DE002121
      DE002121DE005252DE00000000000000000000000000000000005252E7003939
      EF004A4AEF004A4AEF004A4AEF004A4AEF004242EF002121D600FFFFFF00FFFF
      FF00FFFFFF008C8CDE00B5B5EF0000000000000000000000000000000000DEE7
      E7001018BD002118EF001818E7003942AD00EFF7EF0000000000000000000000
      000000000000D6D6D6002929F7006363FF003131F700BDC6C600CE7B4200FFCE
      0000FFA5000094735A00A5ADAD008C949400FF9C0000FFBD0000C67B3900EFEF
      EF0000000000000000000000000000000000F7FFFF00CEDEDE00737B7300F7F7
      F700D6E7DE00D6E7DE00D6E7D600D6E7D600CEDED600BDD6C600ADBDAD0094AD
      9C0073847300CED6CE00D6C6C600D6E7D600D6E7DE00DEE7DE00DEE7DE00DEE7
      DE00DEEFE700E7F7EF00E7EFEF00E7EFE700E7EFE700DEEFE700D6DED600CEDE
      D600A5ADA5008C9C9400E7EFEF00000000000000000000000000000000000000
      000000000000EFF7F700BDA58C00F7A53900FFBD1800FFB50000FFB50000FFAD
      0000F7AD0000EFA50000DEA50000CE9C0800CE9C0800DEA50000EFA50000F7AD
      0000FFAD0000FFAD0000FFB50000FFB50000D6630000C6DED600EFF7F7000000
      00000000000000000000000000000000000000000000F7F7FF004242CE00E7E7
      E700E7E7E700F7F7F7008C8CEF003131DE001818D6001818DE002121DE002929
      DE002121DE005252DE00000000000000000000000000000000005A5AE7004242
      EF005252F7005252F7005252F7005252F7002929DE009494EF00FFFFFF00FFFF
      FF00FFFFFF005252D600EFEFFF0000000000000000000000000000000000DEE7
      E7001010BD001818E7001818E7003942AD00EFEFEF0000000000000000000000
      000000000000CED6D6003131F7007B7BFF003939F700BDC6C600C67B4200FFDE
      0000FFCE0000D65A0000CE5A0000CE520000FFAD0000FFC60000C67B4200EFEF
      EF0000000000000000000000000000000000FFFFFF00DEE7E7007B848400D6D6
      D600E7F7E700D6EFDE00D6E7DE00D6E7DE00CEDED600BDCEC600ADBDAD00849C
      8C006B847300F7EFEF00CEC6BD00D6E7DE00DEE7DE00DEE7DE00DEE7DE00DEE7
      DE00E7F7EF00EFF7EF00E7F7EF00E7F7EF00E7F7EF00DEEFE700D6E7D600CEDE
      D600848C8400BDCEC600F7F7F700000000000000000000000000000000000000
      000000000000F7FFFF00DEE7DE00CE631800EFAD6300F7C67B00F7C67B00FFDE
      9C00FFDE8400FFC63100F7B50000F7AD0000F7AD0000FFBD1800FFDE8400FFDE
      8400FFDE8400FFDE8400FFE79C00FFC67B00D6732100E7EFEF00FFFFFF000000
      00000000000000000000000000000000000000000000000000007B7BDE00ADAD
      DE00EFEFEF00EFEFEF00D6D6F7005252DE002121DE001818DE002121DE002929
      DE002929DE005252E700000000000000000000000000000000005A5AE7004A4A
      EF005252F7005A5AF7005A5AF7003939E7003131D600F7F7FF00FFFFFF00FFFF
      FF00C6C6EF006B6BD6000000000000000000000000000000000000000000DEE7
      E7001010BD001818E7001010E7003942AD00EFEFEF0000000000000000000000
      000000000000D6D6D6003129F7006B6BFF003131F700C6CECE00DE8C5200FFD6
      000000000000FFFFEF00FFFFB500FFF77B00FFE74A00FFD61800D68C4A00F7F7
      F7000000000000000000000000000000000000000000EFF7EF0094A59C00B5B5
      B500DEE7DE00D6E7D600D6E7DE00CEDED600C6D6CE00BDCEBD0094AD9C00738C
      7B00A5B5A500DECECE00CED6CE00DEEFDE00DEEFE700DEEFE700DEE7DE00EFFF
      F700EFFFF700EFFFF700EFFFF700EFFFF700EFFFEF00DEEFE700CEDED6009CAD
      9C008C9C9400EFF7F70000000000000000000000000000000000000000000000
      00000000000000000000F7FFFF00E7E7E700D6BD9C00CE946B00C68C6300AD7B
      4A00B5520000FFAD0000FFB50000FFB50000FFB50000FFBD0800AD520800B55A
      2100BD632100C6632900C67B4200CE946300DEC6AD00F7F7F700000000000000
      0000000000000000000000000000000000000000000000000000D6D6F7006363
      D600EFEFEF00EFEFEF00F7F7F700B5B5EF004242DE002121DE002121DE002929
      E7002929E7004242DE00BDBDF700BDBDF700BDBDF700BDBDF7004A4AE7004A4A
      EF005A5AF7005A5AF7004242EF001818D600D6D6F700FFFFFF00FFFFFF00FFFF
      FF007373DE00C6C6EF000000000000000000000000000000000000000000DEE7
      E7001010BD001010DE001010DE003942AD00EFF7EF0000000000000000000000
      000000000000D6D6D6002921EF005A5AFF002929EF00D6D6D600EFDECE00FF8C
      1000FF8C0000FF8C0000FF8C0000FF840000FF840000FF840000E7DECE000000
      00000000000000000000000000000000000000000000F7F7F700C6CECE007B84
      7B00000000009CBDAD00A5BDAD00A5BDAD009CB5A5008C9C8C007B948400738C
      7B00EFEFE700C6B5B500DEF7E700DEEFDE00B5C6B500848C84007B847B008494
      8C008C948C008C948C0084948C009CA59C007B847B007B847B007B8473009CA5
      9C00F7F7F7000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000F7FFFF00F7F7F700E7EFEF00B5CE
      CE00B5731000FFBD0000FFBD0000FFBD0000FFBD0000FFBD0000D6840000A5C6
      C600DEE7E700EFF7F700F7F7F700F7F7F700FFFFFF0000000000000000000000
      0000000000000000000000000000000000000000000000000000000000008484
      DE009494DE00EFEFEF00EFEFEF00F7F7F700A5A5EF004242DE003131DE002929
      E7003131E7003131E7002929DE002929E7003131E7003131E7004A4AEF005A5A
      F7005A5AF7003939E7002121D600C6C6F700FFFFFF00FFFFFF00FFFFFF00A5A5
      E7007373DE00000000000000000000000000000000000000000000000000DEE7
      E7001010BD001010DE001010DE0031399C00BDC6C600D6D6D600CED6D600D6D6
      D600D6D6D600ADB5AD002121EF004A4AFF002921EF00D6D6D600000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000EFEFEF008494
      8C00D6D6D600D6DED6008CA59400849C8C00849C84007B9484007B947B00BDCE
      C600EFE7E700DEE7DE00ADBDAD007B847B00949C9400CED6D600F7F7F700F7F7
      F700F7FFFF00F7FFFF00F7FFFF00F7FFFF00F7FFF700F7F7F700F7FFFF00FFFF
      FF00000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000F7F7F700C6D6
      D600DE731800FFC60000FFBD0000FFBD0000FFBD0000FFBD0000EF9C3900BDB5
      A500EFF7F7000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000EFEF
      FF005252D600A5A5DE00EFEFEF00EFEFEF00F7F7F700BDBDEF005252DE003939
      DE003131E7003939E7004242EF004A4AEF004A4AEF005252F7005252F7004242
      EF002121DE004A4ADE00DEDEF700FFFFFF00FFFFFF00FFFFFF00BDBDEF005252
      CE00EFEFFF00000000000000000000000000000000000000000000000000DEE7
      E7001010BD000808DE000808DE000008A5001018840010188C0010188C001018
      8C0010218C0010187B001818E7003939FF002121EF00D6D6D600000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000F7FFFF00CED6
      D6007B847B00FFFFFF00B5C6BD007B9484007B9484007B947B00B5BDB5000000
      0000C6C6BD008C948C0084948C00D6DEDE00F7FFFF0000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000FFFFFF00DEE7
      E700D6732900FFFFD600FFDE6300FFC61800FFCE3100FFF7BD00DE7B3100D6E7
      DE00F7FFFF000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000DEDEF7004242CE00B5B5E700EFEFEF00EFEFEF00F7F7F700EFEFF700A5A5
      EF005A5ADE003131D6002929DE003131DE002929DE002121DE001818D6005A5A
      DE00BDBDF700FFFFFF00FFFFFF00FFFFFF00FFFFFF00CECEEF004242CE00D6D6
      F70000000000000000000000000000000000000000000000000000000000E7E7
      E7001010BD000808DE000808DE001010DE001010E7001010E7001818EF001818
      EF002121EF002121EF002929EF003131F7001818EF00D6DED600000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000F7F7
      F700ADB5B50094948C00FFFFFF00F7F7F700E7E7E700F7F7F70000000000CEC6
      C6007B847B00ADBDB500F7F7F700000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000EFF7
      F700CEA58400DE945200FFF7E70000000000FFFFF700EFAD7300C68C5A00EFF7
      F700000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000CECEF7004A4ACE00A5A5E700EFEFEF00F7F7F700F7F7F700F7F7
      F700F7F7F700E7E7F700D6D6F700ADADEF00BDBDEF00CECEF700F7F7FF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00B5B5EF004242CE00C6C6EF000000
      000000000000000000000000000000000000000000000000000000000000F7F7
      F7003131C6000800DE004A4AE7005252E7005A5AEF006B6BEF007373F700847B
      F7008C8CF7009494FF009C9CFF002929F7001008DE00E7EFEF00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000F7F7F700B5BDB5007B847B00B5BDB500DEDEDE00C6C6C600A5A59C007384
      7300CED6D600F7FFFF0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000EFF7F700D6C6AD00C67B4200C6632900C67B4200D6C6AD00EFF7F700FFFF
      FF00000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000DEDEF7005A5AD6009494DE00EFEFF700F7F7F700F7F7
      F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7F700FFFFFF00F7F7F700FFFF
      FF00FFFFFF00FFFFFF00F7F7FF009C9CE7005252D600D6D6F700000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000E7E7EF006363D6006363D6006363CE006363CE006363CE006363CE006363
      CE006363CE006363CE006363CE006363D600BDBDE70000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000FFFFFF00DEE7E700ADB5B5008C948C00949C9400B5BDBD00EFEF
      EF00000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000FFFFFF00F7F7F700F7F7F700F7F7F700FFFFFF00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000F7F7FF009494E7004242CE009C9CE700DEDE
      EF00F7F7F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7F700FFFFFF00FFFF
      FF00E7E7F700A5A5E7004242CE008C8CE700F7F7FF0000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000EFEFFF009494E7005252
      D6006363D6008C8CDE009C9CE700ADADE700ADADE7009C9CE7008C8CDE006363
      D6005252D6009494E700E7E7F700000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000DEDEF700B5B5EF00A5A5E7008C8CDE008C8CDE009C9CE700B5B5EF00DEDE
      F700000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000006B6BFF006363FF005252FF000031
      9C0000000000000000000000000000000000000000001010FF000000FF000000
      FF0000319C000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000006B6BFF006363FF005252
      FF0000319C000000000000000000000000002121FF001818FF001010FF000031
      9C00000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000004284000042840000428400004284000042840000428400000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000006B6BFF006363
      FF005252FF0000319C00000000003939FF003131FF002121FF0000319C000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000031313100313131003131
      310031313100313131003131310031313100313131003131310031313100009C
      FF00009CFF00009CFF00009CFF00009CFF003131310031313100313131003131
      3100313131003131310031313100313131003131310031313100313131003131
      3100313131003131310000000000000000000000000000000000000000000000
      000000000000F7FFFF00F7FFFF00F7F7F700E7EFEF00D6E7DE00C6D6D600BDCE
      CE00BDCECE00CEDEDE00DEEFE700EFF7EF00EFF7F700EFEFEF00E7EFEF00D6DE
      DE00C6D6D600C6D6D600CEDEDE00DEE7E700EFF7F700F7F7F700F7FFFF000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000006B6B
      FF006363FF005252FF0000319C004242FF003939FF0000319C00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000D6D6D600D6D6D600D6D6
      D600D6D6D600D6D6D600D6D6D600D6D6D600D6D6D600D6D6D600D6D6D60084FF
      FF0031FFFF0031FFFF0031FFFF0031FFFF00009CFF00D6D6D600D6D6D600D6D6
      D600D6D6D600D6D6D600D6D6D600D6D6D600D6D6D600D6D6D600D6D6D600D6D6
      D600D6D6D6005A5A5A0000000000000000000000000000000000FFFFFF00FFFF
      FF00F7FFFF00F7F7F700F7F7F700EFF7EF00D6E7E700ADC6C60084ADA5006B94
      9400739C940094B5AD00C6D6CE00DEE7E700DEEFE700DEE7E700C6D6D6009CBD
      B5007BA59C007BA59C0094B5AD00BDCECE00DEE7E700EFF7F700F7F7F700F7FF
      FF00FFFFFF00FFFFFF0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00006B6BFF006363FF005252FF004A4AFF0000319C0000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000031CEFF0031CEFF0031CEFF0031CEFF0031CEFF00009CFF00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FFFFFF00F7FFFF00F7F7
      F700EFF7F700EFF7F700EFF7F700E7EFEF00BDCECE007B8C8C005A6B6B005263
      63006B7373005A6B6B008CADA500B5CEC600BDD6CE00B5CEC60094B5AD005A73
      7300636B7300526363005A737300849C9C00CEDEDE00EFEFEF00F7F7F700F7F7
      F700F7FFFF00F7FFFF000000000000000000000000000000000000000000FFFF
      FF00F7F7F700F7F7F700EFF7F700EFF7F700EFF7F700EFF7F700EFF7F700EFF7
      F700EFF7F700EFF7F700EFF7F700EFF7F700EFF7F700EFF7F700EFF7F700EFF7
      F700EFF7F700EFF7F700EFF7F700EFF7F700EFF7F700EFF7F700EFF7F700EFF7
      F700F7F7F700FFFFFF0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00007373FF006B6BFF006363FF005252FF0000319C00004A7300000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000D6D6D600737373003131310000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000F7FFFF00EFF7F700E7EF
      EF00D6E7DE00D6E7DE00DEE7E700CED6D6006B6B73007B84840094949400ADAD
      A500ADA59C00737B7B005A737300739C940084A59C00739C9400526B6B00737B
      7B00ADAD9C009CA59C00848C8C006B737B00636B7300CEDEDE00E7EFEF00E7EF
      EF00EFEFEF00EFF7F700F7FFFF00000000000000000000000000F7F7F700E7E7
      E700CED6D600BDCEC600B5C6C600B5C6C600B5C6C600B5C6C600B5C6C600B5C6
      C600B5C6C600B5C6C600B5C6C600B5C6C600B5C6C600B5C6C600B5C6C600B5C6
      C600B5C6C600B5C6C600B5C6C600B5C6C600B5C6C600B5C6C600B5C6C600BDC6
      C600C6D6CE00DEE7E700F7F7F700000000000000000031313100313131003131
      3100313131003131310031313100313131003131310031313100313131008C8C
      FF007B7BFF007373FF0000319C006363FF005252FF0000319C00313131003131
      3100313131003131310031313100313131003131310031313100313131003131
      3100313131003131310000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000B5B5B5005A5A5A003131310000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000FFFFFF00F7F7F700E7EFEF00C6D6
      CE00A5BDB5009CB5B500A5BDBD009CADAD006B737B00CECEB500CEC6AD00CEC6
      AD00B5B59C00737363006B737B004A6B63004A6B6300426B63006B737B009494
      8400BDBDA500C6C6AD00CEC6AD00CECEB5007B848400A5B5B500BDCECE00B5CE
      C600C6D6D600DEE7E700EFF7F700FFFFFF0000000000FFFFFF00E7EFEF00B5C6
      BD007B9494005A7B7B0052737300527373005273730052737300527373005273
      7300527B7300527B7300527B7300527B7B00527B7B00527B7B00527B7300527B
      7300527373005273730052737300527373005273730052737300527373005A7B
      7300738C8C00A5B5B500DEE7E700FFFFFF0000000000DEDEDE00DEDEDE00DEDE
      DE00DEDEDE00DEDEDE00DEDEDE00DEDEDE00DEDEDE00DEDEDE009C9CFF009494
      FF008C8CFF0000319C0029FFFF006B6BFF006363FF005252FF0000319C00DEDE
      DE00DEDEDE00DEDEDE00DEDEDE00DEDEDE00DEDEDE00DEDEDE00DEDEDE00DEDE
      DE00DEDEDE006363630000000000000000000000000031313100313131003131
      3100313131003131310031313100313131003131310031313100313131003131
      3100313131003131310031313100313131003131310031313100313131003131
      3100313131003131310031313100313131003131310031313100313131003131
      310031313100000000000000000000000000F7FFFF00EFF7F700D6E7DE00849C
      9C00637B7B00527B73005A847B00638484006B737B00CEC6AD00C6C6AD00C6C6
      AD00B5B59C00736B6300737B6B00737B7B007B7B7B00737B7B00949484009494
      8400BDB5A500C6C6AD00C6C6AD00CEC6AD007B84840073948C00739C94006B94
      8C007B9C9400C6D6CE00EFEFEF00F7FFFF0000000000F7F7F700CED6D600848C
      7B00845A1000945A08008C5A08008C5A08008C5A0800945A0800946308009C63
      0800A56B1000AD731000B5731000B57B1000B57B1000B57B1000AD731000A56B
      10009C63100094630800945A0800945A08008C5A08008C5A08008C5A08008C5A
      08008C5A100073846B00C6D6CE00F7F7F7000000000000000000000000000000
      00000000000000000000000000000000000000000000A5A5FF00A5A5FF009C9C
      FF0000319C004ABDFF004ABDFF004ABDFF006B6BFF006363FF005252FF000031
      9C00000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000006363630063636300636363006363
      6300636363006363630063636300636363006363630063636300636363006363
      6300636363006363630063636300636363006363630063636300636363006363
      6300636363006363630063636300636363006363630063636300636363006363
      630063636300313131000000000000000000FFFFFF00F7F7F700B5C6C6006B73
      7300848C8C00737B7B00637373005A636B0063737300C6C6AD00C6C6AD00C6C6
      AD00B5AD9C006B6B5A0073736300A59C8C00A59C8C009C9C8C009C9484009494
      7B00BDB5A500C6C6AD00C6C6AD00C6C6AD007B84840052636B005A6B6B006373
      73006B737B007B848C00EFEFEF00F7FFFF0000000000F7F7F700BDCECE007B63
      2900CEB594000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000EFDEC6008C5A1000BDCEC600F7F7F7000000000000000000000000000000
      000000000000000000000000000000000000A5A5FF00A5A5FF00A5A5FF000031
      9C000000000000000000DEDEDE007B7B7B00313131006B6BFF006363FF005252
      FF0000319C000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000E7E7E700B5B5B500B5B5B500B5B5
      B500B5B5B500B5B5B500B5B5B500B5B5B500B5B5B500B5B5B500B5B5B500B5B5
      B500B5B5B500B5B5B500B5B5B500B5B5B500B5B5B500B5B5B500B5B5B500B5B5
      B500B5B5B500B5B5B500B5B5B500B5B5B500B5B5B500B5B5B500B5B5B500B5B5
      B50063636300313131000000000000000000FFFFFF0000000000636B7300ADAD
      A500B5B59C00A5A58C00A59C8C0094948C00848C8400C6C6AD00C6BDA500C6BD
      A500ADAD94006B6B5A006B6B5A009C9C8C009C9C8C009C9C8C0094948400948C
      7B00B5B59C00C6BDAD00C6BDAD00C6C6AD008C948C008C8C840094948C009C9C
      8C009C9C8C006B737B00CED6D6000000000000000000F7F7F700BDC6C600945A
      1000EFE7CE0073B5FF00107BF700107BF7001084F7001084F700108CF7001894
      F70018A5F70021ADF70021BDFF0021C6FF0021C6FF0021BDFF0021B5F70018A5
      F700189CF700188CF7001084F700218CF70052A5F70052A5F70052A5F7004AA5
      FF00E7F7FF00945A0800BDC6C600EFF7F7000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000BDBDBD00636363003131310000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000E7E7E700B5B5B500848484006363
      6300636363006363630063636300636363006363630063636300636363006363
      6300636363006363630063636300636363006363630063636300636363006363
      630063636300636363006363630063636300636363006363630084848400B5B5
      B5006363630031313100313131000000000000000000D6D6D600737B8400DEDE
      BD00ADAD9C00A5A58C00A5A58C00A5A58C00A5A59400DEDECE00E7E7DE00F7F7
      EF0000000000C6C6BD006B6B5A009C9C8C009C9C84009C9C840094947B00BDBD
      AD00F7F7E700EFEFDE00DEDED600CECEBD00A5A58C009C9C8400A59C8C00A59C
      8C00A59C8C00848C8400949C9C000000000000000000EFF7F700B5C6C600945A
      1000EFE7CE007BBDFF001084EF001884EF001884EF00188CF7002194F700219C
      F70021ADF70029BDF70029C6F70029CEFF0029CEFF0029CEFF0029BDF70029B5
      F70021A5F7002194F700188CF7001884F7001884EF001884EF001884EF00107B
      F700D6EFFF00945A0800B5C6C600EFF7F7000000000031313100313131003131
      3100313131003131310031313100313131003131310031313100313131003131
      3100313131003131310031313100313131003131310031313100313131003131
      3100313131003131310031313100313131003131310031313100313131003131
      310031313100000000000000000000000000E7E7E700B5B5B500A5A5A500FFFF
      FF00F7F7F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7
      F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7
      F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7F700A5A5A500B5B5
      B5006363630031313100313131000000000000000000D6DEDE00848C8400DED6
      BD00ADAD9400A59C8C00A5A58C00A59C8C00CECEC60000000000FFFFF700FFF7
      F700FFF7EF00FFFFF7009C9C8C009C9484009C9484009C948400ADA59400F7EF
      DE00EFE7CE00F7EFD600FFF7E700FFFFF700CECEBD009C9C84009C9C8C009C9C
      8C009C948C007B848C007B848C000000000000000000EFF7F700BDC6C6008C5A
      1000EFE7CE0073B5FF00107BEF001884EF001884F700188CF7002194F70021A5
      F70029B5F70029C6FF0029CEFF0031D6FF0029D6FF0029CEFF0029C6FF0029B5
      F70021A5F700219CF700188CF700188CF7001884EF001884EF001884EF00107B
      F700D6EFFF00945A0800BDC6C600EFF7F7006363630063636300636363006363
      6300636363006363630063636300636363006363630063636300636363006363
      6300636363006363630063636300636363006363630063636300636363006363
      6300636363006363630063636300636363006363630063636300636363006363
      630063636300313131000000000000000000E7E7E700B5B5B500B5B5B500B5B5
      B500B5B5B500B5B5B500B5B5B500B5B5B500B5B5B500B5B5B500B5B5B500B5B5
      B500B5B5B500B5B5B500B5B5B500B5B5B500B5B5B500B5B5B500B5B5B500B5B5
      B500B5B5B500B5B5B500B5B5B500B5B5B500B5B5B500B5B5B500B5B5B500B5B5
      B5006363630031313100313131003131310000000000D6DEDE007B848400DED6
      BD00ADAD94009C9C8C00A59C8C00A59C8C009C9C8400F7EFEF00FFFFF700FFF7
      F700FFF7EF00E7F7EF00CEEFEF009CC6CE009CBDCE0094B5BD00D6E7D600E7DE
      B500EFE7C600EFEFD600FFF7E700F7EFE7009C9C8C009C9C84009C9C84009C9C
      84009494840073848C007B848C000000000000000000EFF7F700BDC6C6008C5A
      1000EFDECE0094CEFF004A9CF70052A5F70052A5F70052ADF7005AB5FF005AC6
      FF005ACEFF0063D6FF0063E7FF0063E7FF0063E7FF0063E7FF0063DEFF0063D6
      FF005AC6FF005AB5FF0052ADFF0052ADFF0052A5F70052A5F7004A9CF7004A9C
      F700E7F7FF00945A0800BDC6C600EFF7F700DEDEDE00BDBDBD00BDBDBD00BDBD
      BD00BDBDBD00BDBDBD00BDBDBD00BDBDBD00BDBDBD00BDBDBD00BDBDBD00BDBD
      BD00BDBDBD00BDBDBD00BDBDBD00BDBDBD00BDBDBD00BDBDBD00BDBDBD00BDBD
      BD00BDBDBD00BDBDBD00BDBDBD00BDBDBD00BDBDBD00BDBDBD00BDBDBD00BDBD
      BD0063636300313131000000000000000000E7E7E700B5B5B500848484006363
      6300636363006363630063636300636363006363630063636300636363006363
      6300636363006363630063636300636363006363630063636300636363006363
      630063636300636363006363630063636300636363006363630084848400B5B5
      B5006363630031313100313131003131310000000000DEDEDE007B848400E7DE
      CE00DED6CE00BDBDAD00A5A58C009C9C84009C9C840094947B00FFF7F700FFF7
      F700CEEFF700B5E7EF00B5DEEF00ADD6E700A5CEDE00A5CED6009CCECE009CCE
      CE00E7E7CE00F7EFD600E7E7DE0094948400949484009C948400949484009C9C
      8C00A5A59C007384840084848C000000000000000000EFF7F700BDC6C6008C5A
      1000EFDECE0000000000000000000000000000000000E7D6CE006B181800B57B
      730000000000B5635A00A5393900EFCECE00A53939009C312900B56B6300B573
      7300AD736B0000000000F7E7DE008C524A00D6BDBD0000000000000000000000
      0000000000008C5A0800BDC6C600EFF7F700DEDEDE00BDBDBD00848484006363
      6300636363006363630063636300636363006363630063636300636363006363
      6300636363006363630063636300636363006363630063636300636363006363
      630063636300636363006363630063636300636363006363630084848400BDBD
      BD0063636300313131003131310000000000D6D6D600B5B5B500A5A5A500F7F7
      F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7
      F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7
      F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7F700A5A5A500B5B5
      B5006363630031313100313131003131310000000000DEDEDE007B8484000000
      0000000000000000000000000000F7F7F700DEDED600F7F7EF00FFF7F700FFF7
      EF00BDEFF700BDE7EF00B5DEE700ADD6E700A5CEDE00A5CED6009CCECE009CCE
      CE00DEDECE00F7EFD600FFFFF700CECEBD00CECEC600E7E7DE00F7F7F7000000
      00000000000094A5A50084848C000000000000000000EFF7F700BDC6C6008C5A
      1000E7DECE0000000000000000000000000000000000DECECE006B2121007B29
      2100EFDEDE00CEA5A50094313100CE949400D6A5A500EFCECE009C4242008C31
      31007B2929008C524A00844A4A005A181800DECECE0000000000000000000000
      0000000000008C5A0800B5C6C600EFF7F700DEDEDE00BDBDBD00ADA5A500FFFF
      FF00EFEFEF00EFEFEF00EFEFEF00EFEFEF00EFEFEF00EFEFEF00EFEFEF00EFEF
      EF00EFEFEF00EFEFEF00EFEFEF00EFEFEF00EFEFEF00EFEFEF00EFEFEF00EFEF
      EF00EFEFEF00EFEFEF00EFEFEF00EFEFEF00EFEFEF00EFEFEF00ADA5A500BDBD
      BD0063636300313131003131310000000000D6D6D600B5B5B500B5B5B500B5B5
      B500B5B5B500B5B5B500B5B5B500B5B5B500B5B5B500B5B5B500B5B5B500B5B5
      B500B5B5B500B5B5B500B5B5B500B5B5B500B5B5B500B5B5B500B5B5B500B5B5
      B500B5B5B500B5B5B500B5B5B500B5B5B500B5B5B500B5B5B500B5B5B500B5B5
      B5006363630031313100313131003131310000000000DEDEDE00ADADB5000000
      000000000000FFFFFF00FFFFF700FFFFFF00FFFFF700FFF7F700FFF7F700FFF7
      EF00C6EFEF009CD6DE0063ADD60052A5CE004A9CCE004A9CC6007BB5C600A5CE
      C600DEDEC600F7EFD600F7F7DE00FFFFEF00FFFFF700FFFFF700FFFFF700FFFF
      F70000000000EFEFE7007B8484000000000000000000EFF7F700BDC6C6008C5A
      1000E7DECE0000000000000000000000000000000000DED6D6006B2121008C4A
      42009C5A5A00F7EFEF0094393100C68C8C0000000000BD7B7B00943131009C4A
      4A00C6A5A5007B3131009C7373005A181800DECECE0000000000000000000000
      0000000000008C5A0800B5C6C600EFF7F700DEDEDE00BDBDBD00BDBDBD00BDBD
      BD00BDBDBD00BDBDBD00BDBDBD00BDBDBD00BDBDBD00BDBDBD00BDBDBD00BDBD
      BD00BDBDBD00BDBDBD00BDBDBD00BDBDBD00BDBDBD00BDBDBD00BDBDBD00BDBD
      BD00BDBDBD00BDBDBD00BDBDBD00BDBDBD00BDBDBD00BDBDBD00BDBDBD00BDBD
      BD0063636300313131003131310031313100D6D6D600B5B5B500B5B5B5008484
      8400A5A5A50084848400A5A5A50084848400A5A5A50084848400A5A5A5008484
      8400B5B5B500B5B5B500B5B5B500B5B5B500B5B5B500B5B5B500B5B5B500B5B5
      B500B5B5B500B5B5B500B5B5B500319C3100319C3100319C3100B5B5B500B5B5
      B5006363630031313100313131003131310000000000F7F7F7007B848C00C6CE
      C600EFE7E700FFFFFF0000000000FFFFF700FFF7F700FFF7F700FFEFEF00EFDE
      DE0039A5CE00189CD60018A5E70031ADEF0052ADEF000894E7000894DE001084
      C600B5C6BD00EFE7CE00F7EFDE00FFF7E700FFFFEF00FFFFF700000000000000
      000000000000DEDEDE008C8C94000000000000000000EFF7F700BDC6C6008C5A
      1000E7DECE0000000000000000000000000000000000CEB5B5006B212100D6BD
      BD008C393900CEA5A500A5525200A5424200D6ADA5009C393100A55A5A00FFF7
      F7000000000084424200733131005A181800E7DEDE0000000000000000000000
      0000000000008C5A0800B5C6C600EFF7F700DEDEDE00BDBDBD00848484006363
      6300636363006363630063636300636363006363630063636300636363006363
      6300636363006363630063636300636363006363630063636300636363006363
      630063636300636363006363630063636300636363006363630084848400BDBD
      BD0063636300313131003131310031313100D6D6D600B5B5B500B5B5B500A5A5
      A500F7F7F700A5A5A500F7F7F700A5A5A500F7F7F700A5A5A500F7F7F700A5A5
      A500B5B5B500B5B5B500B5B5B500B5B5B500B5B5B500B5B5B500B5B5B500B5B5
      B500B5B5B500B5B5B500B5B5B50063FF310063FF3100319C3100B5B5B500B5B5
      B5006363630031313100313131003131310000000000000000007B848C008484
      7B008C8C73008C8473009C9C8C00F7F7F700FFF7F700F7EFEF00F7E7DE00528C
      B50039CEF70031BDF70021B5EF0063C6F700ADDEFF00109CEF0018A5EF0018AD
      EF00187BB500EFDEC600F7EFD600F7F7E700FFFFF700D6D6CE00ADADA5009C9C
      8400848C7B00636B7300F7F7F7000000000000000000EFF7F700BDC6C6008C5A
      1000E7DECE0000000000000000000000000000000000B59494006B211800E7D6
      DE00C69C9C0094423900BD7B7B009C393900BD7B7B009C313100C69C9400C69C
      9C00DEC6C600DEC6C600632118005A1818000000000000000000000000000000
      0000000000008C5A0800B5C6C600EFF7F700DEDEDE00BDBDBD00ADA5A500EFEF
      EF00EFEFEF00EFEFEF00EFEFEF00EFEFEF00EFEFEF00EFEFEF00EFEFEF00EFEF
      EF00EFEFEF00EFEFEF00EFEFEF00EFEFEF00EFEFEF00EFEFEF00EFEFEF00EFEF
      EF00EFEFEF00EFEFEF00EFEFEF00EFEFEF00EFEFEF00EFEFEF00ADA5A500BDBD
      BD0063636300313131003131310031313100D6D6D600B5B5B500B5B5B500B5B5
      B500B5B5B500B5B5B500B5B5B500B5B5B500B5B5B500B5B5B500B5B5B500B5B5
      B500B5B5B500B5B5B500B5B5B500B5B5B500B5B5B500B5B5B500B5B5B500B5B5
      B500B5B5B500B5B5B500B5B5B500B5B5B500B5B5B500B5B5B500B5B5B500B5B5
      B5006363630031313100313131003131310000000000000000007B848C00BDC6
      BD00E7DEDE00F7F7F70000000000FFFFFF00FFF7F700F7EFEF00EFDED6002173
      AD0042DEFF0031B5F70021ADEF0063C6F700ADDEFF00109CEF0018A5EF0018AD
      F7000073BD00E7CEB500EFE7D600F7F7E700FFFFF700EFEFE700D6D6CE00BDBD
      AD00A5A594007B848C00000000000000000000000000EFF7F700BDC6C6008C5A
      1000EFDECE00000000000000000000000000F7EFEF00946363008C5A5A00EFE7
      E70000000000B5737300C68C8C00B56B6B00E7C6C600CE9C9400AD6B6B00A563
      6300CEADAD0000000000A57B7B00845A52000000000000000000000000000000
      0000000000008C5A0800B5C6C600EFF7F700DEDEDE00BDBDBD00BDBDBD00BDBD
      BD00BDBDBD00BDBDBD00BDBDBD00BDBDBD00BDBDBD00BDBDBD00BDBDBD00BDBD
      BD00BDBDBD00BDBDBD00BDBDBD00BDBDBD00BDBDBD00BDBDBD00BDBDBD00BDBD
      BD00BDBDBD00BDBDBD00BDBDBD00BDBDBD00BDBDBD00BDBDBD00BDBDBD00BDBD
      BD0063636300313131003131310031313100D6D6D600CECECE00CECECE00CECE
      CE00CECECE00CECECE00CECECE00CECECE00CECECE00CECECE00CECECE00CECE
      CE00CECECE00CECECE00CECECE00CECECE00CECECE00CECECE00CECECE00CECE
      CE00CECECE00CECECE00CECECE00CECECE00CECECE00CECECE00CECECE00CECE
      CE00B5B5B50031313100313131003131310000000000000000009CA5A500EFEF
      EF000000000000000000FFFFFF00FFFFFF00FFF7F700F7EFEF00F7DED6002173
      AD0042DEFF0029ADF70021A5EF0063C6F700ADDEFF00109CEF00109CEF0018AD
      F7000073BD00E7CEB500EFE7D600F7F7E700FFFFEF00FFFFF700000000000000
      0000000000007B848400000000000000000000000000EFF7F700BDC6C6008C5A
      1000EFE7D600D6C6C600AD949400B5949400B5949400B59C9C00BD9C9C00BD9C
      9C00C6A59C00CEA5A500D6A5A500D6ADA500D6ADA500D6A5A500CEA5A500CEA5
      A500C69C9C00BD9C9C00BD9C9C00B59C9C00B5949400AD949400AD949400AD94
      9400F7F7F7008C5A1000BDC6C600EFF7F700DEDEDE00BDBDBD00BDBDBD008484
      8400ADA5A50084848400ADA5A50084848400ADA5A50084848400ADA5A5008484
      8400BDBDBD00BDBDBD00BDBDBD00BDBDBD00BDBDBD00BDBDBD00BDBDBD00BDBD
      BD00BDBDBD00BDBDBD00BDBDBD00319C0000319C0000319C0000BDBDBD00BDBD
      BD006363630031313100313131003131310000000000FFFFFF00E7E7E700E7E7
      E700E7E7E700E7E7E700DEDEDE00DEDEDE00DEDEDE00DEDEDE00DEDEDE00DEDE
      DE00DEDEDE00DEDEDE00DEDEDE00DEDEDE00DEDEDE00DEDEDE00DEDEDE00DEDE
      DE00DEDEDE00DEDEDE00DEDEDE00DEDEDE00DEDEDE00DEDEDE00DEDEDE00DEDE
      DE00E7E7E7006363630031313100313131000000000000000000000000007384
      8400EFEFEF000000000000000000E7E7E700C6C6C600BDBDBD00FFEFE7002973
      AD004ADEFF0021ADF70018A5EF0063C6F700ADDEFF00109CEF001094EF0018A5
      F7000073BD00F7DEC600DED6D600E7E7DE000000000000000000000000000000
      0000848C8C00C6C6CE00000000000000000000000000EFF7F700BDC6C6008C5A
      1000EFE7D6009C7B7B00521818005A2118005A212100632121006B2921007329
      29007B3129008C313100943939009C3939009C393900943939008C3931008431
      3100732929006B292100632121005A2121005A2121005A2118005A2118005218
      1800E7D6DE00945A1000B5C6C600EFF7F700DEDEDE00BDBDBD00BDBDBD00ADA5
      A500EFEFEF00ADA5A500EFEFEF00ADA5A500EFEFEF00ADA5A500EFEFEF00ADA5
      A500BDBDBD00BDBDBD00BDBDBD00BDBDBD00BDBDBD00BDBDBD00BDBDBD00BDBD
      BD00BDBDBD00BDBDBD00BDBDBD005AFF29005AFF2900319C0000BDBDBD00BDBD
      BD00636363003131310031313100313131000000000000000000FFFFFF00FFFF
      FF00E7E7E700E7E7E700DEDEDE00DEDEDE00DEDEDE00DEDEDE00DEDEDE00DEDE
      DE00DEDEDE00DEDEDE00DEDEDE00DEDEDE00DEDEDE00DEDEDE00DEDEDE00DEDE
      DE00DEDEDE00DEDEDE00DEDEDE00DEDEDE00DEDEDE00DEDEDE00DEDEDE00DEDE
      DE00DEDEDE00B5B5B50031313100313131000000000000000000000000000000
      0000737B8400738484007B848400949C9C00B5B5B500636B6B00F7E7E700297B
      B5004ADEFF0021A5F700189CF70063C6F700ADDEFF0010A5EF00108CEF0018A5
      F7000073BD00E7DED60052636300949C9C006B737B00848C8C00B5BDBD007B84
      8400DEDEDE0000000000000000000000000000000000F7F7F700BDCECE008C5A
      1000EFE7D6009C7B7B005A2118005A2121005A212100632121006B2921007329
      29007B31310084313100943939009439390094393900943939008C3931008431
      3100733129006B29290063292100632121005A2121005A2121005A2121005A18
      1800E7DEDE0094631000BDCECE00F7F7F700DEDEDE00BDBDBD00BDBDBD00BDBD
      BD00BDBDBD00BDBDBD00BDBDBD00BDBDBD00BDBDBD00BDBDBD00BDBDBD00BDBD
      BD00BDBDBD00BDBDBD00BDBDBD00BDBDBD00BDBDBD00BDBDBD00BDBDBD00BDBD
      BD00BDBDBD00BDBDBD00BDBDBD00BDBDBD00BDBDBD00BDBDBD00BDBDBD00BDBD
      BD00636363003131310031313100313131000000000000000000000000000000
      0000FFFFFF00FFFFFF00DEDEDE00DEDEDE00DEDEDE00DEDEDE00DEDEDE00DEDE
      DE00DEDEDE00DEDEDE00DEDEDE00DEDEDE00DEDEDE00DEDEDE00DEDEDE00DEDE
      DE00DEDEDE00DEDEDE00DEDEDE00DEDEDE00DEDEDE00DEDEDE00DEDEDE00DEDE
      DE00DEDEDE00E7E7E7005A5A5A00313131000000000000000000000000000000
      000000000000000000000000000000000000BDBDBD00DEDEDE00000000003184
      B5004ADEFF00189CF700109CF70063C6F700ADDEFF0010A5EF00088CEF00109C
      F7000073BD00FFFFDE00ADADAD00EFEFEF000000000000000000DEDEDE00F7F7
      F7000000000000000000000000000000000000000000F7F7F700D6DEDE00945A
      1000EFE7D6008C63630052181800521818005A1818005A211800632121006B21
      2100732921007B292900843129008C3131008C31310084313100842929007329
      29006B212100632121005A2118005A1818005A1818005A181800521818005218
      1800E7D6DE0094631000CED6D600F7F7F700DEDEDE00C6C6C600C6C6C600C6C6
      C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6
      C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6
      C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6
      C600BDBDBD003131310031313100313131000000000000000000000000000000
      00000000000000000000F7F7F700FFFFFF00F7F7F700F7F7F700F7F7F700F7F7
      F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7
      F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7
      F700F7F7F700F7F7F700B5B5B500313131000000000000000000000000000000
      000000000000000000000000000000000000DEDEDE00737B7B00B5ADAD002173
      AD0042DEFF001094F7001094F7005AC6F700A5D6FF00089CEF000884EF00109C
      F7000073BD00BDBDB500848C8C00F7F7F7000000000000000000000000000000
      00000000000000000000000000000000000000000000FFFFFF00E7EFEF00946B
      2100CEB594000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000F7E7DE0094631000E7EFEF00FFFFFF0000000000DEDEDE00DEDEDE00DEDE
      DE00DEDEDE00DEDEDE00DEDEDE00DEDEDE00DEDEDE00DEDEDE00DEDEDE00DEDE
      DE00DEDEDE00DEDEDE00DEDEDE00DEDEDE00DEDEDE00DEDEDE00DEDEDE00DEDE
      DE00DEDEDE00DEDEDE00DEDEDE00DEDEDE00DEDEDE00DEDEDE00DEDEDE00DEDE
      DE00DEDEDE006363630031313100313131000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000BDC6C6000863
      9C0039CEFF000884F700319CF700B5E7FF00DEEFFF004ABDF700007BEF001094
      F700007BBD009CA5A500F7F7F700000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000FFFFFF00D6D6
      C600946B29008C5A10008C5A10008C5A08008C5A08008C5A0800945A08009463
      08009C6308009C6B0800A5730800AD731000AD731000AD731000A56B08009C63
      080094630800945A08008C5A08008C5A08008C5A08008C5A10008C5A10008C5A
      100094631800C6B59400FFFFFF0000000000000000000000000000000000DEDE
      DE00DEDEDE00DEDEDE00DEDEDE00DEDEDE00DEDEDE00DEDEDE00DEDEDE00DEDE
      DE00DEDEDE00DEDEDE00DEDEDE00DEDEDE00DEDEDE00DEDEDE00DEDEDE00DEDE
      DE00DEDEDE00DEDEDE00DEDEDE00DEDEDE00DEDEDE00DEDEDE00DEDEDE00DEDE
      DE00DEDEDE00BDBDBD0031313100313131000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000E7E7E7000863
      9C0039CEFF000084F7007BBDFF00CEEFFF00E7F7FF00B5DEFF00087BF7000894
      F700007BC600B5B5B50000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000FFFFFF00FFFFFF00FFFFFF00F7FFFF00F7FFF700F7F7F700F7F7
      F700F7F7F700EFF7F700EFF7F700EFF7F700EFF7F700EFF7F700EFF7F700F7F7
      F700F7F7F700F7F7F700F7FFF700F7FFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF000000000000000000000000000000000000000000000000000000
      000000000000DEDEDE00DEDEDE00DEDEDE00DEDEDE00DEDEDE00DEDEDE00DEDE
      DE00DEDEDE00DEDEDE00DEDEDE00DEDEDE00DEDEDE00DEDEDE00DEDEDE00DEDE
      DE00DEDEDE00DEDEDE00DEDEDE00DEDEDE00DEDEDE00DEDEDE00DEDEDE00DEDE
      DE00DEDEDE00DEDEDE0063636300313131000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000DEDEDE000863
      9C008CE7FF00ADE7FF00C6F7FF00E7FFFF00E7FFFF00EFFFFF00ADEFFF009CDE
      FF000073C600B5B5B50000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000EFEFEF00EFEFEF00EFEFEF00EFEFEF00EFEF
      EF00EFEFEF00EFEFEF00EFEFEF00EFEFEF00EFEFEF00EFEFEF00EFEFEF00EFEF
      EF00EFEFEF00EFEFEF00EFEFEF00EFEFEF00EFEFEF00EFEFEF00EFEFEF00EFEF
      EF00EFEFEF00EFEFEF00BDBDBD00313131000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000EFEFEF000863
      9C00B5FFFF00A5F7FF00ADF7FF00D6F7FF00D6FFFF00B5F7FF00A5F7FF00ADFF
      FF00218CC600ADB5B50000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000003163
      84007BD6F700ADF7FF00A5F7FF00A5F7FF00A5F7FF00A5F7FF00ADF7FF0094E7
      FF002973A500EFEFEF0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000DEDE
      DE0031638400187BB5004AADDE004AADDE004AADDE004AADDE00298CC6002163
      8C00A5B5B5000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000C6CECE00949C9C0063849C0063849C007B8C9C00BDBDBD00F7F7
      F700000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000F7FFF700ADDE
      AD005ABD5A0031AD3100009C0000009C0000009C0000009C000031AD310052BD
      5200ADDEAD00F7FFF70000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000FFFFFF00FFFFFF00F7F7F700F7F7F700FFFFFF00FFFFFF000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FFFFFF00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000F7FFF7007BCE7B00089C080042AD
      420094C69400B5D6B500DEDEDE00E7E7E700E7E7E700E7E7E700B5D6B5009CCE
      9C004AB54A00009C00006BC66B00EFF7EF000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000FFFFFF000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000FFFF
      FF00EFF7F700E7EFEF00D6E7DE00CEDEDE00CEDEDE00D6E7DE00E7EFEF00EFF7
      F700FFFFFF000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000F7F7F700E7EFEF00E7EFEF00DEEFEF00DEEFEF00E7EFEF00EFF7F700FFFF
      FF00000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000009CDE9C0010A510006BBD6B00D6DED600DEDE
      DE00E7E7E700E7E7E700E7E7E700EFEFEF00EFEFEF00EFEFEF00E7E7E700E7E7
      E700E7E7E700E7E7E7006BBD6B00089C080094D6940000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000FFFFFF00EFF7
      F700E7EFEF00E7EFEF00F7F7F700000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FFFFFF00EFF7F700DEE7
      E700BDCECE00A5BDB5008CADA50084A59C0084A59C008CADA500A5BDB500BDCE
      CE00DEE7E700EFF7F700FFFFFF00000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000F7F7
      F700DEC6B500EF845200E7845200DE845200DE845200E7845200EF946B00EFF7
      F700000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000063BD630052B55200ADCEAD00DEDEDE00E7E7E700EFEF
      EF00EFF7EF00E7EFE700DEEFDE00D6EFD600D6EFD600D6EFD600E7EFE700F7F7
      F700EFEFEF00E7E7E700EFEFEF00C6DEC60063BD630052BD5200F7FFF7000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000EFF7F700CEDE
      DE007B9C5A00A5BDA500DEE7E700F7FFF7000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000FFFFFF00EFEFEF00C6D6D6009CB5
      B50073948C00397B8400186B9400106B9400106B9400186B9400397B84007394
      8C009CB5B500C6D6D600EFEFEF00FFFFFF000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000E7EF
      EF00E78C5A00FFB50000FFB50000FFB50000FFB50000FFAD0000FF7B4200DEE7
      E700FFFFFF000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000052BD520063B56300DEDEDE00E7E7E700EFEFEF00EFF7EF00D6EF
      D600B5E7B5007BCE7B0063C6630052BD52005ABD5A005ABD5A007BCE7B009CD6
      9C00C6E7C600F7F7F700EFEFEF00EFEFEF00EFEFEF006BBD6B0042B542000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000F7F7F700D6DEDE007394
      5A0052A500004A7B0000B5CEC600E7EFEF00FFFFFF0000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000EFF7F700C6D6D6008CADA500397B
      8C00187BB5004AADEF00BDE7FF00F7FFFF00F7FFFF00CEEFFF0052B5EF00107B
      BD00397B8C008CADA500C6D6CE00EFEFEF000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000E7EF
      EF00E7845200FF9C1800FF9C0000FF9C0000FF9C0000FF9C0000FF7B4200D6E7
      E700FFFFFF000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00007BCE7B005AB55A00DEDEDE00E7E7E700EFEFEF00DEEFDE00BDE7BD0052BD
      5200089C0800009C0000009C0000009C0000009C0000009C0000009C000018A5
      18004AB54A0084CE8400DEEFDE00F7F7F700EFEFEF00EFEFEF0063BD63006BC6
      6B00000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000F7FFFF00DEE7E7009CB59C005284
      0000EFFFDE0042D600005A7B2100CEDEDE00EFF7F70000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000F7F7F700D6DEDE0094ADA50029739400219C
      E70052CEFF0039CEFF0018C6FF0000ADFF0000ADFF0029C6FF0052D6FF0073DE
      FF001894DE0018739C008CADA500CEDED600F7F7F70000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000DEEF
      EF00DE845200FFA52900FF9C0000FF9C0000FF9C0000FF9C0000FF7B4200D6E7
      E700FFFFFF000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000B5E7
      B50042AD4200CEDECE00E7E7E700EFF7EF00D6EFD6006BC66B00089C0800009C
      0000009C0000009C0000009C0000009C0000009C0000009C080000A5080008A5
      080008A5080029AD31006BC66B00C6E7C600F7F7F700EFEFEF00EFEFEF0052BD
      5200A5DEA5000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000FFFFFF00EFEFEF00C6D6D600527308004ADE
      000042E7000042F700004AAD0000849C7B00DEE7E700F7F7F700000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000E7EFEF00ADC6BD00397B9C001094E70031C6
      FF0000B5FF000094E7000073C600006BC600006BC600006BC600008CE70008B5
      FF0052D6FF000894E700297B9C00A5BDB500DEEFE700FFFFFF00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000E7EF
      EF00DE845200FFBD5200FF9C0000FF9C0000FF9C0000FFA50000FF7B4200D6E7
      E700FFFFFF000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000000000000021A5
      21009CCE9C00DEDEDE00EFEFEF00D6EFD6006BC66B00009C0000009C0000009C
      0000009C0000009C0000009C000000A5080008A5080008A5080008A5100008A5
      100008A5100008A5100021AD21005ABD5A00CEEFCE00F7F7F700EFEFEF00BDDE
      BD0018A51800F7FFF70000000000000000000000000000000000000000000000
      0000000000000000000000000000F7F7F700D6DEDE006B8C4A0052BD00004AEF
      00005AB500004ADE000042EF00004A7B0000B5C6C600E7EFEF00FFFFFF000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000F7FFF700D6DEDE00739CA5000084DE0021C6FF0000B5
      FF00007BCE001873B50084849400A5848C00D6ADAD00A59CB500317BBD000073
      CE0008B5FF0029C6FF000084DE00739C9C00CEDED600F7F7F700000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000E7EF
      EF00E7845200FFDE9400FFD67300FFF7C600FFE79400FFBD1800FF7B4200DEE7
      E700FFFFFF000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000094D694005AB5
      5A00DEDEDE00E7E7E700E7EFE70073C67300009C0000009C0000009C0000009C
      0000009C00007BCE7B0029AD290008A5080008A5100008A5100008AD100010AD
      180010AD180010AD180010AD180029B529005ABD5A00EFF7EF00F7F7F700F7F7
      F7006BC66B0084CE840000000000000000000000000000000000000000000000
      00000000000000000000F7FFFF00DEE7E70094AD8C00528C000042F700005ABD
      00005AB500005AB5000042EF00004AD600005A7B2100CEDEDE00EFF7F7000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000F7F7F700BDCECE00187BB50000A5EF0008B5F700008C
      D6004273A500C68C8400E7CEC600FFF7EF00FFF7F700FFDEDE00F7BDB5005284
      B500008CD60021BDFF0000A5F700187BAD00BDCEC600EFF7F700000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000EFF7
      F700DEA57B00FF7B3900F77B3900EF7B3900EF7B4200F77B4200FF7B4200DEEF
      EF00000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000029AD2900BDD6
      BD00E7E7E700EFF7EF00C6E7C60021A52100009C0000009C0000009C0000009C
      000084CE840000000000E7F7E70029AD290008A5100010AD180010AD180010AD
      180010AD210010AD210010B5210010B5210029B5310094D69400F7F7F700F7F7
      F700D6EFD60018A5180000000000000000000000000000000000000000000000
      000000000000FFFFFF00E7EFEF00B5C6C6004A6B000039EF00004ACE000052B5
      00005AB500005AB500005AC6000042F700004AAD000084A57B00D6E7E700F7F7
      F700000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000EFEFEF00B5C6BD00007BCE0000A5E70000A5E7000863
      A500B58C8400EFE7DE0000000000000000000000000000000000FFFFF700FFB5
      AD00106BAD0000A5E70000A5E700007BD600ADC6BD00E7EFEF00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000F7F7
      F700DEE7E700B5BDAD00A5AD9C009CA59C009CA59C00A5AD9C00BDBDB500E7EF
      EF00000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000DEF7DE0018A51800E7E7
      E700E7E7E700DEEFDE006BC66B00009C0000009C0000009C0000009C00008CD6
      8C00000000000000000000000000E7F7E70029B5310010AD180018B5210018B5
      210018B5290018B5290018B5290018B5290018B5290042B54200EFF7EF00F7F7
      F700F7F7F70031AD3100CEEFCE00000000000000000000000000000000000000
      000000000000EFF7F700CEDEDE006B84420039CE000039DE080042BD08004ABD
      000073C6310052B500005AB5000052D6000042EF00004A7B0000B5C6C600E7EF
      EF00FFFFFF000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000E7EFEF0084B5BD00088CD60018A5DE0010A5DE005273
      9400C6A59C00DED6D600CEC6C600CEC6C600D6CECE00D6CED600E7DEDE00DEBD
      B5007B8CAD00089CD60018A5DE00088CD6007BADBD00E7EFEF00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000F7FF
      F700D6CEBD00FF843900FF8C3100F7843100F7843100FF8C3100FF7B4200DEE7
      E700FFFFFF000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000084CE84006BBD6B00E7E7
      E700EFEFEF00C6E7C60029AD2900009C0000009C0000009C00008CD68C000000
      000000000000000000000000000000000000E7F7E70031B5310010AD210018BD
      290021BD310021BD310021BD310021BD310021BD310029B53100B5DEB500F7F7
      F700F7F7F70084CE84007BCE7B00000000000000000000000000000000000000
      0000F7F7F700D6E7E7008C9C7B0042A5000029EF000039C6100039C6080052C6
      2100A5DE8C006BC6290052B500005AB500004AEF00004AD600005A7B2100CEDE
      DE00EFF7F7000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000EFEFEF007BADBD00189CDE0042BDE70039BDEF006B7B
      9C00C6ADAD00CEBDC6008C7B7B008C7B84008C8484009C949400DED6D600D6BD
      B5007B8CA50031B5DE0042BDE700189CDE007BADBD00EFEFEF00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000F7F7
      F700CEBDAD00FF9C2100FFD60000FFCE0000FFCE0000FFD60000F77B4200C6D6
      CE00EFF7F7000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000052BD520094CE9400E7E7
      E700F7F7F700B5DEB500009C0800009C0000009C000094D69400000000000000
      00000000000000000000000000000000000000000000E7F7E70031B5390018B5
      290021BD390021BD390021C6390021C6390021C6390029B5310084CE8400F7F7
      F700F7F7F700B5DEB5004AB54A0000000000000000000000000000000000FFFF
      FF00E7EFEF00B5C6BD004A7B000018EF000029D6180031CE180031C608007BDE
      63009CE78400A5E78C0052BD080052B500005ABD000042F700004AAD000084A5
      7B00D6E7E700F7F7F70000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000EFF7F70084B5C600219CDE0063D6EF0063D6F7007384
      9C00C6ADA500DED6D6008C848400847B7B00847B7B009C949400D6CECE00C6A5
      A50073849C0063D6F70063D6EF0029A5DE0084B5C600EFF7F700000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000F7F7
      F700CEBDAD00FF8C3100FFBD0000FFB50000FFB50000FFBD0000F78C2900D68C
      6B00D6E7E700F7F7F70000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000039AD3900ADD6AD00E7E7
      E700EFF7EF0094D69400009C0000009C00006BC66B0000000000000000000000
      000000000000BDE7BD00EFF7EF00000000000000000000000000E7F7E70039BD
      420021BD310029C6420029C6420029C6420029C6420029BD390063C66300FFFF
      FF00F7F7F700CEE7CE0029AD290000000000000000000000000000000000EFF7
      F700CED6D6005A73210018DE000018DE210021D6210021CE18004AD639007BDE
      630094DE7B00B5EF9C008CD663004ABD000052B5000052CE000042EF00004A7B
      0000B5C6C600E7EFEF00FFFFFF00000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000F7FFFF00D6DEDE00188CD6007BDEF7008CE7F70073B5
      CE00BD8C8C00FFFFFF00EFEFEF00C6C6C600C6C6C600F7F7F700F7EFEF00C694
      8C0073B5CE008CE7F7007BDEF700188CD600BDD6D600F7F7F700000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000F7FF
      F700CECEC600FF7B4200FFC61000FFBD0000FFB50000FFBD0000FFD60000F78C
      3100DE845200CED6D600EFF7F700000000000000000000000000000000000000
      0000000000000000000000000000000000000000000029AD2900BDD6BD00E7E7
      E700EFF7EF008CD68C00009C000008A5080008A51000BDE7BD00000000000000
      0000BDE7BD0010AD180039B54200EFF7EF00000000000000000000000000E7F7
      E70039BD420021BD390031CE4A0031CE4A0031CE4A0029C642005ABD5A00FFFF
      FF00F7F7F700DEEFDE0018A51800000000000000000000000000FFFFFF00E7EF
      EF007B9C5A0021B5000000EF180010DE210018D6180021D6180063E75A005A94
      21005A841000ADEF9C00C6EFBD005AC621004ABD000052B500004AE7000042D6
      00005A7B2100CEDEDE00EFF7F700000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000E7EFEF00187BC6008CE7FF00ADEFFF008CE7
      FF00949CA500C69C9C00F7F7F7000000000000000000F7F7EF00C69C9400AD9C
      9C0084E7F700A5EFFF008CE7FF00107BC600E7EFE700FFFFFF00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000FFFF
      FF00DEEFE700EF7B4200FFBD3100FFCE2100FFBD0000FFBD0000FFC60000FFDE
      0000FFA52100EF7B4200CEC6BD00EFF7F7000000000000000000000000000000
      0000000000000000000000000000000000000000000031AD3100BDD6BD00E7E7
      E700EFF7EF008CD68C0000A5080008A5080008A5100008A51000B5E7B500BDE7
      BD0010AD180018B5290018B5290039BD4200EFFFEF0000000000000000000000
      0000E7F7E70039BD420029C6420039D6520039D6520029C6420063C66300FFFF
      FF00F7F7F700D6EFD60021A5210000000000000000000000000000000000E7EF
      EF005A8C10006BFF840084F79C0021E7390008DE180031E739005AC63900ADBD
      A5008CA56B007BAD4A00C6F7BD00BDEFAD0039BD00004ABD000052BD000042EF
      00004AAD000084A57B00D6E7E700F7F7F7000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000F7F7F70073ADCE004AB5E700BDF7FF00ADF7
      FF0094EFFF00ADB5BD00B5847B00CEA5A500CEA5A500B5848400ADB5BD009CEF
      F700B5F7FF00B5F7FF004AB5E70073ADCE00F7F7F70000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000EFF7F700CEB5A500F77B4200FFD67300FFDE6300FFC60000FFBD0000FFBD
      0000FFCE0000FFAD1000F77B4200CED6D600F7F7F70000000000000000000000
      0000000000000000000000000000000000000000000042B54200A5CEA500E7E7
      E700F7F7F7009CD69C0008A5100008A5100010AD180010AD180010A5180010AD
      180018B5290021BD310029C6390021BD310042BD4A00F7FFF700000000000000
      000000000000E7F7E70042C64A0029CE420039D65A0029BD39007BCE7B00FFFF
      FF00F7F7F700C6E7C60031AD310000000000000000000000000000000000F7F7
      F7006384180073BD5200ADFFBD00C6FFCE0063F7730039DE39007B9C5200EFF7
      F700EFF7F70063842900ADDE9400DEFFD60084DE630039BD00004ABD08004ACE
      000042EF00004A7B0000B5C6C600E7EFEF00FFFFFF0000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000FFFFFF00DEE7E700187BC60084DEF700D6FF
      FF00BDF7FF009CF7FF00A5EFFF00A5DEE700A5DEE700A5E7F700A5F7FF00C6FF
      FF00CEFFFF008CE7FF00187BBD00DEE7E700FFFFFF0000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000F7FFFF00F7F7F700EFF7F700EFF7
      F700E7EFEF00DEE7E700C6AD9400EF7B4200FFCE9C00FFE76B00FFC60000FFBD
      0000FFBD0000FFBD0000FF9C1800E7845200E7EFEF00FFFFFF00000000000000
      000000000000000000000000000000000000000000006BC66B0084C68400E7E7
      E700EFEFEF00ADDEAD0029B5310008A5100010AD180010AD210018B5290018BD
      290021BD310029C6390029C6420031CE4A0021C6390042C64A00F7FFF7000000
      00000000000000000000E7F7E70031BD390042DE630021B52900C6E7C600FFFF
      FF00FFFFFF009CD69C005ABD5A00000000000000000000000000000000000000
      0000F7FFFF00A5B584005A7B1000BDDEAD00000000005A941800DEE7DE000000
      000000000000DEE7DE00527B0800CEF7C600E7FFE7004ACE210039C608004ABD
      080042DE000042D600005A7B2100CEDEDE00EFF7F70000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000E7EFEF008CA5A500107BBD0084D6
      F700E7FFFF00E7FFFF00CEFFFF00BDFFFF00BDFFFF00CEFFFF00DEFFFF00DEFF
      FF0084DEF700107BBD008CA5A500E7EFEF000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000FFFFFF00EFF7F700D6DEDE00CEBDAD00CEAD9400D69C
      7B00D69C7B00D6C6B500DEE7E700C6C6B500E77B4A00FFBD6300FFCE0800FFC6
      0000FFC60000FFBD0000FFC60000FF7B4200CECEC600F7F7F700000000000000
      00000000000000000000000000000000000000000000A5DEA50052B55200E7E7
      E700EFEFEF00CEEFCE0052BD5A0010AD180010AD180018B5210018B5290021BD
      310021C6390029C6420031CE4A0031CE4A0039D6520029C642004AC65200F7FF
      F70000000000000000007BD6840031D6520042DE630021AD2100FFFFFF00FFFF
      FF00FFFFFF0063C6630094D69400000000000000000000000000000000000000
      00000000000000000000F7F7F700ADBD8C0073943100ADBD9400FFFFFF000000
      000000000000FFFFFF00B5C6A500739C3100EFFFF700B5EFA50031C6000039C6
      08004ABD080039EF00004AAD000084A57B00D6E7E700F7F7F700000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000E7EFEF009CA5A500C6BDBD004294
      CE0039A5DE00BDE7FF00000000000000000000000000F7FFFF00B5E7FF0031A5
      DE003994D600A59494009CA5A500E7EFEF000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000EFF7F700DEAD8C00FF8C3900FF943100FF9C2900FFAD
      1800FFAD2100EF7B4A00DEE7E700E7EFEF00C6C6C600EF734200FFCE0800FFC6
      0000FFC60000FFC60000FFC60000FF8C3100CEB5A500F7F7F700000000000000
      00000000000000000000000000000000000000000000EFF7EF00009C0000E7E7
      E700E7E7E700F7F7F7008CD68C0029B5310010AD210018B5290021BD310021BD
      310029C6390029CE420031CE4A0039D6520039D65A0042DE630031CE4A004AC6
      5A00F7FFF7007BD6840031D652004AE7730029BD390094D69400FFFFFF00FFFF
      FF00FFFFFF0018A51800E7F7E700000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000F7F7F7007B9C5A00B5CE9400EFFFF70063D64A0031C6
      080042C6080042C6080039EF00004A840000B5C6C600E7EFEF00FFFFFF000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000EFEFEF009CADA500D6C6C600D6CE
      C6006B7B8400428CBD002984CE002194DE002194DE00187BCE00398CBD006B7B
      8400DED6CE00AD9C9C009CA5A500E7EFEF000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000EFF7F700DE947300FFC60800FFDE0000FFDE0000FFD6
      0000FFD60000FF7B4200CEDEDE00E7EFEF00D6DEDE00D6845A00FFBD1000FFCE
      0000FFC60000FFC60000FFC60000FF9C1800D69C7B00EFF7F700000000000000
      000000000000000000000000000000000000000000000000000052BD520094CE
      9400EFEFEF00EFEFEF00D6EFD60052BD520018B5290018B5290021BD310021C6
      390029C6420031CE4A0031D6520039D65A0042DE630042DE6B004AE76B0039D6
      520031C6420039D65A0052EF7B0031CE4A0031AD3100F7FFF700FFFFFF00FFFF
      FF00B5DEB50039B5390000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000EFF7F70063842100CEEFC600CEFFCE0031CE
      100031C6080042C6100039D6080039DE00005A732100CEDEDE00EFF7F7000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000EFF7F700A5ADAD00D6CECE00D6CE
      C600847B7B00ADC6C600E7EFEF00FFFFFF0000000000EFF7EF00B5CEC600847B
      7B00E7DED600AD9C9C009CADA500EFEFEF000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000EFF7F700D6A58C00FF942100FFCE0800FFC60000FFC6
      0000FFCE0000F7942900C69C8400CEDEDE00B5CEC600E7734A00FFC60800FFCE
      0000FFC60000FFC60000FFC60000FF942900CEB59C00EFF7F700000000000000
      0000000000000000000000000000000000000000000000000000CEEFCE0031AD
      3100EFEFEF00EFEFEF00F7F7F700B5DEB50042BD4A0021BD310021BD310029C6
      390029CE420031CE4A0039D6520039DE5A0042DE63004AE76B004AE7730052EF
      7B0052EF7B0052EF840039D65A0018A51800D6EFD600FFFFFF00FFFFFF00FFFF
      FF004AB54A00B5E7B50000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000CEDECE0063841800DEFFD6008CE7
      7B0029CE080039C6100042C6100039E7000042B500008CA57B00DEE7E700F7FF
      FF00000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000F7F7F700C6D6D600C6B5B500D6CE
      CE009C8C8C0094B5AD00D6E7DE00F7F7F700F7FFFF00DEE7E700A5BDB500847B
      7B00F7F7F700BDADAD00A5B5AD00F7F7F7000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000F7F7F700CECEC600FF7B3900FFCE1000FFC60000FFC6
      0000FFCE0000FFC60800F7843900DE7B5200E7734A00F79C2900FFD60000FFCE
      0000FFC60000FFC60000FFCE0800FF843900CEC6BD00F7F7F700000000000000
      0000000000000000000000000000000000000000000000000000000000005ABD
      5A0073C67300EFEFEF00EFEFEF00F7F7F700A5DEA50042BD420029BD390029C6
      420031CE4A0031CE520039D65A0042DE630042DE6B004AE7730052EF730052EF
      7B0052F7840039CE4A0021A52100C6E7C600FFFFFF00FFFFFF00FFFFFF0084CE
      84004AB54A000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000F7FFFF00A5BD94008CAD5200D6FF
      DE0042D6310029CE100031C6100039C6100031F700005A841000C6D6CE00F7F7
      F700000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000F7FFFF00D6E7DE00B5A5A500F7F7
      F700A58C8C006B8C8400A5BDBD00CEDEDE00D6DEDE00B5C6C60073948C00AD9C
      9C0000000000B5A5A500CED6D600F7FFFF000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000FFFFFF00E7EFEF00D68C6300FFA52100FFD63100FFCE
      0000FFCE0000FFD60000FFDE0000FFC60800FFCE0000FFD60000FFCE0000FFCE
      0000FFCE0000FFD63900FFB50800EF7B4200DEE7E700FFFFFF00000000000000
      000000000000000000000000000000000000000000000000000000000000EFF7
      EF0018A518008CCE8C00EFEFEF00EFEFEF00F7F7F700BDE7BD0052BD520031BD
      420031C6420031D6520039D65A0042DE63004AE76B004AE7730052EF7B0042D6
      5A0021B531004AB54A00DEF7DE00FFFFFF00FFFFFF00FFFFFF00A5DEA50010A5
      1000E7F7E7000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000F7F7F70073944A00A5D6
      8C00ADF7AD0021CE100029CE100031CE100073E75200A5EF84006B8C3100F7F7
      F700000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000EFEFEF00949494000000
      0000AD9494007B7B7B00638C840084A5A5008CADA5006B948C006B736B00DED6
      DE0000000000948C8C00E7EFEF00000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000F7F7F700CECEC600F77B4200FFC61800FFDE
      5200FFCE0000FFCE0000FFD60000FFD60000FFD60000FFD60000FFCE0000FFCE
      0800FFE76300FFCE1800FF843900CEB59C00EFF7F70000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000D6EFD600089C0800A5D6A500EFEFEF00EFEFEF00F7F7F700EFF7EF00A5DE
      A5005ABD5A0029B5310029B5310031BD390029B5310021B5290018A518005ABD
      5A00BDE7BD00FFFFFF00FFFFFF00FFFFFF00FFFFFF00B5E7B500009C0000C6E7
      C600000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000DEE7E7005A7B
      1000B5EFB50063E7630021D6100029CE18008CE773006B9C2900A5BD9400FFFF
      FF00000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000F7FFFF00C6CEC600D6CE
      CE00E7DEE7009C8C8C00737B73004A736B004A736B006B736B00C6B5B500FFF7
      F700DED6D600B5B5B500F7F7F700000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000EFF7F700CEC6B500F77B3900FFBD
      3900FFEF7B00FFE76300FFDE2100FFD60800FFD61000FFDE4A00FFEF8C00FFF7
      9C00FFCE3900FF8C3100D6947300E7EFEF00FFFFFF0000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000BDE7BD00089C08008CCE8C00EFEFEF00F7F7F700F7F7F700F7F7
      F700F7F7F700E7F7E700D6EFD600ADDEAD00BDE7BD00CEEFCE00F7FFF700FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF009CD69C00089C0800ADDEAD000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000FFFFFF00BDCE
      B50063841800ADFFB50029DE290039DE310063BD39007B944A00F7F7F7000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000F7F7F700A59C
      9C00F7F7F700DED6D600A59494009C8C8C00AD949C00B5A5A500E7DEDE000000
      0000A59C9C00EFF7F70000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000FFFFFF00EFEFEF00CEC6BD00E77B
      4A00FF943900FFC68400FFF7C600FFFFEF000000000000000000FFD69C00FF9C
      3100F7733900CEAD9400E7EFEF00F7FFFF000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000D6EFD60021A5210073C67300EFEFEF00F7F7F700F7F7
      F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7F700FFFFFF00F7F7F700FFFF
      FF00FFFFFF00FFFFFF00F7FFF7007BCE7B0018A51800CEEFCE00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000F7FF
      FF009CAD7B0084B55A007BF78C0039D629006B842900EFF7F700000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000F7F7
      F700ADA5A500F7EFEF0000000000000000000000000000000000F7EFEF00A59C
      9C00E7EFEF000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000EFF7F700DEE7
      E700D6AD9400DE8C6300DE7B4A00F7733100FF733100DE7B4A00DE845200D6A5
      8400D6DED600EFEFEF00F7FFFF00000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000F7FFF70073C67300089C080084CE8400D6EF
      D600F7F7F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7F700FFFFFF00FFFF
      FF00DEEFDE008CCE8C00009C00006BC66B00EFF7EF0000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000F7F7F7006B84290073C65200527B0800E7EFE70000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000FFFFFF00CECECE00ADA5A500B5ADAD00B5ADAD00B5ADA500C6C6C600FFFF
      FF00000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000F7FF
      FF00EFF7F700E7EFEF00DEEFEF00DEE7E700DEE7E700DEE7E700E7EFEF00EFF7
      F700F7FFF7000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000E7F7E70073C6730018A5
      180029AD290063BD63007BC67B0094D6940094D694007BCE7B0063BD630031AD
      310018A518006BC66B00DEF7DE00000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000EFEFEF009CAD7300DEE7D6000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000FFFFFF00FFFFFF00FFFFFF00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000D6EFD6009CD69C0084CE840063C6630063C663007BCE7B009CD69C00CEEF
      CE00000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000F7F7EF00DED6D600BDB5B500A59494008C7B7300846B
      63007B5A52007B5242007B5242007B4A39007B4A39007B5242007B5242007B5A
      5200846B63008C7B7300A59C9400C6BDB500DEDED600E7DED6009C8C8400947B
      63008C7B6300ADA59C0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000E7E7E700CECECE009C9C9C00A5A5A500CECECE00E7E7E7000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000DED6
      D600948484007B5242008442210094391000AD4A1800B55A2100BD633100C66B
      3900CE7B4A00CE845200D6845A00D68C5A00D68C5A00D6845A00CE845200CE7B
      4A00C6734200BD633100BD5A2900AD4A180073311000AD7B4A00F7E7D600FFFF
      F700FFF7EF00EFCEAD00A58C7300000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FFFFFF00F7F7F700F7F7
      F700FFFFFF000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000EFEFEF00DEDEDE00CECECE00B5B5
      B50094949400848484005A5A5A00215A5A00214A52005A5A5A00848484009494
      9400B5B5B500CECECE00DEDEDE00EFEFEF000000000000000000000000000000
      00000000000000000000000000000000000000000000CEC6C6007B5242009439
      0800AD420800AD4A1000B5522100BD632900BD6B3900C6734200CE7B4A00CE84
      5A00D68C6300D6946B00DE947300DE9C7300DE9C7300DE9C7300DE946B00D68C
      6300D6845A00CE845200BD6B420094521800D69C6300FFE7D600FFEFE700FFF7
      EF00FFEFE700FFE7D600EFB58C00E7DED6000000000000000000000000000000
      000000000000FFFFFF00F7F7F700EFF7EF00E7EFEF00E7EFEF00E7EFEF00E7EF
      EF00E7EFEF00E7EFEF00E7EFEF00E7EFEF00E7EFEF00E7EFEF00E7EFEF00E7EF
      EF00E7EFEF00E7EFEF00E7EFEF00EFEFEF00F7F7F700F7FFFF00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000F7F7F700E7E7E700DEDED600DEDE
      D600E7E7E700F7F7F700FFFFFF00000000000000000000000000000000000000
      0000EFEFEF00DEDEDE00CECECE00B5B5B500A5A5A5008C8C8C007B7B7B007373
      73006B6B6B005252520010393900A5FFFF009CFFFF00102931005A5A5A006B6B
      6B00737373007B7B7B008C8C8C00A5A5A500BDBDBD00CECECE00E7E7E700EFEF
      EF0000000000000000000000000000000000E7D6D60094391000AD390000AD42
      0800AD4A1000B5521800BD5A2100BD6B3100C6734200CE7B4A00D6845A00D68C
      6300DE9C6B00DE9C7B00E7A57B00E7A58400E7A58400E7A57B00DEA57B00DE9C
      7300D6946B00B5734A00AD632100EFC69C00FFDECE00FFDED600FFE7D600FFE7
      D600FFDECE00FFD6BD00FFC6AD00EFCEB5000000000000000000000000000000
      0000F7FFFF00E7EFEF00CEDED600B5C6C600A5BDBD00A5BDB500A5BDB500A5BD
      B500A5BDB500A5BDB500A5BDB500A5BDB500A5BDB500A5BDB500A5BDB500A5BD
      B500A5BDB500A5BDB500A5BDBD00ADC6BD00C6D6CE00DEE7E700F7F7F7000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000FFFFFF00EFEFEF00DED6D600BDBDB5005A6394004A5A
      940063739C00D6D6D600F7F7F700000000000000000000000000DEDEDE00C6C6
      C600B5B5B500A5A5A500949494008C8C8C008484840084848400848484008C8C
      8C006B6B6B001839420073F7FF00BDFFFF00B5FFFF0073F7FF00102931007373
      73008C8C8C008484840084848400848484008C8C8C0094949400A5A5A500B5B5
      B500C6C6C600DEDEDE000000000000000000D6AD9C00AD420000AD420000B54A
      0800B5521000BD5A2100C66B2900C6733900CE7B4A00D6845200D6946300DE9C
      7300E7A57B00E7AD8400DEAD9400D6AD9C00D6AD9C00DEAD9400DEAD8C00DEA5
      7B00A56B4A00C6844200FFDECE00FFF7EF00FFCEB500FFCEBD00FFD6BD00FFCE
      BD00FFCEB500FFC6A500F7BD9400EFCEAD000000000000000000000000000000
      0000E7EFEF00BDCECE0084A59C005A8C84004A7B73004A7B73004A7B73004A7B
      73004A7B73004A7B73004A7B73004A7B73004A7B73004A7B73004A7B73004A7B
      73004A7B73004A7B73004A7B730052847B0073949400A5BDBD00DEE7E700F7FF
      FF000000000000000000000000000000000000000000FFFFFF00F7F7F700F7F7
      F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7
      F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7F700F7F7
      F700F7F7F700F7F7F700E7EFE700CECECE00A5A5A500637BAD00F731EF00FF21
      F700EF4AEF00424AA500EFEFEF00FFFFFF0000000000EFEFEF00DEDEDE00C6C6
      C600BDBDBD00B5B5B500ADADAD00ADADAD00ADADAD00A5A5A500ADADAD008484
      84001839390073F7FF008CF7FF00CEFFFF00CEFFFF008CF7FF006BF7FF001029
      31008C8C8C00ADADAD00A5A5A500ADADAD00ADADAD00ADADAD00B5B5B500BDBD
      BD00CECECE00DEDEDE000000000000000000F7E7E700B5522100B5520000BD5A
      0800BD631800C66B2100CE733100CE7B3900D6844A00C68C6B0094949C0063A5
      C60039B5DE0021C6EF0010CEF70010D6F70010D6F70010CEF70018B5DE002142
      5200945A2100FFE7D600FFF7EF00FFFFF700F7C6AD00F7BDA500F7BDA500F7BD
      9C00F7B59400F7B59400EFA57300F7EFDE00000000000000000000000000F7FF
      FF00D6DEDE0084A59C0063736B008C948C008C8C84008C8C84008C948C008C94
      8C008C948C008C948C0094948C00949C94008C948C008C948C008C948C008C94
      8C008C948C008C948C008C9484008C948C007B847B006B8C8C00BDCECE00EFF7
      F70000000000000000000000000000000000F7F7F700DEEFE700CEDEDE00C6D6
      D600C6D6D600C6D6D600C6D6D600C6D6D600C6D6D600C6D6D600C6D6D600C6D6
      D600C6D6D600C6D6D600C6D6D600C6D6D600C6D6D600C6D6D600C6D6D600C6D6
      D600C6D6D600BDCECE00B5BDB500949494007384B50000000000EFE7E700FF6B
      EF00FF8CFF00845ACE00E7E7E700FFFFFF000000000000000000000000000000
      000000000000EFEFEF00E7E7E700DEDEDE00D6D6D600D6D6D6009C9C9C001839
      42006BF7FF0084F7FF00ADF7FF00B5F7FF00B5F7FF00A5F7FF007BF7FF006BF7
      FF0010293100ADADAD00D6D6D600D6D6D600DEDEDE00E7E7E700EFEFEF000000
      00000000000000000000000000000000000000000000EFEFEF00C68C7B00BD52
      2100C65A1800CE732100CE7B3100A58473004AA5C60010CEF70000EFFF0000F7
      FF0000F7FF0000F7FF0000F7FF0000F7FF0000F7FF0000BDC600083139003931
      2900E7A57300FFF7E700FFFFF70000000000FFE7D600F7AD9400F7AD8C00F7AD
      8C00F7AD8C00F7A58400EFBD8C0000000000000000000000000000000000F7F7
      F700C6D6CE006B7B7300EFF7EF00D6E7DE00CEDED600CEDECE00D6E7D600DEEF
      DE00E7EFE700E7F7E700E7F7EF00EFF7F700EFFFF700F7FFF700EFFFF700EFF7
      F700E7F7EF00E7EFE700DEE7DE00DEE7DE00F7FFF700848C8400A5BDBD00E7EF
      EF0000000000000000000000000000000000DEE7E700ADC6C60084A5A500739C
      9400739494007394940073949400739494007394940073949400739494007394
      9400739494007394940073949400739494007394940073949400739C9400739C
      940073948C00738C84007384730029397B0000000000EFEFE700DED6CE00C6BD
      B500FFBDF700CE8CEF00CECEDE00FFFFFF000000000000000000000000000000
      00000000000000000000000000000000000000000000BDBDBD00184242006BF7
      FF007BF7FF00A5F7FF009CF7FF008CF7FF008CF7FF009CF7FF009CF7FF007BF7
      FF0063F7FF0010313900C6C6C600000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000EFDED600D6A5940084737B0008CEF70000E7FF0000EFFF0000E7FF0000E7
      FF0000E7FF0000E7FF0000DEFF0000DEF70000848C0010212100424242005A52
      4200EFB58400FFF7EF00FFFFFF0000000000FFFFF700FFDECE00F7BD9C00F7AD
      8C00E7945A00EFCEA5000000000000000000000000000000000000000000F7F7
      F700BDCECE0094949400F7FFFF00A5B5A500A5B5A500C6CEC600C6D6C600BDCE
      C600A5C6B50084AD9C00739C8C006B9C8C006B9C8C0073A594008CADA500ADC6
      B500BDD6C600CED6CE00B5BDB5009CAD9C00F7FFF700ADB5AD0094ADA500E7EF
      EF0000000000000000000000000000000000C6D6D6006B634200846B4A007B6B
      4A007B6B4A007B6B4A007B6B4A007B6B4A007B6B4A007B6B4A007B6B4A007B6B
      4A007B6B4A007B6B4A007B6B4A007B6B4A007B6B4A007B6B4A007B6B4A007B6B
      4A007B6B4A007B6B4A00424A63003163B5007394C600D6CECE00C6BDB500C6BD
      B500FFF7F7005A5AB500EFEFEF00000000000000000000000000000000000000
      000000000000000000000000000000000000C6C6C6001842420063F7FF0073F7
      FF009CF7FF0094F7FF0084F7FF0073F7FF0073F7FF0084F7FF0094F7FF0094F7
      FF0073F7FF005AEFFF0010313900CECECE000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000008C94AD0008C6F70018B5EF0031A5CE005A9CB5007394
      AD008C9CB5009CA5BD008C94A50029314200292929004A4A4A005A5A5A006B6B
      6300CE945A00FFEFE700FFF7F700FFF7F700FFF7E700FFE7D600F7C69C00E7A5
      6B00FFF7E700000000000000000000000000000000000000000000000000F7F7
      F700BDCECE008C948C00F7FFF70000000000848C8400BDCEBD00ADBDB500739C
      8C0039635A0031294A0039184A004A084A004A084A0039184A0031294A00395A
      5A00739C8C00ADBDAD00000000006B6B6B00EFF7F700ADB5AD0094ADA500E7EF
      EF0000000000000000000000000000000000BDCECE008C6B4A00FFEFDE00F7D6
      C600F7D6C600F7D6C600F7D6C600F7D6C600F7D6C600F7D6C600F7D6C600F7D6
      C600F7D6C600F7D6C600F7D6C600F7D6C600F7D6C600F7D6C600EFCEBD00E7C6
      B500C6AD9C006B637B00427BDE006BADFF003173DE00527BBD00C6BDB500FFF7
      F700ADB5DE0094A5B500F7F7F700000000000000000000000000000000000000
      0000000000000000000000000000C6C6C600183942005AF7FF0073EFFF0094F7
      FF008CF7FF006BDEFF0063DEFF0063DEFF0063DEFF0063DEFF006BE7FF008CF7
      FF008CF7FF006BEFFF0052EFFF0010313900CECECE0000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000C69C8C00A56B3100C66B1000CE6B1000DE7B3100D69C
      7300F7B59C00B5948C003129210031393900525252006B6B6B007B8484007B7B
      840084634200E7AD7B00FFE7DE00FFEFDE00F7D6BD00DE945200DEAD8C000000
      000000000000000000000000000000000000000000000000000000000000F7F7
      F700BDCECE008C948C00F7FFF700C6D6CE00BDCEBD00ADBDAD006B8C84003931
      4A004A104A00734A7B00845A8C009473940084638C007B4A7B00734A73004A10
      4A0039314A0063847B00ADBDAD00C6D6C600EFF7EF00A5B5A50094ADA500E7EF
      EF0000000000000000000000000000000000BDCECE008C6B4200FFE7DE00FFFF
      F700000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FFFFF700E7E7DE00CEC6
      BD006B739400397BD6006BB5FF003994FF00428CFF00D6E7FF00B5C6EF009CA5
      CE004A525200C6D6CE00F7F7F700000000000000000000000000000000000000
      00000000000000000000C6C6C60010424A0052EFFF0063EFFF0084F7FF0084F7
      FF007BFFFF000000000000000000000000000000000000000000081821007BFF
      FF0084F7FF0084F7FF0063EFFF004AEFFF0010313900CECECE00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000E7CEC600C65A0000CE6B00005A84A5007B8C9C004AA5
      D6007B6352002121210042424200525A5A00737B7B008C9C9C009CA5A500848C
      8C006B6B6B006B5A42009C6329009C5A2100AD5A0000B5520800FFEFE7000000
      000000000000000000000000000000000000000000000000000000000000F7F7
      F700BDCECE008C948C00F7FFF700C6D6CE00B5C6B5007394840042214A005218
      520052185A004A1052004A2142004A3939004A3939004A2142004A1052005218
      5A005218520042214A007B948C00BDCEBD00EFF7EF00A5B5A50094ADA500E7EF
      EF0000000000000000000000000000000000BDCECE008C6B4200FFE7DE00F7DE
      D600FFE7DE00FFE7DE00FFE7DE00FFE7DE00FFE7DE00FFE7DE00FFE7DE00FFE7
      DE00FFE7DE00FFE7DE00FFE7DE00FFE7DE00F7DED600E7CEC600CEB5A5006B6B
      8400397BD60063BDFF003194FF003994FF00D6E7FF00B5D6FF003152AD00DEC6
      BD00736B4A00C6D6D600F7FFF700000000000000000000000000000000000000
      000000000000BDBDBD0010424A004AEFFF005AEFFF007BF7FF007BEFFF006BEF
      FF006BFFFF000010180000000000000000000000000000000000103139006BFF
      FF006BEFFF0073EFFF0073EFFF005AEFFF0042EFFF0008313900C6C6C6000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000BD521800CE6B0000638C940000D6DE000842
      4A00292929004A4A4A005A6363007B8484009CA5A500ADB5BD00A5ADAD00848C
      8C00636363004242420018394200635A4A00CE630000BD734A00000000000000
      000000000000000000000000000000000000000000000000000000000000F7F7
      F700BDCECE008C948C00F7FFF700C6D6CE009CB5A5004A3952005A215A005A21
      5A0052294A005294080084CE3900A5DE63009CDE63007BCE3100529408005231
      42005A215A005A215A004A295200A5BDAD00EFF7EF00A5B5A50094ADA500E7EF
      EF0000000000000000000000000000000000BDCECE008C6B4200FFE7DE00EFD6
      CE00FFE7DE00FFE7DE00FFE7DE00FFE7DE00FFE7DE00FFE7DE00FFE7DE00FFE7
      DE00FFE7DE00FFE7DE00FFE7DE00F7DED600E7CEC600C6B5A5006B638400317B
      D60063BDFF002994FF003194FF00D6E7FF00B5DEFF003163BD00DEC6B500FFE7
      D600736B4A00CED6D600F7F7F700000000000000000000000000000000000000
      0000BDBDBD0010424A0042EFFF0052EFFF006BEFFF006BEFFF0063EFFF005AE7
      FF0063FFFF0000181800000000000000000000000000000000001029390063FF
      FF005AE7FF005AEFFF006BEFFF006BEFFF004AE7FF0039E7FF0008394200C6C6
      C600000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000CE947B00CE63000052525200082929003939
      3900525252006B6B6B008C949400A5ADB500ADB5BD009CA5A5007B7B84005A5A
      5A0029313100087B840000E7F70094735200C65A0000CEB5AD00000000000000
      000000000000000000000000000000000000000000000000000000000000F7F7
      F700BDCECE008C948C00F7FFF700BDD6C6007B8484005A215A00633163005231
      4A005AB500007BCE2900A5DE7300B5DE8C00ADDE7B0094CE52006BC610005AB5
      000052314A00633163005A215A0073848400EFF7EF00A5B5A50094ADA500E7EF
      EF0000000000000000000000000000000000BDCECE008C6B4200FFE7DE00EFCE
      BD00FFE7DE00FFE7D600FFE7D600FFE7D600FFE7D600FFE7D600FFE7D600FFE7
      D600FFE7D600FFE7D600F7DED600E7CEBD00C6B5A5006B638400317BD6005ABD
      FF00219CFF003194FF00D6EFFF00B5DEFF00315ABD00E7CEC600EFCEBD00FFE7
      D60073634A00CED6D600F7F7F70000000000000000000000000000000000BDBD
      BD0010424A0039E7FF004AE7FF0063EFFF0063EFFF0052E7FF0052E7FF0052E7
      FF0063FFFF000010180000000000000000000000000000000000103139005AFF
      FF0052E7FF0052E7FF0052E7FF005AEFFF005AEFFF0042E7FF0031E7FF000839
      4200C6C6C6000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000DED6CE00522900002121180042424200525A
      5A00737B7B00949C9C00ADB5B500A5ADAD00848C8C00636B6B00424242004239
      3900299CC60000FFFF0000F7FF0073847B00BD52180000000000000000000000
      000000000000000000000000000000000000000000000000000000000000F7F7
      F700BDCECE008C948C00F7FFF700BDCEC600524263006B396B005A296300529C
      100039AD080029A5100063C618006BC6210052B51800299C100052BD080052C6
      0000429410004A4252006B396B0052426300E7F7EF00A5B5A50094ADA500E7EF
      EF0000000000000000000000000000000000BDCECE008C6B4200FFE7DE00E7C6
      B500FFE7D600FFE7D600FFE7D600FFE7D600FFE7D600FFE7D600FFE7D600FFE7
      D600FFE7D600F7DECE00E7CEC600CEB5A5006B6384003184D60052BDFF00219C
      FF00299CFF00CEEFFF00B5DEFF002963BD00DEC6BD00FFDED600E7C6B500FFE7
      D60073634A00CED6D600F7F7F700000000000000000000000000B5B5B5000842
      520029E7FF0039E7FF0052EFFF0052EFFF004AE7FF004AE7FF004AE7FF0052E7
      FF005AFFFF000010180000000000000000000000000000000000082939005AFF
      FF004AE7FF004AE7FF0042E7FF004AE7FF0052EFFF004AEFFF0039E7FF0029E7
      FF0008394200C6C6C60000000000000000000000000000000000000000000000
      00000000000000000000DEDEDE0042424200292929004A4A4A005A6363008484
      84009CADAD00A5B5B500949C9C006B7373004A52520031313100947B7B00EFB5
      9C00849CB50008DEF70018CEEF005A8C9C00C68C730000000000000000000000
      000000000000000000000000000000000000000000000000000000000000F7F7
      F700BDCECE008C948C00F7FFF700B5CEBD0052295A00734273005A31520039BD
      080000841800007B180031B508004AC6080010941000007B1800109410004AC6
      08001094100031424200734273005A295A00E7F7EF00A5B5A50094ADA500E7EF
      EF0000000000000000000000000000000000BDCECE008C6B4200FFE7DE00E7BD
      AD00FFE7D600FFDED600FFDED600FFDED600FFDED600FFDED600FFDED600F7DE
      D600F7DECE00EFD6C600CEBDAD006B6B8C002984D60052C6FF0018A5FF00219C
      FF00CEEFFF00ADDEFF002963BD00DEC6BD00F7DECE00FFE7D600E7BDAD00FFE7
      D60073634A00CED6D600F7F7F7000000000000000000B5B5B5000842520021E7
      FF0031E7FF0042EFFF004AE7FF0042E7FF0042DEFF0042DEFF004AE7FF004AE7
      FF0052FFFF0000181800000000000000000000000000000000000829390052FF
      FF004AE7FF0042E7FF0042DEFF0039DEFF0039E7FF0042E7FF0042EFFF0029DE
      FF0021DEFF0008394A00C6C6C600000000000000000000000000000000000000
      000000000000ADADAD0021212100393939004A5252006B6B6B008C949400A5AD
      B5009CA5A5007B8484005A5A5A00313939005A636300B5DEE700B5CEDE00F7AD
      8C00E7945A00399CD6009C734A00C6520000EFDEDE0000000000000000000000
      000000000000000000000000000000000000000000000000000000000000F7F7
      F700BDCECE008C948C00F7FFF700B5CEBD005A295A007B4A7B004A42420018AD
      1000109C1800189C1000189C100042CE1000007B180029BD10000084180042CE
      1000007B1800425239007B4A7B005A295A00E7F7EF00A5B5A50094ADA500E7EF
      EF0000000000000000000000000000000000BDCECE008C6B4200FFE7DE00DEB5
      A500FFDED600FFDECE00FFDECE00FFDECE00F7DECE00F7DECE00F7DECE00F7DE
      CE00F7D6C600DEC6B500AD9C94005273B50094CEE70029ADFF0018A5FF00CEEF
      FF00ADDEFF002963BD00DEC6B500F7D6C600F7DECE00FFDED600DEB5A500FFE7
      D60073634A00CED6D600F7F7F70000000000B5B5B500084A5A0018E7FF0021DE
      FF0029DEFF0031E7FF0031DEFF0031DEFF0039DEFF0039DEFF0039DEFF0039E7
      FF0042FFFF0000101800000000000000000000000000000000000831390042F7
      FF0039E7FF0039DEFF0039DEFF0031DEFF0031DEFF0031DEFF0031E7FF0021DE
      FF0018DEFF0018DEFF0000394A00D6D6D600000000000000000000000000F7EF
      EF006B6B6B002121210042424200525A5A00737B7B0094A5A500A5ADAD00848C
      8C00636B6B004242420039313100A5ADAD00EFFFFF00E7E7EF00E7C6BD00EFA5
      7B00E78C4A00947B6300CE6B0800BD6331000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000F7F7
      F700BDCECE008C948C00F7FFF700BDD6C60063296300845A7B004A4A4A00008C
      100021B5180029C621000084180039C62900088C180039D621000084180021B5
      1800008C1800425A3900845A7B005A296300EFFFEF00A5B5A50094ADA500E7EF
      EF0000000000000000000000000000000000BDCECE008C6B4200FFE7DE00D6AD
      9C00FFDECE00FFDECE00A58C8C00FFDECE00F7DECE00F7DECE00F7DECE00F7DE
      CE00E7CEBD00CEB5A5005A638C009CC6DE00B5D6E700B5D6E700C6EFFF00ADDE
      FF002963BD00DEBDB500F7D6C600F7DECE00F7DECE00FFDECE00D6AD9C00FFE7
      D60073634A00CED6D600F7F7F7000000000063636300109CBD0021E7FF0029D6
      FF0029D6FF0029D6FF0031DEFF0039DEFF0039DEFF0039E7FF004AA5B5003173
      8C003984A5000810180008000000080808000808080008000000102129003984
      A500316B8C004AADC60039E7FF0039DEFF0031DEFF0031DEFF0029D6FF0029D6
      FF0021D6FF0021E7FF00008CAD0094948C000000000000000000D6CEC6009463
      310039312900424242005A636300848C8C009CA5AD00949C9C00737373005252
      52003131290073524A00EFCEBD00F7EFEF00F7F7FF00FFDED600F7BDA500EF9C
      7300DE843900D6731000CE630000D6ADA5000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000F7F7
      F700BDCECE008C948C00F7FFF700C6DECE00633963008C6384004A4A4A000084
      100029D629005AE74A0000842100108C290031AD42006BE76300109C21000084
      1800009C1800524A52008C63840063316300EFFFF700A5B5A50094ADA500E7EF
      EF0000000000000000000000000000000000BDCECE008C6B4200FFE7DE00CEA5
      8C00F7DECE00FFDECE00A58C8C00FFDECE00F7DECE00F7DECE00F7D6C600EFD6
      C600DEBDAD00A5948C005A7BB500B5D6E700C6DEEF00EFF7F700CEEFFF002163
      BD00DEBDB500F7D6C600F7D6CE00F7D6CE00F7DECE00F7DECE00D6A58C00FFE7
      D60073634A00CED6D600F7F7F700000000000000000042424200109CBD0039E7
      FF0039DEFF0039DEFF0039DEFF0042DEFF0042DEFF004AE7FF0052E7FF002110
      1000100800001818180018181800181818001818180018181800181818001000
      00002921210052EFFF0042DEFF0042DEFF0042DEFF0039DEFF0039DEFF0039DE
      FF0039E7FF001094B500525252000000000000000000AD9C9400C68442008C5A
      210042424200525252007B7B7B008C9C9C007B8484005A5A5A00393939003929
      210063738400C6ADA500B5CEDE00FFEFE700FFF7EF00FFDECE00F7B59C00EF94
      6300DE7B3100D66B1000BD520800000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000F7F7
      F700BDCECE008C948C00F7FFF700C6DECE006B5273008C6B8C006B5A6B00109C
      210042E74A0094F79C0094DE9C004AAD5A00B5EFB500A5F7AD005AE7630008A5
      180010B521007B4273008C6B8C006B527300F7FFF700A5B5A50094ADA500E7EF
      EF0000000000000000000000000000000000BDCECE008C6B4200FFE7DE00CE9C
      8400FFDECE00FFDECE00A58C8400FFDECE00F7D6C600F7D6CE00F7D6C600EFCE
      BD00CEB5A5004A528400A5C6D600DEF7F700000000009CADD6005A639C00DEC6
      B500F7D6C600F7D6C600F7D6C600F7D6C600F7D6C600F7DECE00CE9C8400FFE7
      D600736B4A00CED6D600F7F7F70000000000000000000000000042424200109C
      BD0052EFFF0052DEFF0052DEFF0052E7FF0052E7FF005AE7FF005AE7FF0063E7
      FF00392121003131310031313100313131003131310031313100313131003931
      290063EFFF005AE7FF005AE7FF0052DEFF0052DEFF0052DEFF004ADEFF0052EF
      FF001094AD00525252000000000000000000DED6CE00E7A57300FFDEC6009463
      3900424242004A4A4A00525A5A00525A5A0042424A002929290063311000CE73
      180031B5DE0029DEFF0094CEE700FFE7DE00FFEFE700FFD6BD00F7AD8C00E794
      5200D67B2100CE6B0800C67B5200000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000F7F7
      F700BDCECE008C948C00F7FFF700C6DECE009C9C9C00734A73009C7B94004A42
      520018DE3100A5F7AD00CEFFD600CEFFD600CEFFCE00C6FFCE008CF7940010DE
      29004A4252009C7B94007B527B00A5A5A500EFFFF700A5B5A50094ADA500E7EF
      EF0000000000000000000000000000000000BDCECE008C6B4200FFE7DE00C694
      7B00F7D6C600F7D6C600A58C8400FFDECE00FFDEC600FFDECE00F7D6C600EFCE
      BD00B5A5A50000001000181818009CADDE00636BA500C6B5AD00F7D6BD00F7D6
      C600F7D6C600F7D6C600F7D6C600F7D6C600F7D6C600F7D6C600C6947B00FFE7
      D600736B4A00CED6D600F7F7F700000000000000000000000000000000004242
      4200189CBD0073F7FF006BE7FF006BE7FF006BE7FF006BE7FF006BE7FF0073EF
      FF007BCEDE005242390052525200525252005252520052525200524242007BD6
      EF006BEFFF006BE7FF006BE7FF006BE7FF0063E7FF0063E7FF006BF7FF00108C
      AD005A5A5A00000000000000000000000000E7C6A500FFE7D600FFF7E700DEA5
      73004A392900393939003939390031313100292921006B423100AD420800D673
      10004AA5C60010FFFF006BD6F700F7DED600FFE7DE00F7CEB500EFA58400E78C
      4A00D6731800C65A0800D6BDB500000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000F7F7
      F700BDCECE008C948C00F7FFF700C6D6CE00BDCEBD00735273009C7B94009C7B
      94004A42520008D6310042F763007BF794007BF794004AF7730008D631004A42
      52009C7B94009C7B94006B426B00C6DECE00EFF7EF00A5B5A50094ADA500E7EF
      EF0000000000000000000000000000000000BDCECE008C6B4200FFE7D600C68C
      7300F7D6C600F7D6C600F7D6C600A58C8400A58C8C00A58C8C00A58C8400A58C
      8400847373006B5A5A004A4A7300CEB5B500F7D6C600F7D6C600F7D6C600F7D6
      C600F7D6C600F7D6C600F7D6C600F7D6C600F7D6C600F7D6C600C68C7300FFE7
      D600736B4A00CED6D600F7F7F700000000000000000000000000000000000000
      00004A4A4A00189CBD008CF7FF0084E7FF0084EFFF0084EFFF0084E7FF0084EF
      FF0084F7FF008CB5BD006B63630073737300737373006B6363008CC6CE0084F7
      FF0084E7FF0084E7FF0084EFFF0084E7FF0084E7FF008CF7FF001094AD005A5A
      5A0000000000000000000000000000000000F7D6BD00FFE7D600FFFFF700FFEF
      DE00D69C63007B4A10006339100052211000A54A1800C65A2100B54A1800BD6B
      290018CEEF0008FFFF0042F7FF00BDD6E700EFDEDE00A5BDD600BD9C9C00A584
      7300D6731000BD5A180000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000F7F7
      F700BDCECE008C948C00F7FFF700C6D6CE00BDCEBD00B5C6BD006B426B00A584
      9C00AD8CA500845A840052525A00186B3900187B31004A6352007B527B00AD8C
      A500A5849C006B426B00BDCEBD00C6D6CE00EFF7EF00A5B5A50094ADA500E7EF
      EF0000000000000000000000000000000000BDCECE008C6B4200FFE7D600BD84
      6B00F7D6C600F7D6C600F7D6C600F7D6C600FFDEC600FFDECE00F7DECE00F7DE
      CE00F7DECE00F7DECE00F7DECE00F7DECE00F7DECE00F7DECE00F7DECE00F7DE
      CE00F7D6C600F7D6C600F7D6C600F7D6BD00F7D6BD00F7D6C600BD846B00FFE7
      D600736B4A00CED6D600F7F7F700000000000000000000000000000000000000
      0000000000004A4A4A001094B500ADFFFF009CEFFF009CEFFF009CEFFF009CEF
      FF009CEFFF009CFFFF00A5ADB5008C8C8C008C8C8400A5BDC6009CFFFF009CEF
      FF009CEFFF009CEFFF009CEFFF009CEFFF00ADFFFF00088CAD005A5A5A000000
      00000000000000000000000000000000000000000000EFB58400FFEFDE00FFE7
      DE00EFBD9400C6631800BD633100DE945A00DE8C5200CE733900BD522100AD5A
      2900738C940021CEEF0073B5D600EFCEC600E7D6D6004AE7FF0018DEF7008C84
      7B00CE6B1000C68C730000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000F7F7
      F700BDCECE008C948C00F7FFF700C6D6CE00BDCEBD00BDCEBD00BDCEBD00735A
      7B008C738C00C6B5BD00CEBDC600D6CED600D6C6CE00C6B5C600C6B5BD008C73
      8C006B4A7300BDCEC600C6D6C600C6D6CE00EFF7EF00A5B5AD0094ADA500E7EF
      EF0000000000000000000000000000000000BDCECE008C6B4200FFE7D600B57B
      6300F7D6BD00F7D6BD00F7D6BD00F7D6C600F7D6C600F7DECE00F7DECE00F7DE
      D600F7DED600F7E7D600F7E7D600F7E7D600F7E7D600F7E7D600F7DED600F7DE
      CE00F7DECE00F7D6C600F7D6C600F7D6BD00F7D6BD00F7D6BD00B57B6300FFE7
      D600736B4A00CED6D600F7F7F700000000000000000000000000000000000000
      000000000000000000004A4A4A001894B500CEFFFF00B5F7FF00B5F7FF00B5F7
      FF00B5F7FF00B5F7FF00BDFFFF00B5B5B500B5BDBD00BDFFFF00B5F7FF00B5F7
      FF00B5F7FF00B5F7FF00BDF7FF00C6FFFF00088CA5005A5A5A00000000000000
      0000000000000000000000000000000000000000000000000000EFBD8C00E7AD
      7300D6B59400C6734200F7C69C00EFAD8400DE946300CE7B4200BD5A2900B542
      1000D6731800738C9C00ADA5AD00F7C6B500BDCEDE0031F7FF0010E7FF00A57B
      5A00C65A0800E7D6CE0000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000F7F7
      F700C6D6D6008C948C00000000006B736B00848C8400BDCEBD00C6D6C600C6DE
      CE00A5ADAD00735A7B006B426B00734A7300734A7300734A73007B5A7B00ADAD
      AD00CEDECE00C6D6C6009CA59C006B736B00F7FFF700ADB5AD009CADAD00EFEF
      EF0000000000000000000000000000000000BDCECE008C6B4A00FFE7D6009C63
      4A00DEB5A500DEB5A500DEB5A500DEBDAD00E7C6B500E7CEBD00E7CEC600EFD6
      CE00EFD6CE00EFDED600EFDECE00EFDECE00EFDECE00EFD6CE00EFD6CE00E7CE
      C600E7C6BD00E7C6B500DEBDAD00DEB5A500DEB5A500DEB5A5009C634A00FFE7
      CE00736B4A00CED6D600F7F7F700000000000000000000000000000000000000
      00000000000000000000000000004A4A4A001094B500E7FFFF00D6F7FF00CEF7
      FF00CEF7FF00CEF7FF00CEF7FF00D6F7FF00D6FFFF00CEF7FF00CEF7FF00CEF7
      FF00CEF7FF00D6F7FF00E7FFFF00088CA5006363630000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000EFDED600D68C5A00F7C6A500EFB58400DE9C6300CE7B4200BD5A2900AD42
      1000C65A1800D6844200E79C7B00EFBDAD007BDEF70021FFFF0008FFFF006B8C
      9400C66B39000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000FFFF
      FF00DEE7E7008C9484000000000000000000A5B5AD00CED6CE00CEDECE00D6E7
      D600D6E7DE00DEEFE700DEF7EF00E7FFEF00E7F7EF00DEF7E700DEEFE700D6E7
      DE00D6DED600CEDECE00000000009C9C9C0000000000ADB5AD00B5BDBD00F7F7
      F70000000000000000000000000000000000BDCECE008C6B4A00D6946B00BD6B
      1800BD6B1800BD6B2100BD6B2100BD732900C6733100C67B3900C67B4200C684
      4200C6844A00C6844A00CE844A00CE844A00C6844A00C6844A00C6844200C67B
      4200C67B3900C6733100C6732900BD6B2100C66B1800C66B1800C66B1800D694
      6B00736B5200CEDED600F7F7F700000000000000000000000000000000000000
      000000000000000000000000000000000000525252001094B50000000000EFFF
      FF00E7FFFF00E7FFFF00E7FFFF00E7FFFF00E7FFFF00E7FFFF00E7FFFF00E7FF
      FF00EFFFFF00000000000884A500636363000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000C6735200E7A57300EFAD7B00DE945A00CE734200BD522100AD39
      1000B5421000DE7B3100EF946300F7B59C00CEBDBD0029D6F7004AA5C6009473
      6300E7B5A5000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000F7F7F7008C949400BDCEC600F7FFF700F7FFF700FFFFFF00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000F7FFF700F7F7F700F7F7F700F7FFF700DEEFE700848C8400E7E7E7000000
      000000000000000000000000000000000000BDD6CE008C6B4A00DE9C3900DEAD
      3900DEAD4200E7B54A00E7B55200E7BD6300EFC67B00EFCE8C00EFD69C00F7D6
      A500F7DEAD00F7DEB500F7E7B500F7DEB500F7DEAD00F7DEA500EFD69C00EFCE
      8C00EFC67B00E7BD6300E7B55200E7AD3900A59C6300B5944A00DE9C1000D694
      31007B6B5200CEDEDE00F7FFF700000000000000000000000000000000000000
      00000000000000000000000000000000000000000000525252001094B5000000
      000000000000F7FFFF00F7FFFF00F7FFFF00F7FFFF00F7FFFF00F7FFFF000000
      0000000000000084A50063636300000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000DEAD9C00C66B3900D6844200C66B3100B5521800AD39
      0800AD391000D66B2900E7945200F7AD8C00F7B59C00529CD600C6844A00C65A
      1800FFF7EF000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000EFEFEF009CA5A5008C948C00949C9400949C9400949C94009C9C
      94009C9C94009C9C94009C9C94009C9C94009C9C94009C9C9400949C9400949C
      9400949C9400949C9400949C9400949C9400848C8400D6DED600000000000000
      000000000000000000000000000000000000CEDEDE00946B4A00E7AD3900E7B5
      3100E7B53100E7B53100E7BD3900E7BD4200EFBD4A00EFC65200EFC65A00EFCE
      6300EFCE6B00EFCE7300EFCE7300EFCE7300EFCE6B00EFCE6B00EFCE6300EFC6
      5A00EFC65200EFBD4A00EFBD3900EFBD31000073FF002984DE00EFBD3100DE9C
      4A0084735200DEE7E700F7FFFF00000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000052525200088C
      AD00000000000000000000000000000000000000000000000000000000000000
      00000084A5006363630000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000CE8C7300BD521800B5421000A531
      0800A5310800BD522100E78C4A00EFA57B00F7AD8C00CE946B00DE7B2900CE84
      6300000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000E7EFEF008C6B4A00E7C6AD000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000003194FF005A8CBD00F7BD5200BD84
      52009C8C7300EFF7EF0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000005A5A
      5A00088CAD000000000000000000000000000000000000000000000000000084
      A5006B6B6B000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000F7E7DE00C66B4A00AD39
      0800A5310800B5421800DE843900EF9C6B00EFA57B00E78C4A00CE6B2100EFCE
      BD00000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000F7FFF700D6DEDE00946B4A00A56B
      42009C6B42009C6B42009C6B42009C6B42009C6B4A009C734A009C734A00A573
      5200A5735200A5735200A57B5200A57B5200A5735200A5735200A57352009C73
      4A009C734A009C6B4A009C6B42009C6B4200A56B4200A56B4200A56B4200A58C
      6B00E7EFEF00FFFFFF0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00005A5A5A00088CAD0000000000000000000000000000000000007B9C006B6B
      6B00000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000EFD6
      CE00B5522900AD421000CE6B3100E7945200E7946300DE843900C66B39000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FFFFFF00EFF7F700E7EF
      EF00DEE7E700DEE7E700D6E7E700D6E7E700DEE7E700D6E7E700DEE7E700DEE7
      E700D6E7E700DEE7E700DEE7E700DEE7E700DEE7E700D6E7E700DEE7E700D6E7
      E700D6E7E700DEE7E700D6E7E700D6E7E700DEE7E700DEE7E700E7EFEF00F7F7
      F700FFFFFF000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000005A5A5A000884A5000000000000000000007B9C006B6B6B000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000E7B59C00C65A3100D67B3100DE843900CE6B2900EFCEBD000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000FFFFFF00FFFFFF00FFFFFF00FFFFFF00F7FFFF00F7FFFF00F7FFFF00F7FF
      FF00F7FFFF00F7FFFF00F7FFFF00F7FFFF00F7FFFF00F7FFFF00F7FFFF00F7FF
      FF00F7FFFF00F7FFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000636363001894AD0010849C0073737300000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000FFF7EF00EFC6B500DEA58C00F7D6CE00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000737373007B7B7B0000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000008C94
      94008494B5007B9CCE00739CD6006B94DE006394E7005A8CE7005284E7004A84
      EF004A84E7004A7BE7004A7BDE004A7BD600527BCE006B84BD008C8C94000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000006B6B
      AD008484AD000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000008C949C007B94CE00739C
      E70073A5F70073A5F7006BA5F700639CF7005A94F7004AADF700429CF700427B
      F700427BF700397BF700317BF7003173EF00296BEF00296BEF00316BE7004273
      CE006B84AD000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000D6D6D6005252B5003939
      F7003131EF007B7BB50000000000000000000000000000000000000000000000
      000000000000000000000000000000000000BDB5A500C6A56B00CEAD5200D6B5
      6300D6C68400CEC6A50000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000C6BD
      AD00CEC69C00D6CEAD00CEC6A500BDBDB500848CA5006B94E70073A5F70073A5
      F70073A5F70073A5F7006BA5F7004AC6FF0029D6FF0021D6FF00429CF700427B
      F700427BF7003973F700317BF70029ADF7002984EF002963EF002163E700215A
      E700295ADE006B84AD0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000006363A5002121F7004A4A
      F7004242F7001818E7008C8CAD00000000000000000000000000000000000000
      000000000000000000000000000000000000C69C5200C69C0000AD9C0000AD9C
      0000BDAD2900E7C65A00E7CE9400C6C6BD000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000C6B5A500DEBD
      4200E7CE7300E7D69400E7D68400D6C66B005A8CE700639CF7006BADF7006BB5
      F70073A5F70073A5F7006BADF7004AC6F70021D6FF0039BDF70042A5F7004284
      F700427BF700397BF7003184F70018C6FF0018CEFF0021ADF7002173EF00215A
      E700215ADE003963CE008C949400000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000C6C6C600BDBDBD00D6D6
      D600000000000000000000000000D6D6D6005A5AAD000808EF001010F7001010
      F7001010F7001010EF000808DE007B7BB5000000000000000000000000000000
      000000000000000000000000000000000000DEBD8400CEAD3100D6C68C00BDAD
      5200A5940000D6BD6300EFD68C00EFDEBD00EFE7C600D6D6C600000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000C6B59C00DEC6
      5200E7D69400E7D68C00E7D68400E7D68C004284E7005A9CF70039D6FF005ABD
      FF0073A5F70073A5F70073A5F700639CF70052ADF700528CF7004A84F7004284
      F700427BF700397BF700319CF70021C6F70010D6FF0018C6F700216BE700295A
      E700295ADE00315ACE0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000CECECE0073736B008C7363008484
      7B00BDBDBD0000000000000000005252B5000000F7000000F7000000FF000000
      FF000000FF000000F7000000EF000000EF007B7BAD0000000000000000000000
      000000000000000000000000000000000000EFDEB500EFDEAD00F7EFD600E7DE
      B500DED6B500EFDEA500EFD68C00F7EFCE00F7EFD600F7EFD600DEDED600EFE7
      DE00EFE7DE00E7DED600DEDED600DEDED600DEDED600D6D6D600D6D6CE00D6D6
      CE00CECECE00CECEC600CECEC600CECEC600CECEC600CECEBD00D6CEAD00E7D6
      9C00EFE7BD00EFDEA500EFDEA500E7DEAD005A84C6004A94F7005AADF7006BAD
      F70073A5F70073A5F70073A5F7006B9CF7006394F700528CF7004A84F7004284
      F700397BF700397BF700316BEF00299CF70021B5F7002194EF002173E700215A
      DE002152DE00636BAD00AD846300AD7B6300A57B6300A5736300A57B63009C7B
      6B009C847B00948C8C0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000DEFF0000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000009C9C9C00735A4200BD8C6300CE9C
      7B00947B6B00949494005A5AA5000000EF000000F7000000FF000000FF000000
      FF000000FF000000FF000000F7000000EF000808DE008484AD00000000000000
      000000000000000000000000000000000000E7DEAD00F7EFCE00FFF7EF00FFFF
      F700FFF7EF00EFDEA500EFD68400F7F7E700FFF7EF00F7EFDE00F7EFDE00EFDE
      D600B5CECE008CC6DE008CC6DE00B5D6DE00EFE7DE00EFE7DE00FFF7E700EFEF
      DE00E7E7DE00F7EFDE00EFE7D600EFDECE00EFE7CE00EFDEC600E7D6B500EFDE
      AD00E7D6A500E7D6A500EFDEA500E7DEAD00848C9C004A84E7005A94F7007BAD
      F7007BADF7006BB5F70042CEFF0052BDFF00639CF7005A8CF7004A8CF7004284
      F700397BF7003973F7003173EF002973EF002963EF00296BEF00296BE700215A
      DE002952D6009C7B7B00BD7B3900B5733900B56B3900B56B3900AD633900AD63
      3100AD633100AD633900A56B5A00948484000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000042C60000F7FF00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000BDBDBD006B6352008C634200AD735200CE9C
      7300DEAD84004A39B5000000EF000000F7000000FF000000FF000000FF000000
      FF000000FF000000FF000000FF000000F7000000EF000000E7007373B5000000
      000000000000000000000000000000000000E7D6AD00F7E7C600F7F7E700FFF7
      EF00F7F7E700EFDEAD00EFD68C00F7EFDE00F7F7E700FFF7E700E7DECE007BB5
      D60021BDF70008C6FF0000CEFF0010CEFF006BC6E7009CBDC600C6CECE00DED6
      D600D6CECE00EFE7DE00DED6CE00DECEC600DECEBD00DECEBD00D6CEB500DED6
      AD00DECEA500DECEA500EFDEA500E7DEAD00000000006384BD004A8CF70073AD
      F70094BDFF006BB5F7004ACEFF005AB5F7006394F7005A94F7004A8CF7004284
      F700397BF700397BF7003173EF00316BEF002973EF0021B5F70018BDF7002163
      DE004263C600C68C5A00BD7B4A00BD734200B56B3900B56B3900AD633100AD63
      3100AD5A3100AD5A3100A55A31009C6342000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000DEFF000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000D6D6D6008C8484007B5A420094634200BD845200BD7B
      4A0052399C000000E7000000EF000000F7000000FF000000FF000000FF000000
      FF000000FF000000FF000000FF000000FF000000F7000000EF000000E7008484
      AD0000000000000000000000000000000000E7D6B500F7E7C600F7F7E700FFF7
      EF00F7F7E700EFDEAD00EFD68C00E7E7DE00F7F7E700FFF7E700BDD6DE0010C6
      F70000CEFF0000D6FF00217BF7004273DE009CBDAD0010D6F70031D6F700C6DE
      EF00DED6DE00EFE7EF00E7DEDE00EFE7DE00FFF7DE00E7D6C600E7D6BD00F7E7
      C600EFDEB500EFDEA500EFDEA500E7D6AD00000000008C949C004A84E700639C
      F7009CC6FF007BA5F70073A5F7006B9CF7006394F7005A94F7004A8CF700427B
      F7003973F7003194F7002994F7003163EF00296BE700218CEF00218CE700215A
      DE009494B500DEAD8C00D6A58400CE947B00CE947B00C68C7300BD846B00BD7B
      6300B56B4A00AD5A3100A55229009C5A39000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000B5FFFF0063C6
      FF0000000000000000000042C600000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000ADADAD006B5A4A00845A4200AD734A00BD7B52005231
      9C000000DE000000EF000000F7000000FF000000FF000000FF000000FF000000
      FF000000FF000000FF000000FF000000FF000000FF000000F7000000EF000000
      DE007B7BAD00000000000000000000000000DED6B500F7E7C600F7F7E700FFF7
      EF00F7F7E700EFDEB500DECE9C00DEDEDE00E7E7D600F7E7DE0073C6DE0000CE
      FF0000D6FF0000DEFF002184F7004273DE009CC6B50000E7FF0000E7FF00C6DE
      E700B5C6C60094CEDE00B5C6D600CECEDE00E7E7E700E7E7D600D6C6B500EFDE
      BD00EFDEB500E7D6A500EFDEA500E7D6AD0000000000000000006B84BD00528C
      F7009CBDFF008CB5FF006BADF70063ADF70052B5F7005A9CF700528CF700428C
      F7003984F70031ADF70021C6F7002984EF00296BEF002963E700214ADE004A63
      C600D6AD9400D6AD8C00CE9C7B00C68C7300C68C7300C68C7B00C6947B00CE94
      8400C6948400BD7B6B00AD6B4A00946352000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000FFFF
      FF00006BFF000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000CECECE00736B6B00845A42008C633900BD7B520042299C000000
      DE000000E7000000F7000000FF000000FF000000FF000000FF000000FF000000
      FF000000FF000000FF000000FF000000FF000000FF000000FF000000F7000000
      EF000000E7006B6BAD000000000000000000D6CEB500F7E7C600F7F7E700FFF7
      EF00F7F7E700EFDEB500DECEA500EFE7DE00D6CECE0084BDD60010CEF70000DE
      FF0000DEFF0000E7FF0000EFFF0018BDF70000DEFF0010EFFF0008EFFF004ADE
      EF0039DEEF0000E7FF0021D6F7007BCEE700DEDED600CECED600CECEC600DECE
      B500DED6B500DECEA500EFDEA500DED6AD0000000000000000008C9494004A84
      E7007BADF700A5C6FF0052C6F70021DEFF0031D6FF005A9CF700528CF70031B5
      F70021CEFF0018CEFF0010CEFF0018CEF70021BDF700217BE7002152D600948C
      A500CE9C6B00C68C6300BD844A00B5733900B56B3100B56B3900AD633900B56B
      4200BD7B6300C68C7B00BD8C7B009C8C84000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000004AE7FF000000
      0000B5FFFF00006BFF0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000009C9C9C00735A4200845A3900AD73420063428C000000CE000000
      DE000000EF000000FF000000FF000000FF000000FF000000FF000000FF000000
      FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF000000
      F7000000EF000000DE009494AD0000000000D6CEB500F7E7C600F7F7E700FFF7
      EF00F7F7E700E7DEBD00DECEA500EFE7DE00C6CECE00A5DEEF0039DEFF0000DE
      FF0000E7FF0000EFFF0018EFFF0021E7F70021E7F70021EFFF0021E7FF0000E7
      FF0000E7FF0000E7FF0000E7FF0000D6FF00B5E7EF00F7EFDE00D6D6D600DED6
      C600EFDEBD00EFE7B500EFDEA500DED6B5000000000000000000000000006B8C
      BD00639CF700A5CEFF006BC6F70031D6FF0052BDF7005AA5F700528CF700427B
      F700398CF70021CEFF0010D6FF0010CEF7002984EF00215ADE005273C600E7C6
      AD00DEAD9400D6A58C00CE9C7300C68C6B00BD7B5A00B56B4200AD633100AD5A
      2900A55A2900AD5A39009C6B5A0094948C000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000004AE7FF00000094000000
      6B0000000000B5FFFF0063C6FF00000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000BDBDBD006B635200845A39008C6339008C636B000000BD000000D6000000
      EF000000FF000000FF000000FF000000FF000000FF000000FF000000FF000000
      FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF000000
      FF000000EF000000E7001818C600C6C6C600CECEB500F7E7C600F7F7E700FFF7
      EF00F7F7E700E7DEBD00E7D6A500C6D6DE0021BDF7006BCEEF00BDDEDE008CDE
      E70000EFFF0021EFFF0029EFF70021E7F70021DEFF0018C6FF0021A5F700218C
      F7002184F700219CF70018C6FF0000DEFF0039D6F700D6DEDE00E7DECE00D6D6
      CE00DED6B500EFDEB500EFDEA500D6CEB5000000000000000000000000007B8C
      AD00528CF70094BDFF0094BDFF0063B5F7006BA5F7006394F700528CF700427B
      F7003984F70021BDF70029A5F70021B5F700218CE7002952D6009C8CA500E7C6
      B500E7C6B500DEB59C00DEAD9400D6A58C00CE9C8C00CE948400C6847300B573
      5A00AD6339009C5221008C736B00000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000004AE7FF004AE7FF0000009400000094000000
      94004AE7FF0000000000B5FFFF00000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000D6D6
      D6008C848400845A390073523100AD7342004A318C000000C6000000DE000000
      F7000000FF000000FF000000FF000000FF000000FF000000FF000000FF000000
      FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF000000
      FF000000F7000000E7000000E7007B7BA500C6C6BD00F7E7C600F7F7E700FFF7
      EF00F7F7E700EFDEB500E7CEA5008CC6DE0008C6FF0010D6F70039CEE70052C6
      E70021DEFF0029DEF70029DEF70021D6F70021ADF700217BF7002163EF002163
      EF00215AEF00215AEF00219CF70000EFFF0000DEFF006BCEEF00DED6C600DED6
      C600D6C6B500DED6AD00EFDEA500CECEB5000000000000000000000000000000
      00005284DE006BA5F700ADCEFF007BA5F7006BA5F7006394F7005294F7004284
      F700397BF700317BEF00316BE700296BE700216BE7004A6BBD009C7B7300CE8C
      6B00DEB5A500CE947300C68C5A00BD7B4A00BD7B5200BD7B6300C6847300C68C
      7B00C6847B00A5736B0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000004AE7FF002994FF000018AD0000009400000094008CFF
      FF00000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000ADAD
      AD00735A4A00845A3900845A3100AD73520018109C000000CE000000EF000000
      FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF000000
      FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF000000
      FF000000FF000000EF000000E7004242B500C6C6BD00F7E7C600F7F7E700FFF7
      EF00F7F7E700EFE7B500EFD6A5007BCEF70008CEFF0031CEEF0000E7FF0018B5
      F70029DEF70029E7F70021EFF70018E7FF00219CF7002163EF002152EF002129
      EF002121EF002131EF00217BF700219CF70018ADF70029CEF700D6E7DE00EFDE
      CE00DED6CE00F7E7BD00EFDEAD00C6C6B5000000000000000000000000000000
      0000738CB5004A8CF7009CC6FF0084B5F7006B9CF700639CF70039BDF70031A5
      F7003973F7003173EF00296BE7002963E700215ADE005A73B50094948C00BD8C
      7300E7C6B500DEAD9400CE9C7300BD845200B56B3900AD633100AD633100AD63
      3900B57B6B009C8C8C0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000004AE7FF000063E7000042C6000018AD00000094008CFFFF000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000CECECE00736B
      6B008C5A39006B4A2900AD73420094635A000000AD000000D6000000F7000000
      FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF000000
      FF000000F7000000FF000000FF000000FF000000FF000000FF000000FF000000
      FF000000FF000000F7000000E7001818CE0000000000EFE7C600F7F7E700FFF7
      EF00F7F7E700EFE7B500EFDEA500CEDEEF0073CEEF0031BDCE0021DEDE0018EF
      FF0029E7F70021DEF70021E7F70018E7F70018C6F7002194F700216BEF002129
      EF002118EF002118EF002118EF00214AEF00217BF70010BDFF006BD6EF00DECE
      CE00EFE7CE00F7E7BD00E7DEAD00000000000000000000000000000000000000
      0000000000005284D60073A5F7008CB5F7006B9CF7006394F7004A94F700398C
      F7003973F7003173EF00296BE7002963DE00295AD6007B8C9C0000000000A594
      8400DEB5A500E7C6B500DEB59C00D6A58C00CE948400BD846B00B5735A00AD5A
      310094634A000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00004AE7FF002994FF000063E7000018AD000018AD002994FF008CFFFF000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000A5A5A500735A
      42007B5231007B523100C67B4A008C5A63000000AD000000DE000000F7000808
      FF000808FF000808FF000808FF000808FF000808FF000000FF000000F7000000
      F7000000F7000000F7000808F7000808FF000808FF000808FF000808FF000808
      FF000000FF000000F7000000E7001010D60000000000E7DEC600F7F7E700FFF7
      EF00F7F7E700EFE7B500F7DEA500EFE7E700A5ADDE0039ADBD0042BD840031DE
      CE0021EFFF0021E7F70018DEF70018EFF70010EFF70010EFF70018CEF700217B
      F7002139EF002139EF002152EF00217BF70018A5F70008CEF7006BBDDE00D6CE
      CE00E7D6BD00E7DEB500DED6AD00000000000000000000000000000000000000
      000000000000738CAD005A94F70084BDFF0052BDF7005AA5F7004A84F700397B
      F7003973F700317BEF002994EF002963DE005273B5000000000000000000948C
      8C00B5846B00D6AD9400CE9C7300C68C6B00C6846B00C68C7B00CE948400BD84
      6B009C847B000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000008CFF
      FF002994FF000063E7000042C6000018AD000018AD008CFFFF00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000C6C6C60073635A008C5A
      39006B422900A56B4200C67B4A00945A5A000000AD000000DE001818F7002121
      FF002121FF002121FF002121FF002121FF002121FF002121F7001010EF000000
      E7000808E7002121EF002121F7002121FF002121FF002121FF002121FF002121
      FF002121FF000808F7000000E7001818CE0000000000DED6C600F7F7E700FFF7
      EF00F7F7E700EFE7B500E7D6B500D6D6DE00B5B5C60029D6E70039C6A50029E7
      E70021EFFF0021DEF70018DEF70018E7F70010E7F70008EFF70008E7F70018C6
      F70018B5F70018B5F70018BDFF0031CEF70018DEF70039B5E700B5CEDE00F7EF
      D600EFE7C600EFDEB500D6CEB500000000000000000000000000000000000000
      000000000000000000005A84D6008CC6FF005ACEFF0063B5F7005A94F700397B
      F7003173F700296BEF00217BE7002963D600848C9C0000000000000000000000
      0000A5847B00DEB5A500D6A58400C6845A00B56B3900AD633100B56B4A00BD84
      7300000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000FFFFFF002994
      FF000063E7000042C6000018AD000018AD00B5FFFF0000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000D6D6D60094949400845A3900734A
      29007B523100BD7B4A00BD7B4A00A56B52000808AD001010D6004A4AF7004A4A
      FF004A4AFF004A4AFF004A4AFF004A4AFF004A4AFF004A4AF7004242E7000000
      D6002121D6004A4AE7004A4AEF004A4AF7004A4AFF004A4AFF004A4AFF004A4A
      FF004A4AFF003131EF000000DE003131B50000000000D6D6C600F7F7E700FFF7
      EF00F7F7E700EFE7B500EFDEAD00EFDED600BDD6DE0000DEFF0000E7FF0021EF
      FF0029DEF70021DEF70021DEF70018E7F70000EFF70039EFF70039EFF70000EF
      F70000EFF70018EFFF0029EFF700BDB58C008CB5BD0094C6EF00D6D6DE00F7EF
      D600EFE7CE00EFDEB500CEC6B500000000000000000000000000000000000000
      00000000000000000000848CAD00A5C6FF00ADCEFF008CB5FF0084B5F7005AC6
      FF0042BDF7004A94EF002963DE005A73B5000000000000000000000000000000
      0000948C8C00C69C8C00DEAD9C00CE9C7B00C68C7B00BD7B6B00AD633100946B
      5A00000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FFFFFF002994FF000063
      E7000042C6000042C6000018AD00B5FFFF000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000CECECE007B6B5A00845A31006342
      2900A56B4200BD7B4A00BD7B4A00C6844A0039218C002929CE007373F7007373
      FF007373FF007373FF007373FF007373FF007373F7007373EF006B6BDE000808
      BD004A4ACE007373DE007373EF007373F7007373FF007373FF007373FF007373
      FF007373F7005A5AE7000000CE0073739C0000000000D6CEC600F7F7E700FFF7
      EF00F7F7E700EFDEB500EFDEAD00DECECE00D6CECE0063D6F70000DEFF0018DE
      FF0021DEF70021EFF70021EFF70010EFF7007BD6DE00C6CECE00BDDEDE0094D6
      DE0073D6DE0021EFF70000EFFF0073D6DE0094CEDE00C6BDC600B5B5B500CECE
      C600CEC6BD00DED6B500CEC6B500000000000000000000000000000000000000
      00000000000000000000000000007BA5DE00A5C6FF006BA5F7005294F70031B5
      F70021D6FF006BBDF7006B8CD6008C8C94000000000000000000000000000000
      000000000000AD8C7B00DEB59C00C6846300B5735200BD7B6300B5847B00948C
      8C00000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000FFFFFF002994FF000063E7000063
      E7000042C6000018AD00B5FFFF00000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000D6D6D600846B5A00734A29007B52
      3100BD7B4A00BD7B5200BD845200CE8C5200845A63002929B5009C9CEF009494
      F7009494FF009494FF009494FF009494FF009494F7009C9CEF008C8CDE000000
      9C004A4ABD00A5A5E7009494EF009494F7009494FF009494FF009494FF009494
      F7009C9CEF007373DE001010A500C6C6C60000000000CECEC600F7F7E700FFF7
      EF00F7F7E700EFE7B500EFD6AD00E7DEDE00E7DED600E7EFEF004AD6F70000DE
      FF0021EFFF0029EFF70021EFF70018EFF70073D6DE00D6D6D600F7EFEF00F7E7
      E700E7DED600CEF7F700A5E7EF00D6EFE700DEEFEF00BDB5B5009C948C00FFEF
      CE00EFDEBD00EFDEAD00D6CEB500000000000000000000000000000000000000
      00000000000000000000000000006B8CC60094BDFF0084B5F700639CF7004294
      F700297BEF00317BEF007B8CB500000000000000000000000000000000000000
      0000000000009C847B00CE9C8400CE947300BD7B5A00AD6342009C7B73000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000FFFFFF002994FF002994FF000063E7000042
      C6000018AD00D6FFFF0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000C6C6C6008C847B00A56B
      4200C67B5200BD845A00C6845A00C68C5A00C68C5A004A3984008C8CD600CECE
      F700BDBDF700BDBDF700BDBDF700BDBDF700BDBDF700CECEEF006363BD000000
      840018189400ADADDE00C6C6EF00BDBDEF00BDBDF700BDBDF700BDBDF700C6C6
      F700C6C6EF004242B500737394000000000000000000CECEC600F7F7E700FFF7
      EF00F7F7E700EFE7B500EFDEB500EFDED600EFE7DE00FFF7EF0094DEEF0000D6
      FF0018EFFF0029EFF70018EFF70018EFF70063E7EF00D6DEDE00FFFFF700E7DE
      DE00DED6CE00F7EFEF00F7E7DE00F7EFE700D6DEDE00A5A5A5006B6B6300EFE7
      CE00F7E7BD00EFDEAD00D6CEB500000000000000000000000000000000000000
      0000000000000000000000000000848CA500638CEF006B9CF7005A94F7006394
      F7005A94F700316BDE007B84A500000000000000000000000000000000000000
      00000000000000000000AD7B6300BD845A00B56B4200B57B6B00948C8C000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000FFFFFF002994FF002994FF000063E7000042C6000042
      C600D6FFFF000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000ADADA500BD7B
      4A00C6845A00C68C6300C68C6300C68C6B00CE946B00BD8C6B0063528C009C9C
      D600EFEFFF00EFEFFF00EFEFFF00F7F7FF00E7E7F7007373BD0010088400846B
      8C00634A840031319C00B5B5DE00F7F7FF00EFEFFF00EFEFFF00F7F7FF00CED6
      EF005A5AB5006B6B9400000000000000000000000000D6CEC600F7F7E700FFF7
      EF00F7F7E700EFE7B500EFDEBD00E7D6CE00E7DED600F7EFE700B5DEE70000D6
      FF0000E7FF0010EFFF0039EFF700ADEFF700F7EFE700E7DED600F7EFE70084C6
      DE0063D6E70084D6DE00B5CED600B5B5B50084848400848484006B6B6B007B7B
      7300BDB59400E7D6A500DED6AD00000000000000000000000000000000000000
      0000000000000000000000000000000000006B84C600638CE7004294EF0031A5
      F700528CEF006B8CCE008C949400000000000000000000000000000000000000
      0000000000000000000094847B00B5735200AD6329009C736B00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000FFFFFF002994FF002994FF000063E7000063E7000042C600FFFF
      FF00000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000B58C7300CE84
      5200C68C6B00CE946B00C6946B00CE946B00CE947300D69C7300CE9473006B52
      84007373B5009CA5D600ADADDE009494D6004242A50021188400947B8C00EFBD
      9C00E7BD9C0073638C0029218C007373BD009CA5D600A5A5DE008C94CE004A42
      9C006B5A7B0000000000000000000000000000000000D6D6C600F7F7E700FFF7
      EF00F7F7E700EFDEB500EFE7BD00DECEBD00D6CEBD00D6CECE0073C6D60000D6
      FF0000E7FF0000EFFF008CE7EF00EFD6D600C6C6C600CECEC600EFE7DE008CDE
      F70000EFFF0031D6C6007BB5AD009C949400848484008C8C940094949C007B7B
      7300948C7B00CEBD9400E7D6AD00000000000000000000000000000000000000
      000000000000000000000000000000000000848CA5005A84DE004AA5E7002194
      DE002963E7007384AD0000000000000000000000000000000000000000000000
      000000000000B5AD8C00AD947B00AD734A00945A31009C8C7B009C947B009494
      8C00000000000000000000000000000000000000000000000000000000000000
      000000000000FFFFFF002994FF002994FF000063E7000042C600FFFFFF000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000ADA59400B584
      5A00CE8C6300D69C7300CE9C7B00CE9C7B00D69C7B00D6A57B00D6A58400DEAD
      8400B58C8400846B8C00735A9400735A8C009C7B9400D6AD9C00E7BD9C00DEBD
      A500E7BDA500EFCEAD00CEB5AD00947BA5007B6BA5007B73A5009C8CB500B584
      6B00C6C6BD0000000000000000000000000000000000DED6C600F7F7E700FFF7
      EF00F7F7E700EFDEAD00EFE7BD00F7EFD600EFD6BD0094CEDE0008C6FF0008CE
      FF0018BDF70000DEFF0031E7FF007BD6E70021DEF7006BE7F700F7F7EF00EFF7
      EF0094DEE700B5D6D600DED6C600FFF7DE00DEDECE005A5A5A0084847B00CEBD
      A500F7DEAD00EFDEAD00E7D6AD00000000000000000000000000000000000000
      000000000000000000000000000000000000000000006B84BD00426BD6002952
      BD00395AAD000000000000000000000000000000000000000000000000000000
      000000000000A59C8C00DEC67300D6B56B00BD9C5A00BD9C5200A59473000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000FFFFFF002994FF000063E7000063E700FFFFFF00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000D6D6
      D600BDB5AD00A5846B00CE946300D6A58400DEAD8C00D6AD8C00D6AD8C00DEAD
      9400DEB59400E7BD9400E7BD9C00EFC69C00E7C6A500E7BDA500E7BDAD00E7C6
      AD00E7C6B500E7CEB500EFCEBD00F7D6BD00F7DEC600FFE7CE00F7C69C00AD9C
      94000000000000000000000000000000000000000000DED6C600F7F7E700FFF7
      EF00F7F7E700EFDEA500EFE7BD00F7EFCE00F7EFCE00C6D6D6005ACECE0042C6
      8C0021A5EF0008CEFF005ADEF70073E7F70000E7FF0000DEFF00B5E7EF00F7E7
      DE00DECEC600EFDED600DECEBD00E7DECE00EFE7D60094948400A59C8C00EFDE
      B500E7D6A500EFDEA500E7DEAD00000000000000000000000000000000000000
      000000000000000000000000000000000000000000007B8CA500396BDE00294A
      AD006B7B9C000000000000000000000000000000000000000000000000000000
      000000000000ADA58C00DEBD7B00DEBD7300CEAD6300BD9C4A009C947B000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000FFFFFF00FFFFFF00FFFFFF00FFFFFF0000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000C6B5AD00B5948400BD946B00D6A58400DEB59400DEBD
      9C00DEB59C00DEBD9C00DEBDA500DEBDA500E7C6AD00E7C6AD00E7C6B500E7CE
      B500E7CEBD00EFCEBD00EFD6C600EFD6C600EFDECE00F7DECE00BD947300D6D6
      D6000000000000000000000000000000000000000000E7DEC600F7F7E700FFF7
      EF00F7F7E700EFDE9C00F7E7C600F7F7E700F7EFD600FFEFDE00BDDEBD0063CE
      94008CDEE700B5DEE700DED6CE00ADD6DE0000D6FF005ADEF700DEDEDE00E7DE
      CE00CEC6B500E7D6C600D6CEBD00D6C6AD00E7D6BD00CEBD9C00BDAD8C00DECE
      A500DECE9C00E7D6A500E7D6AD00000000000000000000000000000000000000
      0000000000000000000000000000848CA5004273D600296BE700296BEF005284
      EF006394DE00638CC6008C949400000000000000000000000000000000000000
      0000A59C8C00B5AD8400BDB58C00DEBD8400CEAD6300AD9C7300A59473009494
      8400000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000CECECE00BDAD9C00B5947B00CE9C
      7300E7B59C00E7C6AD00E7C6B500E7C6B500E7CEB500E7CEBD00EFCEBD00EFD6
      C600EFD6C600EFDECE00EFDECE00EFDED600F7E7DE00D6AD8400C6C6BD000000
      00000000000000000000000000000000000000000000EFE7C600F7F7E700FFF7
      F700F7F7E700EFDE9C00EFDEA500EFE7B500EFE7BD00F7E7C600F7EFCE00EFEF
      D600FFEFD600FFEFD600F7EFD600D6EFE7004ACEF700C6DEDE00FFEFDE00F7EF
      DE00EFE7CE00EFE7CE00EFE7C600E7D6B500EFDEAD00D6CEB500D6CEB500EFDE
      A500EFDEAD00EFDEA500E7D6AD00000000000000000000000000000000000000
      00000000000000000000000000004A7BCE00216BF7002173F7002173F7002973
      F7004284F700397BF700738CAD00000000000000000000000000000000000000
      0000000000000000000000000000B5A57B00BDA5730000000000000000009494
      8C00000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000C6BD
      B500BD947300CEA58400E7BDA500EFD6BD00EFD6C600EFD6C600EFD6C600EFDE
      CE00EFDECE00EFDED600F7DED600F7E7DE00F7DEC600B5948400000000000000
      000000000000000000000000000000000000C6C6BD00F7E7C600F7F7E700FFF7
      F700F7F7DE00D6CEAD00D6CEAD00D6CEB500DED6B500DED6BD00D6CEBD00DED6
      C600EFE7CE00F7EFCE00F7EFD600FFEFD600EFEFD600F7EFD600F7EFD600F7EF
      CE00F7E7CE00EFE7C600DED6BD00D6D6B500E7D6AD00CECEB500D6CEB500EFDE
      A500EFDEA500EFDEA500DED6AD00000000000000000000000000000000000000
      000000000000000000008C9494003984DE002194F700189CF700189CF700218C
      F7002173F7002163EF006384BD00000000000000000000000000000000000000
      00000000000000000000000000000000000094948C0000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000CEC6C600BDA59400CEA58400DEB59C00EFD6C600F7E7DE00F7E7
      DE00F7E7DE00F7E7DE00F7E7DE00FFEFE700C69C7B00CECECE00000000000000
      00000000000000000000000000000000000000000000D6CEBD00EFE7DE00F7F7
      EF00E7DED6000000000000000000000000000000000000000000000000000000
      0000C6C6BD00C6C6BD00C6C6BD00CEC6C600CECEC600CECEC600CEC6BD00C6C6
      BD00C6C6BD00C6BDBD00000000000000000000000000C6BDBD00C6C6B500CEC6
      B500CECEB500CEC6B50000000000000000000000000000000000000000000000
      000000000000000000000000000073A5DE00BDE7FF007BDEFF0018C6FF0018A5
      F7002184F700216BF7006B84B500000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000C6BDBD00C6A59400D6A57B00EFDE
      CE00FFEFE700FFEFEF00FFF7F700E7C6A500BDADA50000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000007394B500A5D6F700DEFFFF009CE7FF0031AD
      FF002184F7003173E700848C9C00000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000CEC6C600C6AD
      9C00CEAD9400E7CEBD00EFCEBD00BD947B000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000084949C0073A5C60073ADDE005A9C
      D6006B8CBD008C94940000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000DEDED600CEBDB500CEB5AD00D6D6D6000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000B5B5B500ADADAD00C6C6BD00B5B5AD00849C9C008CAD
      B5007B949C0094ADB50094A5A500A5ADB500CECECE0000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000ADADAD0094949400949494009C9C
      9C00B5B5B5000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000D6D6D600B5B5AD00D6CEC600C6C6BD0063D6D6005ADE
      E7005ABDDE005AB5D6005AB5D6005AB5CE009CADAD0000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000B5B5B500ADADAD00A5A5A5006B73840084C6CE008CCED6005A84
      AD0063636B007B7B7B008C8C8C009C9C9C00A5A5A500ADADAD00B5B5B5000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000C6C6C600BDBDB500BDBDBD008C9CA500738C94004AA5A50052C6C60052C6
      C6004AADB5004A94AD0052A5BD0052ADC600C6C6C60000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000B5B5
      B500ADADAD00A5A5A5008C8C8C007B7B7B005A7B94009CF7FF009CF7FF0063A5
      E700525252005A5A5A00636363007373730084848400949494009C9C9C00ADAD
      AD00B5B5B500B5BDB50000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000CECE
      CE00A5A59C00F7EFE7008CA5A5004AA5C600428C9C0052C6BD005ADEDE005ADE
      DE005AD6D60052ADC60052A5B5004A949C00BDBDBD00D6D6D600000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000B5B5B500B5B5
      B500A5A5A5009C9C9C008C8C8C00848484005A7B94008CDEFF008CDEFF005A9C
      D600525A5A00636363006B6B6B0073737300848484008C948C00949C9400A5A5
      A500ADADAD00B5B5B500B5B5B500000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000039313100393131003931
      3100393131003931310039313100000000000000000039313100393131003931
      3100393131003931310000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000ADADAD008C8C8C005AC6C60052CECE0052BDBD0063EFEF0063EFE70063EF
      E70063E7E7005ABDD6005AB5D6005AADC6005A949C00639CA50073949C008CA5
      AD00B5BDBD00CECECE0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000B5BDB500B5B5
      B500ADADAD00A5A5A5009C9C9C00949494005A7B940084D6FF0084D6FF005294
      C600636B6B0084848400848484008C8C8C00949494009C9C9C009C9C9C00A5A5
      A500ADADAD00B5B5B500B5B5B500000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000002121210021212100212121002121210021212100212121002121
      2100000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000039313100847B7300948C8400E7DE
      C600E7D6CE00F7E7DE00E7D6CE00393131003931310042637B00739CBD00739C
      BD00739CBD0039637B003931310039313100393131005A524A00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000D6D6D60094B5B5004AB5AD005AD6D6005ADEDE005ADED6005ADE
      DE005ADED6005AB5C60052ADC60052ADC6004A94AD005AB5CE004A9CB5005AB5
      CE005AB5CE0052849400A5ADAD00D6D6D6000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000B5B5
      B500B5B5B500B5B5B500ADB5AD00ADADAD005A7B94008CD6FF0094D6FF005A8C
      BD00737B7B00A5A5A500A5A5A500A5A5A500A5A5A500ADADAD00ADADAD00ADB5
      AD00B5B5B500B5B5B500B5BDB500000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000002121
      2100212121002118DE002118DE001810C6001810C6001810C6004242EF002118
      D600212121002121210000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000039313100847B7300AD9C8C007363
      6300BDAD9C00AD9C8C00B5A59400C6B59C00394A4A00739CBD00294A73003152
      840018316B00315A7B005284A50039313100D6C6BD005A524A00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000BDB5BD006B9C9C004ABDBD004AADAD0052CEC60052C6
      C60052C6C600428C9C004A94A5004A9CAD0042849400428494004A94A5004A94
      AD005AB5D60052A5BD0052ADC6006B9CAD00B5B5B50000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000B5B5B5005A738C007BBDEF007BBDEF005A84
      AD007B84840000000000B5B5B500B5B5B500B5B5B500B5B5B500B5B5B5000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000212121003931
      E700635AEF00635AEF0018109C0018109C0018109C0018109C0018109C001810
      B5004242EF002118D60021212100000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000393131007B7B6B007363
      63009C8C8400ADA5940073635A008C7B6B0042525A00739CBD00315284003163
      AD00214A8C0018395A0039637B0039313100A5948C005A524A00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000D6D6D600BDC6C6008CCECE0052DEDE0052CEC60063F7EF0063EF
      E70063EFEF004AA5B5005AB5CE005AB5CE004A94AD004A94A500428C9C003973
      7B004A94A5004A8CA5005AB5CE005ABDD60052A5BD009CADAD00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000B5BDB5005A6B84006394BD006394BD005273
      94007B8484000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000212121008C8C
      F700635AEF0018109C001810B5002118E7002118DE002118DE001810B5001810
      9C0018109C004242EF0021212100000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000393131005A4A
      4200AD948C00BDA594008C736B0021101800213139004A739400395A8C00315A
      A500214A8C002139630039637B00423131005A524A0039313100000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000BDC6C600E7FFFF009CCEC6004ACEC6004ABDB5005ADEDE005ADE
      D6005AD6DE004A94A50052A5BD005AB5C6004A94A50052A5B50052ADC6004A94
      A5005AADC6004A94AD005AB5CE005AB5CE005AB5CE004A94AD0094ADAD000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000B5B5B500526B7B005A84AD005A8CAD004A73
      94007B8484000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000212121003931E700ADBD
      EF001810B5002118E7002118E7003931E7003129E7003129E7002118DE002118
      D6001810B5001810B5002118D600212121000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000393131003121
      1800393131003131390029292900182121001821310029425A0029427300315A
      A500214A8C0018395A0010182100393129003931310000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000C6D6D600EFFFFF00BDD6D6004AB5B50052C6C60052CEC60052CE
      C60052B5BD004A94A5004A9CAD004A94A50031737B0052ADC60063BDD6004A9C
      AD0052ADBD004A9CB5005AB5CE005AB5CE0052ADC6004A94AD0052B5CE009CAD
      B500000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000B5B5B5004A5A7300527BA500527BA5004A6B
      8C0073737B000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000212121008C8CF700635A
      EF002118E7004A42EF002118E7004242EF004242EF004242EF004242EF004242
      EF002118D60018109C0018109C00212121000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000182921002942
      5A0042638400527B94005A7B94005273940042637B0010101800183963002952
      940018427B001829420010182100424A52001829210000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000CECECE00B5BDBD00B5C6C600C6D6D6007BC6C60063F7EF0063EFE70063EF
      E7005ACED6005AB5D60063BDDE004A94AD004A94A5004A94A5005AB5D6004AA5
      B50052C6C6004AADAD005ACED6005ABDD60052A5B500428C9C004294A50052AD
      C6009CB5B5000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000ADADAD00425A6B0052739400527394004263
      7B006B6B73000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000212121003931E700635A
      EF00ADA5F700ADA5F700C6BDFF00CECEFF00CECEFF00CECEFF00C6BDFF00ADA5
      F700524AEF002118D60018109C00212121000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000182921003963
      840029425A001029520018396B0029427B00527B9C004A638400182939001831
      630010294A0010182100395A6B006384AD001018210000000000000000000000
      000000000000000000000000000000000000000000000000000000000000ADB5
      AD00737B7B0073948C0042949C005AA5BD004A8484004ABDB50063F7EF0063E7
      DE005ABDD6005AB5D6004A9CAD004A9CAD005ABDD60052A5B500428C9C0052AD
      BD0052C6BD004AADAD004AB5B50052B5BD004A9CA5005AB5CE0052A5BD004A94
      AD0042849400ADC6CE0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000B5B5B500525A6B004A6B840052739400527394004A6B
      8C00425A6B007B84840000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000021212100F7BDA5008C8C
      F700ADA5F700ADA5F700ADA5F700ADA5F7008C8CF7008C8CF7008C8CF7008C8C
      F700ADA5F700736BEF00D69CA500212121000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000001029
      310010214A001831630021427B0021427B0010214200425A7300213139002121
      21002929290039526B00315A7B00101821000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000CECECE00A5AD
      AD004A7B8C0063ADAD0063DEE70052A5BD00428CA5004A94A5004AADAD0052B5
      C600529CB50042949C004A9CAD005AB5D6005AB5CE005AB5CE00428494004A9C
      AD0042A5A50063EFE70063E7E70052C6C6004AADAD0063E7DE005AC6D6005AB5
      CE00428494004A94A500D6D6D600000000000000000000000000000000000000
      000000000000B5B5B500ADADAD00B5B5B5000000000000000000000000000000
      00000000000000000000A5A5A500395263004A739400527B9C00527B9C004A73
      9400425A730052637300ADADAD00000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000021212100D69C
      A5008C8CF7008C8CF7008C8CF7008C8CF7008C8CF7008C8CF7008C8CF7008C8C
      F700736BEF00D69CA50021212100000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000018213100101018000810180008101000080810000810180010101800C6AD
      A500F7DED6003939390008183900000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000A5B5B5006B9C
      9C0063737B0063ADAD0063EFE7004AB5B5005ABDCE005AB5D6004A94AD00316B
      7B00428C9C004AADB50052BDBD005AB5C6005ABDD6004A9CB50052ADBD004A94
      AD006B9C940073BDBD0063CEC60052C6BD005ADED60063F7EF0063EFE7005AC6
      CE004A94AD005AB5CE009CADAD00000000000000000000000000000000000000
      0000B5B5B500636B73005284A5006B7384000000000000000000000000000000
      000000000000B5BDB5005A738400425A7300527394005A84AD005A84AD005273
      9C004A6B8C007BB5DE00737B8C00000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000021212100F7BD
      A5006B63EF00635AEF00635AEF00635AEF00635AEF00635AEF00635AEF00635A
      EF006B63EF00D69CA50021212100000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000101018001831520021396300294A7300294A6B0008183100425A7300848C
      9C0084848C00394A520010295200000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000A5B5B50073BD
      B5006B848C006B9C9C0052CEC60052CEC60063EFE7005AC6D6005AADC600428C
      9C004A94A5005AC6D6005ADEDE00429C9C0052A5B5004A94AD005AB5CE005AA5
      BD00D6D6D600D6D6D600CECECE00A5ADAD008CB5B5006BCECE0063EFE70052C6
      BD0052B5C6005ABDDE005A8C9400D6D6D6000000000000000000B5B5B5009494
      9400737373004252630063A5E700526B8400A5A5A500B5B5B500000000000000
      000000000000B5B5B500527B9C0042637B00527B9C005A8CB5005A8CB500527B
      A5004A6B8C0084CEF70073848C00000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000002121
      2100F7BDA5000000000000000000000000000000000000000000000000000000
      0000F7BDA5002121210000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000005A524A005A524A005A524A0000000000000000001031
      18001831520021427B00315A9400396394004A7394008CADCE00739CBD00314A
      630018314A008CADCE003963940029394A000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000D6D6D60052CE
      C60052ADB500ADBDC6004A9C9C004AB5AD0063EFE70063EFEF004AADB50052AD
      C6005AADC600428C94005ADED6004AADB5004AB5B500428494005ABDDE006BA5
      B5000000000000000000000000000000000000000000D6D6D600A5B5B50052AD
      A50063F7EF005ABDD600428C9C00B5B5B50000000000B5B5B5009C9C9C007B7B
      7B006363630042526300639CCE00526B7B0094949400ADADAD00000000000000
      000000000000B5B5B50052738C0042637B005284A500638CB500638CB5005A84
      A5004A73940084C6EF0073848C00000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000021212100F7BDA500FFFFFF00FFFFFF00000000000000000000000000F7BD
      A500212121000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000005A524A00AD9C9C00EFD6C600FFFFEF005A524A00000000001829
      3100314A6B004A63840042637B006384AD008CADCE005A7B9C004A6384006384
      AD0039526B008CADCE00638CB50029394A000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000BDBDBD009CBD
      BD00529C9C00A5C6C60094C6C6004ABDBD0052BDBD005ADEDE004AA5A5004A9C
      AD005AB5CE004A9CAD0052C6BD0052ADBD0063EFE7004AA5B5004294A50094B5
      BD0000000000000000000000000000000000000000000000000000000000C6C6
      C6008CBDB50052B5B5004AADBD0094A5AD0000000000B5B5B5009C9C9C008484
      84007373730042525A004A84AD004A637300A5A5A500B5B5B500000000000000
      000000000000B5B5B5004A6B8C00426384005A84AD006394C6006394C6005A84
      AD004A73940084C6E7006B848C00000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000021212100F7BDA500FFFFFF000000000000000000F7BDA5002121
      2100000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00005A524A00EFD6C600FFFFFF00C6B5AD00CEB5AD00FFFFEF005A524A001821
      290039526B00527394005A7B9C00527394004A6384008CADCE00BDE7FF00B5DE
      FF009CC6E7005A739C008CADCE0039527300736B6300736B6300182918000000
      00000000000000000000000000000000000000000000C6CECE00D6EFEF00EFFF
      FF00A5CECE007BA5A500DEEFEF0073C6C60052CECE00429C9C0063DEDE0052BD
      C60042849400429C9C004AADB5005ACED60063EFE7005ABDD60039849400BDC6
      C600000000000000000000000000000000000000000000000000000000000000
      000000000000A5B5B5004AA5B5006B9CA50000000000B5B5B500A5A5A500949C
      940094949400424A5200395A730042525A00B5B5B50000000000000000000000
      000000000000B5B5B5004A6384004A6B8C006394C60073ADDE006BA5D6006394
      BD00527394007BBDDE006B848C00000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000021212100D69CA500FFFFFF000000000000000000D69CA5002121
      2100000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000073635A00BDA59400A58C8400FFFFF700EFD6C600B5A59400E7D6C6003129
      210018293900314A6B00314A6B008CADCE00BDE7FF00BDE7FF009CC6DE008CAD
      CE007394B500638CB5004A6B9400183152006B636B00FFFFEF009C8C84001829
      18000000000000000000000000000000000000000000C6CECE00E7FFFF00DEF7
      F700DEF7F700A5B5BD00B5C6C60094ADAD004AA59C0052D6CE0063EFE70063E7
      E7004AADB50052CEC6004AADAD0052BDBD0063EFE70052BDC6005A949C000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000ADB5B50063848C000000000000000000000000000000
      0000A5A5A5002931390021394A0031394200A5A5A50000000000000000000000
      000000000000B5B5B5004A637B004A739C006BA5DE0084BDF7007BBDF7006BA5
      D600527BA50073B5D6006B848C00000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000021212100000000000000000000000000212121000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00004231290073635A00CEB5AD00CEB5AD00FFFFFF00D6C6BD00B5A594007363
      630021395A004A6B94006384AD007B9CC60063849C00425A7B005A738C006B84
      9C004A638400294263005273A500314A6B00948C8400C6ADA500847B6B004A4A
      520000000000000000000000000000000000BDC6C60084ADAD00DEEFEF00E7FF
      FF00DEF7F700DEF7F700BDCED600C6CED6006B8C94004AC6BD006BF7EF005AD6
      CE0052C6C60063F7EF005ADEDE004AADA50052BDBD00429CAD009CADAD000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000C6C6C6000000000000000000000000000000
      00005A636B0029425200314A6B0029425A005A63630000000000000000000000
      000000000000B5B5B50042637300527BA50073B5EF008CD6FF008CD6FF0073AD
      E7005284AD0073ADCE006B849400000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000021212100000000000000000000000000212121000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000004231290084736B00B5A59400CEB5AD00F7E7DE0094847B005A39
      31000808210018395200314A6B00294263005A738C0084A5C6006B849C00637B
      8C0094B5CE005273A500314A6B0021426300847B7300BDAD9C004A4A52000000
      0000000000000000000000000000000000008CBDBD0052DED60073B5B500D6E7
      E700E7FFFF00E7FFFF00D6EFEF00CEDEE7008CADB50042949C004ABDB50042A5
      A50063E7DE0063EFE70052BDBD0063E7DE005AD6CE00428C9400CECECE000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000B5B5
      B50052738C00395A7B00395A7B0031526B0042525A00B5BDB500000000000000
      000000000000B5B5B500425A73005284B50073BDF7009CE7FF009CDEFF0073B5
      F700528CB5006BA5CE006B849400000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000021212100000000000000000000000000212121000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000423129008C737300B5A59400CEB5AD008C736B002921
      29002139520010213900001029005A7B9400A5C6DE00314A5A00212942002129
      420029394A0094BDD60039526B0018314A005A52520094947B00000000000000
      00000000000000000000000000000000000063B5B5006BFFF70052C6CE00739C
      A500C6D6D600B5CECE00DEF7F700D6DEE7007BA5B5004A9CB500428C940052CE
      CE0052C6C6005AD6CE0052C6BD0063EFE7005AEFE7008CB5B500000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000B5B5
      B50052738C00426B8C004A739C0042638C0042526300B5BDB500000000000000
      000000000000B5B5B50042637B005A94C60073BDFF009CEFFF009CEFFF0073BD
      F700528CBD0063A5CE006B849400000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000021212100D69CA50000000000D69CA500212121000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000423129008C7373005A42390042424A003963
      84008CB5DE004A63840018395200BDE7FF003142520029394A00394A5A004252
      6B00182131008CADC60021293100101831007B736B004A4A5200000000000000
      00000000000000000000000000000000000063ADA5005AD6CE004AB5B5004A9C
      AD002942420008080800394242009CADB5005AA5B50052ADC60052A5B50063EF
      EF0052C6C60042A5A50063EFE70063EFE70063CECE00D6D6D600000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000B5B5
      B500526B84004A739C005284B5004A7BA500425A6300B5BDB500000000000000
      000000000000B5BDB5005A6B840063ADEF0084D6FF00A5F7FF00A5F7FF007BD6
      FF0063A5E7005A94BD00848C9400000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000021212100734239007342390084394200212121000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000001018180008101800294A7300A5CE
      EF00BDE7FF00183952009CC6E7007394AD0021294200394A5A00394A63003142
      52002939520094BDD6004A637B006B8CAD002129310000000000000000000000
      0000000000000000000000000000000000005A94940052CEC6005ADEDE0063CE
      DE0029526300000000000000000029525A005AC6DE0052A5BD0052ADBD0063EF
      E70063EFE7004AADAD0052CEC6005AE7DE00ADC6C60000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000B5B5
      B5004A6B84004A7BAD00639CCE00528CB5004A5A6B00B5BDB500000000000000
      000000000000000000009CA5A500639CD60084E7FF009CFFFF009CFFFF0084DE
      FF006BB5F7005A6B840000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000002121210000000000E7FFFF000000000000000000C6C6CE002121
      2100000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000008102100395A8C008CB5D600CEEF
      FF008CADC60018395200B5DEFF0031425A0039425A00394A6300394A63002129
      3900526B8C00A5CEEF006B8CA500849CB5002129310000000000000000000000
      0000000000000000000000000000000000006BB5AD006BFFF7005ADEDE005AC6
      CE0042849C0021212100211818001842420063D6DE004A94AD005ABDCE0063EF
      E70063F7EF0052BDBD00398C9C0094B5B5000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000B5B5
      B5004A637B004A84B5006BADE7005A94C600425A6B0000000000000000000000
      0000000000000000000000000000949C9C006B8494005284A5004A84AD005A7B
      940073848C00ADADAD0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000021212100DEC6CE00AD9CA500104A7B00AD9CA500000000002121
      2100000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000008102100526B8C006384
      A50018395200A5CEE700212931002129310031394A0029314200293139002129
      31008CB5D6004A637B00849CB500212931000000000000000000000000000000
      00000000000000000000000000000000000084A5A50063F7EF0063E7DE005ACE
      CE0052C6CE0073A5A5007B8C84003184840063EFE7004AADB50063E7DE0063EF
      E70063E7DE004AB5BD005ABDBD00D6D6D6000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00007B848400426384004A7BA5004A6B8C0084848C0000000000000000000000
      0000000000000000000000000000B5B5B500525A630042638400396384003952
      63008C9494000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000021212100104A7B00106BCE00104A7B00212121000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000081021000810
      2100212931002129310000000000000000000000000000000000000000002129
      3100212931000810210021293100000000000000000000000000000000000000
      000000000000000000000000000000000000B5BDBD005AD6CE0063EFE7004ABD
      B5004AB5B5005ADED6005ADEDE0063EFE7005ADED60052CEC60052BDBD005AC6
      D60052B5B5004ACECE00A5C6C600000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000B5B5B5004A525A00315273005A636B000000000000000000000000000000
      00000000000000000000000000006B7373005A84B50073ADDE006BA5D6005A8C
      B50042526B00ADADAD0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000212121001094D6001094D600106BCE00212121000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000739C9C0052CECE004AA5
      A50052CEC60063F7EF005ADED60063E7DE0052BDB500529C9C0052A5BD004284
      94004AC6BD006BC6C600D6D6D600000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000848C8C00426B8C0063A5D600426B9400A5A5A50000000000000000000000
      0000000000000000000000000000526B7B006BB5F70094E7FF0094DEFF006BAD
      E700426B8C008C8C8C0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000212121002121210021212100000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000C6C6C60063B5B50063F7
      F7004AADAD0052C6C60063E7DE0052CEC60052A5A50073ADAD0052ADBD00317B
      84005AC6BD00CECECE0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00008C8C8C00426B94006BADE70042739C00A5A5A50000000000000000000000
      0000000000000000000000000000527394007BCEFF00A5F7FF009CEFFF0073BD
      FF004A7BAD00848C8C0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000BDBDBD006BAD
      A50063E7DE0052BDC6004AADB5004ABDBD0073B5B50084B5BD0042A5AD00639C
      9C00BDBDBD000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000B5B5B50063737B00526B8C00737B84000000000000000000000000000000
      00000000000000000000000000006B7B8C0084DEFF00ADFFFF00A5FFFF007BD6
      FF00527BAD00A5ADAD0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000D6D6
      D600849494006BC6BD004AA5A50052D6CE005A9C9C005AADAD006B949C00CECE
      CE00000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000ADADAD006B94B5008CE7FF008CE7FF006BAD
      DE007B848C000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000D6D6D600B5B5B500A5ADAD009CA5A5008CADB500D6D6D6000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000B5B5B50084949C0084949C009C9C
      A500000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000424D3E000000000000003E000000
      2800000080000000E00000000100010000000000000E00000000000000000000
      000000000000000000000000FFFFFF00E001E7FF000000000000000000000000
      E00007FF000000000000000000000000E00007FF000000000000000000000000
      E00007FF000000000000000000000000E0000FBF000000000000000000000000
      E000063F000000000000000000000000E000003F000000000000000000000000
      F000003F000000000000000000000000FC00003F000000000000000000000000
      FF00007F000000000000000000000000F800007F000000000000000000000000
      F00000FF000000000000000000000000E00000FF000000000000000000000000
      C00001FF000000000000000000000000800000FF000000000000000000000000
      0000000300000000000000000000000080000003000000000000000000000000
      8000000300000000000000000000000080000007000000000000000000000000
      800000070000000000000000000000008000000F000000000000000000000000
      8000003F0000000000000000000000008000007F000000000000000000000000
      800003FF000000000000000000000000C00001FF000000000000000000000000
      8000007F00000000000000000000000080000003000000000000000000000000
      800000070000000000000000000000008000000F000000000000000000000000
      8700001F000000000000000000000000FFC0007F000000000000000000000000
      FFF801FF000000000000000000000000FFFFFFFFFFFFFFFFFF03807FFFFFFFFF
      FC007FFFFFFFF0FFFC00003FFFC003FFF8003FFFFE0FE07FF800001FFF0000FF
      F800201FF803C03FF800001FFE00007FF800000FF001C03FF000001FF800001F
      F8000007E000C03FC000001FF800001FF8000007C000403F8000001FF000000F
      F8380007C010003F8000001FE0000007F83801078008001F0000001FC003C003
      F80003078000000F00000007C003C003F80000078004000700000003C003C003
      F803F807000000030000000180000001F803F807000000018000000180000001
      F803F807000000018000000080018001F003FC0F00000000C000000080018001
      E001FC1F00000000F008200080018001E001F80F00000000F000000080018001
      E001F80F10000000F00420018003C001E000000F10000000F00100018003C001
      E068000F00000000F80000038003C001E078000F00000001F800001F8003C001
      E078000F00000001F800001FC003C003E078080F80000003FC00003FC0000003
      E078001F88000007FF00007FE0000007E0003FFFC000000FFFC007FFE0000007
      E0003FFFC0107FFFFFC007FFF000000FE0003FFFE021FFFFFFE10FFFF800001F
      E0003FFFF003FFFFFFF00FFFFC00003FF0007FFFF80FFFFFFFF83FFFFE00007F
      FFFFFFFFFFFFFFFFFFFFFFFFFF8001FFFFFFFFFFFFFFFFFFFFFFFFFFFFF00FFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0F87FFFFFFFFFFFFFFFFFF
      FFFFFFFFFF870FFFFFF03FFFFFFFFFFFFFFFFFFFFFC21FFF80000003F800001F
      FFFFFFFFFFE03FFF80000003C0000003FFFFFFFFFFF07FFFFFF03FFF80000003
      E0000003FFF03FFFFFFC7FFF80000001C000000180000003FFFC7FFF00000000
      8000000080000003800000070000000080000000FF800FFF0000000300000000
      87FFFFF0FF0C07FF000000034000000180000000FFFC7FFF0000000180080001
      8000000080000007000000018040000180000000000000030000000080000001
      800000000000000300000000800000018788047800000001000000009E000019
      8780007800000001000000009800000987808078000000000000000082000039
      878008780000000000000000C0000001878000F80000000000000000C2000003
      870804F80000000000000000CC00003B800000000000000080000000E60000F3
      8000000000000000C0000000F00000078000000000000000F0000000FF2000CF
      8000000000000000FC000000FF0000FF87FFFFF080000000FFFFFFFFFFC001FF
      C0000001E0000000FFFFFFFFFFC003FFF8000007F8000000FFFFFFFFFFC003FF
      FFFFFFFFFE000000FFFFFFFFFFC003FFFFFFFFFFFFFFFFFFFFFFFFFFFFE003FF
      FFFFFFFFFFFFFFFFFFFFFFFFFFE007FFFFFFFFFFFFFFFFFFFFFFFFFFFFF80FFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFC003FFFFFFFFFFFFF81FFFFFFFBFFFFF0000FFFFF7FFFFFFE007FF
      FFF00FFFFE00007FFFC1FFFFFF8001FFFFE00FFFFC00001FFFC0FFFFFF0000FF
      FFE007FFF800001FFF807FFFFF0000FFFFE007FFF000000FFF007FFFFE00007F
      FFE007FFE0000007FE003FFFFE00003FFFE007FFE0000003FE001FFFFC00003F
      FFE007FFC0000003FC001FFFFC00003FFFE00FFFC0040003F8000FFFFC03C03F
      FFE00FFF800E0001F80007FFFC00003FFFE007FF801F0001F00007FFFC00003F
      FFE007FF803F8001E00003FFFC00003FFFE003FF8079C001E00001FFFC00003F
      FFE001FF8030E001C00001FFFE01803FFFE000FF80007001E00000FFFE00007F
      FFF0007F80003801E000007FFE00007FFF00003F80001C01F098007FFF0000FF
      FC00003F80000C01FC18003FFF0380FFFC00003F80000001FFFC001FFF0000FF
      FC00003FC0000003FFFE001FFF0080FFFC00003FC0000003FFFF000FFF0000FF
      FC00003FE0000007FFFF000FFF0008FFFC00003FE0000007FFFF800FFF9009FF
      FE00007FF000000FFFFFC00FFF8001FFFF00007FF800001FFFFFC01FFFC013FF
      FF00C0FFFC00003FFFFFE03FFFE3C7FFFFC001FFFE00007FFFFFF07FFFF00FFF
      FFE007FFFF8001FFFFFFF8FFFFFFFFFFFFFE3FFFFFF00FFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFC000003FFFFFFFFFFFFFFFFFFF81FFF
      E0000001FFFFFFFFFFFFFF87FF0000FF80000000F800003FFFFFFF01F000000F
      00000000F000001FFFFFFC01C000000300000000F000000F8000000080000003
      00000000E000000F00000040F800001F80000101E000000F00000080FF8001FF
      F0000103E000000F00000001FF0000FFFC000007E100020F00000001FE00007F
      FC00001FE000000F0FFF8001FC00003FFC00001FE000000F00000001F800001F
      FE00003FE000000F00000001F000000FFE00003FE000000F00000001E0000007
      FE00007FE000000F00000001C0000003FC00007FE000000F0000000180000001
      F800007FE000000F0000000100000000E00000FFE000000F0000000100000000
      C00000FFE000000F0000000180000001800001FFE000000F00008001C0000003
      000001FFE000000F00000001E0000007000001FFE000000F00000001F000000F
      000003FFE000000F00000001F800001F800003FFE000000F00000001FC00003F
      C00003FFE200000F00000001FE00007FF00007FFE300028F00000001FF2004FF
      F80007FFF03FF01F00000001FF9819FFFC0007FFF800003F00000001FFCFF3FF
      FF000FFFFFFFFFFF1FFFFF03FFE7E7FFFF800FFFFFFFFFFF00000003FFF3CFFF
      FFE01FFFFFFFFFFF80000007FFF99FFFFFF81FFFFFFFFFFFF000003FFFFC3FFF
      FFFC3FFFFFFFFFFFFFFFFFFFFFFE7FFFFFFFFFFFE0001FFFFFFFFFFFFFFFE7FF
      FFFFFFFF800007FFFFFFFFFFFFFF83FF03FFFFE0000003FFFFFFFFFFFFFF81FF
      00FFFFC0000001FFFFFFFFFFFF8E00FF003FFFC0000003FFFFFFFF7FFF06007F
      0000000000000003FFFFFE3FFF00003F0000000000000000FFFFFE1FFE00001F
      0000000080000000FFFFCC3FFC00000F0000000080000000FFFF80FFFC000007
      00000000C0000000FFFFC1FFF800000300000000C0000000FFFF81FFF8000001
      00000000E0000000FFFE00FFF000000000000000E0000001FFFC00FFE0000000
      00000000F0000003FFF805FFE000000000000000F0000003FFF00FFFC0000000
      80000001F8002007FFE00FFFC000000080000001F8006007FFC01FFF80000000
      80000001FC00700FFF803FFF0000000080000001FC00F00FFF007FFF00000000
      80000001FE00F80FFE00FFFF0000000080000001FE01F81FFC01FFFF80000001
      80000001FE01FC1FF803FFFFC000000380000001FF01FC3FF007FFFFC0000007
      80000001FF03F80FF00FFFFFC000000780000001FF87F81FF01FFFFFE000000F
      80000001FF87F81FF03FFFFFFC00000F80000001FE01F00FF07FFFFFFF00001F
      80000001FE01FE6FFFFFFFFFFFE0003F00000001FC01FF7FFFFFFFFFFFF8003F
      87F00383FE01FFFFFFFFFFFFFFFF007FFFFFFFFFFE01FFFFFFFFFFFFFFFFC0FF
      FFFFFFFFFF03FFFFFFFFFFFFFFFFF0FFFFFFFFFFFFFFFFFFFC007FFFFFFF07FF
      FFFFFFFFFFFFFFFFFC007FFFFFF8001FFFFFFFFFFFFFFFFFF0007FFFFFE00003
      FFFFFFFFFFFFFFFFE0003FFFFFC00001FFFFFFFFFF8183FFF00003FFFFC00001
      FFF80FFFFF00003FF80000FFFFE00001FFE003FFFF00003FFC00007FFFFE041F
      FFC001FFFF80003FF800003FFFFE07FFFFC001FFFFC0003FF800001FFFFE07FF
      FF8000FFFFC0007FF800000FFFFE07FFFF8000FFFFC0007FF0000007FFFE07FF
      FF8000FFFFC0007FE0000003FFFC03FFFF8000FFFFE000FFC0000001F8FC01FF
      FFC001FFFFF001FFC0000001F0F801FFFFC001FFFFF001FFC0000000C03801FF
      FFE7F3FFFC6000FFC0000F80803801FFFFF0E7FFF82000FFC0000FE0803801FF
      FFF8CFFFF000001F80000FF8807801FFFFF8CFFFF000000F80001FFCF07801FF
      FFFDDFFFF000000F00001FFEF07801FFFFFDDFFFF800001F00001FFFE03801FF
      FFFDDFFFFC00003F00003FFFE03801FFFFFC9FFFFE00003F00003FFFE03801FF
      FFFC1FFFFF00007F00007FFFE03C03FFFFFACFFFFF00007F0000FFFFE07E03FF
      FFF82FFFFF8000FF0000FFFFF07E07FFFFFC1FFFFFC3E1FF0001FFFFF0FE03FF
      FFFC1FFFFFFFFFFF8001FFFFF07E03FFFFFE3FFFFFFFFFFF8003FFFFF07E03FF
      FFFFFFFFFFFFFFFFC007FFFFF0FE03FFFFFFFFFFFFFFFFFFE00FFFFFFFFE07FF
      FFFFFFFFFFFFFFFFF81FFFFFFFFF0FFF00000000000000000000000000000000
      000000000000}
  end
end
