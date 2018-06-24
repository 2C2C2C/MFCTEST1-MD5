
// FkNp2bmfcDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "FkNp2bmfc.h"
#include "FkNp2bmfcDlg.h"
#include "afxdialogex.h"


#include <md5.h>
#include <hex.h>
#include <files.h>
#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1 
#pragma comment (lib,"cryptlib.lib")  //加载lib文件的语句 



#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CFkNp2bmfcDlg 对话框



CFkNp2bmfcDlg::CFkNp2bmfcDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_FKNP2BMFC_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFkNp2bmfcDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CFkNp2bmfcDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_FKFile, &CFkNp2bmfcDlg::OnBnClickedButtonFkfile)
END_MESSAGE_MAP()


// CFkNp2bmfcDlg 消息处理程序

BOOL CFkNp2bmfcDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CFkNp2bmfcDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CFkNp2bmfcDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CFkNp2bmfcDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CFkNp2bmfcDlg::OnBnClickedButtonFkfile()//选择文件
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog dlg(TRUE, _T("*"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_ALLOWMULTISELECT, _T("Fast Boom wa (*.*) |*.*||"));//选择文件
	CString fs;//文件路径
	if (dlg.DoModal() == IDOK)
	{
		POSITION pos = dlg.GetStartPosition();//得到路径
		while (pos != 0)
		{
			fs = dlg.GetNextPathName(pos);//获取文件路径到 CString fs
		}
	}
	if (fs == L"")//未选择文件则跳出
		return;

	MessageBox(fs);//检视选择的文件的路径
	std::string fpp;//文件路径
	fpp = CT2A(fs);//文件路径 cstring -> string

	std::string result;//存MD5结果
	CryptoPP::MD5 hash;//实例化MD5对象
	CryptoPP::FileSource(fpp.c_str(), true, new CryptoPP::HashFilter(hash, new CryptoPP::HexEncoder(new CryptoPP::StringSink(result), false)));
	//得到文件的MD5值
	CString rst(result.c_str());//MD5值 string -> cstring 
	MessageBox(rst);//输出MD5摘要值

	SetDlgItemText(IDC_EDIT_RST,rst);//传入对话框上的一个控件

}
