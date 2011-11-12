object FrmDrawMap: TFrmDrawMap
  Left = 0
  Top = 0
  Caption = 'FrmDrawMap'
  ClientHeight = 565
  ClientWidth = 819
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
  object Panel1: TPanel
    Left = 0
    Top = 418
    Width = 819
    Height = 147
    Align = alBottom
    TabOrder = 0
  end
  object Panel2: TPanel
    Left = 608
    Top = 0
    Width = 211
    Height = 418
    Align = alRight
    TabOrder = 1
  end
  object sbMap: TScrollBox
    Left = 0
    Top = 0
    Width = 608
    Height = 418
    Align = alClient
    DoubleBuffered = True
    ParentDoubleBuffered = False
    TabOrder = 2
    object imgPicMap: TImage
      Left = 0
      Top = 0
      Width = 449
      Height = 313
    end
    object imgObsMap: TImage
      Left = -4
      Top = 20
      Width = 449
      Height = 313
      Transparent = True
    end
    object pbMapObj: TPaintBox
      Left = 0
      Top = -1
      Width = 350
      Height = 247
      PopupMenu = PopupMenu1
      OnMouseEnter = pbMapObjMouseEnter
      OnMouseLeave = pbMapObjMouseLeave
      OnMouseMove = pbMapObjMouseMove
      OnPaint = pbMapObjPaint
    end
    object labMapHint: TLabel
      Left = 150
      Top = 124
      Width = 60
      Height = 12
      Caption = 'labMapHint'
      Font.Charset = GB2312_CHARSET
      Font.Color = clWhite
      Font.Height = -12
      Font.Name = #23435#20307
      Font.Style = []
      ParentFont = False
      Transparent = True
      Visible = False
    end
  end
  object RefreshTimer: TTimer
    Interval = 200
    OnTimer = RefreshTimerTimer
    Left = 216
    Top = 128
  end
  object PopupMenu1: TPopupMenu
    Left = 408
    Top = 256
    object miCopy: TMenuItem
      Caption = #22797#21046
      OnClick = miCopyClick
    end
    object miMove: TMenuItem
      Caption = 'Move'
      OnClick = miMoveClick
    end
  end
end
