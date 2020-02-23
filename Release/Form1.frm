VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "Form1"
   ClientHeight    =   3030
   ClientLeft      =   120
   ClientTop       =   450
   ClientWidth     =   4560
   LinkTopic       =   "Form1"
   LockControls    =   -1  'True
   ScaleHeight     =   3030
   ScaleWidth      =   4560
   StartUpPosition =   3  '窗口缺省
   Begin VB.CheckBox Check2 
      Caption         =   "Check2"
      Height          =   495
      Left            =   240
      Style           =   1  'Graphical
      TabIndex        =   8
      Top             =   2400
      Width           =   855
   End
   Begin VB.Frame Frame1 
      Caption         =   "Frame1"
      Height          =   615
      Left            =   240
      TabIndex        =   7
      Top             =   480
      Width           =   1335
   End
   Begin VB.HScrollBar HScroll1 
      Height          =   255
      Left            =   240
      TabIndex        =   6
      Top             =   2040
      Width           =   3735
   End
   Begin VB.VScrollBar VScroll1 
      Height          =   1815
      Left            =   4080
      TabIndex        =   5
      Top             =   720
      Width           =   255
   End
   Begin VB.PictureBox Picture1 
      Height          =   1215
      Left            =   1920
      ScaleHeight     =   1155
      ScaleWidth      =   1635
      TabIndex        =   4
      Top             =   600
      Width           =   1695
   End
   Begin VB.DriveListBox Drive1 
      Height          =   300
      Left            =   240
      TabIndex        =   3
      Top             =   1200
      Width           =   1215
   End
   Begin VB.CheckBox Check1 
      Caption         =   "Check1"
      Height          =   255
      Left            =   240
      TabIndex        =   2
      Top             =   1560
      Width           =   1215
   End
   Begin VB.CommandButton Command1 
      Caption         =   "Command1"
      Height          =   495
      Left            =   1680
      TabIndex        =   1
      Top             =   2400
      Width           =   1215
   End
   Begin VB.TextBox Text1 
      Height          =   270
      Left            =   240
      TabIndex        =   0
      Text            =   "Text1"
      Top             =   120
      Width           =   3975
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Declare Function clsSec Lib "clsSec" () As Long
Private Declare Function clsSec_Hook Lib "clsSec" (ByVal onm As String, ByVal nnm As String) As Long
Private Declare Function clsSec_GenRnd Lib "clsSec" (ByVal p As String, ByVal sz As Long) As Long
Private Declare Function clsSec_Start Lib "clsSec" () As Long
Private Declare Sub clsSec_Destroy Lib "clsSec" ()
Private Declare Sub clsSec_ErrLook Lib "clsSec" (ByVal code As Long)

Private Sub Form_Initialize()
    If clsSec Then
        '随机类名
        clsSec_Hook "ThunderRT6FormDC", vbNullString
        clsSec_Hook "ThunderRT6DriveListBox", vbNullString
        clsSec_Hook "ThunderRT6Frame", vbNullString
        '自定义类名（名称不可重复）
        clsSec_Hook "ThunderRT6TextBox", "JuncoJet"
        clsSec_Hook "ThunderRT6CommandButton", "TButton"
        clsSec_Hook "ThunderRT6PictureBoxDC", "TPanel"
        'clsSec_Hook "ThunderRT6HScrollBar", "THScroll" '通过DllAttach方式来修改
        clsSec_Hook "ThunderRT6VScrollBar", "TVScroll"
        '超长类名
        clsSec_Hook "ThunderRT6CheckBox", "01234568890123456889012345688901234568890123456889012345688901234568890123456889"
        clsSec_Start
    End If
End Sub

Private Sub Form_Load()
    '随机窗口名
    Dim p As String
    p = Space$(64)
    If clsSec_GenRnd(p, 64) Then
        Form1.Caption = p
    End If
    '退出销毁clsSec,可防止被外部程序读出内存数据
    clsSec_Destroy
End Sub
