object frmChargeFrm: TfrmChargeFrm
  Left = 0
  Top = 0
  Caption = #20805#20540#30028#38754
  ClientHeight = 298
  ClientWidth = 471
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  FormStyle = fsStayOnTop
  OldCreateOrder = False
  Position = poScreenCenter
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 181
    Width = 471
    Height = 117
    Align = alBottom
    TabOrder = 0
    object Label1: TLabel
      Left = 44
      Top = 48
      Width = 88
      Height = 13
      Caption = #36755#20837#20805#20540#21345#21495#30721':'
    end
    object Label2: TLabel
      Left = 8
      Top = 16
      Width = 124
      Height = 13
      Caption = #36755#20837#39764#20861#19990#30028#30331#38470#24080#21495':'
    end
    object edtChargeText: TEdit
      Left = 154
      Top = 45
      Width = 227
      Height = 21
      TabOrder = 1
    end
    object edtAcc: TEdit
      Left = 154
      Top = 13
      Width = 227
      Height = 21
      TabOrder = 0
    end
    object btCharge: TButton
      Left = 396
      Top = 80
      Width = 75
      Height = 25
      Caption = #20805#20540
      TabOrder = 2
      OnClick = btChargeClick
    end
  end
  object PageControl1: TPageControl
    Left = 0
    Top = 0
    Width = 471
    Height = 181
    ActivePage = TabSheet2
    Align = alClient
    TabOrder = 1
    object TabSheet2: TTabSheet
      Caption = #20805#20540#20449#24687
      ImageIndex = 1
      object memChargeMsg: TMemo
        Left = 0
        Top = 0
        Width = 463
        Height = 153
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
  end
end
