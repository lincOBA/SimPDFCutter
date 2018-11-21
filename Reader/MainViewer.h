﻿// summary: 主窗口
#ifndef MAIN_VIEWER_H
#define MAIN_VIEWER_H

#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QToolBar>
//#include <QDialog>
#include <QFileDialog>
#include <QString>
#include <QMdiArea>
#include <QDesktopServices>
#include <QMdiSubWindow>
#include <QLineEdit>
#include <QLabel>

#include "IMainViewer.h"
#include "ChildViewer.h"
#include "MultiViewer.h"

class MainViewer : public QMainWindow, public IMainViewer
{
	Q_OBJECT
public:
	MainViewer(QWidget *parent = 0);
	~MainViewer();

public:
	virtual QString getFileName(){ return m_strFileName; }
	virtual QLineEdit* getPageNumLineEdit() { return m_PageNumLineEdit; }

public:
	void CreatToolBar(); //创建工具栏
	void CreatActions(); //创建动作
	void CreatMenus(); //创建菜单栏

private:
	ChildViewer* getCurChildViewer();

private:
	QMenu* m_FileMenu; //菜单栏
	QMenu* m_EditMenu;
	QMenu* m_WindowMenu;
	QMenu* m_HelpMenu;

	//动作
	QAction* m_OpenAction; //打开文件
	QAction* m_SaveAction; //保存文件
	QAction* m_QuitAction; //退出

	QAction* m_ZoomIn;
	QAction* m_ZoomOut;
	QAction* m_ZoomReset;

	QAction* m_PreviousPage; //上一页
	QAction* m_NextPage; //下一页
	QLineEdit* m_PageNumLineEdit; //页码框
	QLabel* m_PageCountLabel; //页码总数

	//test
	QAction* m_NewAction; //新建文件

	//两个工具栏
	QToolBar* m_FileTool;
	QToolBar* m_ZoomTool;
	QToolBar* m_PageTool;

	//窗口布局
	MultiViewer* m_MainMdiArea; //主窗体中的多文档区域


public:
	ChildViewer* CreateChildViewer();

public slots:
	//定义槽函数
	void OpenFile();
	void SaveFile();
	void CloseFile();
	void NewFile();
	//     void UpDataMenus(); //更新状态栏
	void ZoomIn();
	void ZoomOut();
	void ZoomReset();
	void PreviousPage();
	void NextPage();
	void UpdataPageNum();
	void GotoPage();

private:
	QString m_strFileName;
	void RefreshWindow();
};
#endif // MAIN_VIEWER_H
