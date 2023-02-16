
// LotteryDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "Lottery.h"
#include "LotteryDlg.h"
#include "afxdialogex.h"
#include<vector>
#include<algorithm>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLotteryDlg 对话框



CLotteryDlg::CLotteryDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LOTTERY_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLotteryDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_input);
	DDX_Control(pDX, IDC_EDIT2, m_result);
	DDX_Control(pDX, IDC_EDIT3, m_samenumber);
}

BEGIN_MESSAGE_MAP(CLotteryDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CLotteryDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CLotteryDlg 消息处理程序

BOOL CLotteryDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CLotteryDlg::OnPaint()
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
HCURSOR CLotteryDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CLotteryDlg::OnBnClickedButton1(){
	// TODO: 在此添加控件通知处理程序代码
	std::vector<int> lotterynumbers;
	/*初始化1-36*/
	for (int i = 1; i <= 36; i++){
		lotterynumbers.push_back(i);
	}
	std::vector<int> inputnumbers;
	CString input;
	m_input.GetWindowTextW(input);
	//按空格或者逗号分隔
	int pos = 0;
	CString token = input.Tokenize(_T(" ,"), pos);
	while (token != _T("")){
		inputnumbers.push_back(_ttoi(token));
		token = input.Tokenize(_T(" ,"), pos);
	}
	//检查输入的7个数字是否重复
	for (int i = 0; i < inputnumbers.size(); i++) {
		for (int j = i + 1; j < inputnumbers.size(); j++) {
			if (inputnumbers[i] == inputnumbers[j]) {
				AfxMessageBox(_T("输入的数字有重复"));
				//清空输入框
				m_input.SetWindowTextW(_T(""));
				return;
			}
		}
	}
	//检查输入的7个数字是否在1-36之间
	for (int i = 0; i < inputnumbers.size(); i++) {
		if (inputnumbers[i] < 1 || inputnumbers[i] > 36) {
			AfxMessageBox(_T("输入的数字不在1-36之间"));
			//清空输入框
			m_input.SetWindowTextW(_T(""));
			return;
		}
	}
	//检查输入的数字个数是否为7个
	if (inputnumbers.size() != 7) {
		AfxMessageBox(_T("输入的数字个数不为7个"));
		m_input.SetWindowTextW(_T(""));
		return;
	}
	//随机生成7个不重复的数字
	
	srand((unsigned)time(NULL));
	std::vector<int> resultnumbers;
	for (int i = 0; i < 7; i++) {
		int index = rand() % lotterynumbers.size();
		resultnumbers.push_back(lotterynumbers[index]);
		lotterynumbers.erase(lotterynumbers.begin() + index);
	}
	//sort
	std::sort(resultnumbers.begin(), resultnumbers.end());
	//计算中奖号码
	std::vector<int> same;
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < inputnumbers.size(); j++) {
			if (resultnumbers[i] == inputnumbers[j]) {
				same.push_back(resultnumbers[i]);
			}
		}
	}
	//输出结果
	CString result;
	for (int i = 0; i < 7; i++) {
		result += _T(" ");
		result.AppendFormat(_T("%d"), resultnumbers[i]);
	}
	m_result.SetWindowTextW(result);
	//输出中奖号码
	CString samestr;
	for (int i = 0; i < same.size(); i++) {
		samestr += _T(" ");
		samestr.AppendFormat(_T("%d"), same[i]);
	}
	m_samenumber.SetWindowTextW(samestr);
}
