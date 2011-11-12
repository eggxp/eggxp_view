object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Form1'
  ClientHeight = 290
  ClientWidth = 554
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object btTest: TButton
    Left = 8
    Top = 8
    Width = 75
    Height = 25
    Caption = 'btTest'
    TabOrder = 0
    OnClick = btTestClick
  end
  object GroupBox1: TGroupBox
    Left = 152
    Top = 81
    Width = 353
    Height = 201
    Caption = 'Client Calc'
    TabOrder = 1
    object labUserName: TLabeledEdit
      Left = 16
      Top = 40
      Width = 121
      Height = 21
      EditLabel.Width = 49
      EditLabel.Height = 13
      EditLabel.Caption = 'UserName'
      TabOrder = 0
      Text = 'eggxp'
    end
    object labPsw: TLabeledEdit
      Left = 208
      Top = 40
      Width = 121
      Height = 21
      EditLabel.Width = 19
      EditLabel.Height = 13
      EditLabel.Caption = 'Psw'
      TabOrder = 1
      Text = '1'
    end
    object edtClients: TLabeledEdit
      Left = 16
      Top = 88
      Width = 121
      Height = 21
      EditLabel.Width = 5
      EditLabel.Height = 13
      EditLabel.Caption = 's'
      TabOrder = 2
    end
    object edtClientB: TLabeledEdit
      Left = 208
      Top = 88
      Width = 121
      Height = 21
      EditLabel.Width = 6
      EditLabel.Height = 13
      EditLabel.Caption = 'B'
      TabOrder = 3
    end
    object edtClientCalcResult: TLabeledEdit
      Left = 136
      Top = 136
      Width = 193
      Height = 21
      EditLabel.Width = 27
      EditLabel.Height = 13
      EditLabel.Caption = 'result'
      TabOrder = 4
    end
    object btClientCalc: TButton
      Left = 16
      Top = 136
      Width = 75
      Height = 25
      Caption = 'btClientCalc'
      TabOrder = 5
      OnClick = btClientCalcClick
    end
  end
  object Button1: TButton
    Left = 256
    Top = 8
    Width = 75
    Height = 25
    Caption = 'Button1'
    TabOrder = 2
    OnClick = Button1Click
  end
end
