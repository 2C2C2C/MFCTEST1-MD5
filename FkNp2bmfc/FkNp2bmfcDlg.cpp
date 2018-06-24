
// FkNp2bmfcDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FkNp2bmfc.h"
#include "FkNp2bmfcDlg.h"
#include "afxdialogex.h"


#include <md5.h>
#include <hex.h>
#include <files.h>
#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1 
#pragma comment (lib,"cryptlib.lib")  //����lib�ļ������ 



#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CFkNp2bmfcDlg �Ի���



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


// CFkNp2bmfcDlg ��Ϣ�������

BOOL CFkNp2bmfcDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CFkNp2bmfcDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CFkNp2bmfcDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CFkNp2bmfcDlg::OnBnClickedButtonFkfile()//ѡ���ļ�
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CFileDialog dlg(TRUE, _T("*"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_ALLOWMULTISELECT, _T("Fast Boom wa (*.*) |*.*||"));//ѡ���ļ�
	CString fs;//�ļ�·��
	if (dlg.DoModal() == IDOK)
	{
		POSITION pos = dlg.GetStartPosition();//�õ�·��
		while (pos != 0)
		{
			fs = dlg.GetNextPathName(pos);//��ȡ�ļ�·���� CString fs
		}
	}
	if (fs == L"")//δѡ���ļ�������
		return;

	MessageBox(fs);//����ѡ����ļ���·��
	std::string fpp;//�ļ�·��
	fpp = CT2A(fs);//�ļ�·�� cstring -> string

	std::string result;//��MD5���
	CryptoPP::MD5 hash;//ʵ����MD5����
	CryptoPP::FileSource(fpp.c_str(), true, new CryptoPP::HashFilter(hash, new CryptoPP::HexEncoder(new CryptoPP::StringSink(result), false)));
	//�õ��ļ���MD5ֵ
	CString rst(result.c_str());//MD5ֵ string -> cstring 
	MessageBox(rst);//���MD5ժҪֵ

	SetDlgItemText(IDC_EDIT_RST,rst);//����Ի����ϵ�һ���ؼ�

}
