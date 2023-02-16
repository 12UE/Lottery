
// LotteryDlg.h: 头文件
//

#pragma once


// CLotteryDlg 对话框
class CLotteryDlg : public CDialogEx
{
// 构造
public:
	CLotteryDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LOTTERY_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CEdit m_input;
	CEdit m_result;
	CEdit m_samenumber;
	afx_msg void OnBnClickedButton1();
};
