﻿#include "SingleContinuousState.h"

class DocWidget;

SingleContinuousState::SingleContinuousState(IChildViewer* childViewer): m_ChildViewer(childViewer)
{

}

SingleContinuousState::~SingleContinuousState()
{

}

void SingleContinuousState::RenderPages(QPainter *paint)
{
	if (paint == NULL)
		return;

	int nScrollHeight = 0; //当前窗口的高度
	int nScrollYFlag = 0;  //当前坐标（画布）
	nScrollHeight = m_ChildViewer->getScrollArea()->size().height(); //当前绘制的剩余窗口高度
	nScrollYFlag  = GetVScrollPos();
	//首先刷一下成灰色

	// 当前绘制的页码
	int nPageNum;
	// 当前页码绘制的起始VPos
	int nPageVPos;
	// 当前页码的图片
	QImage img;
	QImage imageCopy;

	int nXDrawPos = 0;

	while (nScrollHeight > 0)
	{
		GetVPos(nScrollYFlag, nPageNum, nPageVPos);
		// 绘制当前页的高度
		int nRenderHeight = GetPageSize(nPageNum).height() + 8 - nPageVPos;

		imageCopy = m_ChildViewer->getPageImage(nPageNum);
		img = imageCopy.copy(0, nPageVPos, GetPageSize(nPageNum).width(), nRenderHeight);

		QSize docWidget = m_ChildViewer->getDocWidgetSize();
		nXDrawPos = ((docWidget.width() - GetPageSize(nPageNum).width())) / 2;
		if (nXDrawPos < 0)
			nXDrawPos = m_ChildViewer->getScrollArea()->verticalScrollBar()->size().width() / 2;

		paint->drawImage(nXDrawPos, nScrollYFlag, img);

		nScrollHeight -= img.height();
		nScrollYFlag += img.height();
	}

}

int SingleContinuousState::GetCurPageNum()
{
	int nCurPagePos = GetVScrollPos() + m_ChildViewer->getDocWidgetSize().height() / 2;
	int nPageCount = GetPageCount();
	for (int i = 0; i < nPageCount; i++)
	{
		if (nCurPagePos < m_ChildViewer->getPageSize(i).height())
			return i;
		nCurPagePos = nCurPagePos - GetPageSize(i).height() - 8;
	}
	return 1;
}

void SingleContinuousState::GotoPage(int nPageNum)
{
	int nPageNumHeight = GetPageHeightCount(nPageNum);
	QScrollBar* pScrollBar = m_ChildViewer->getScrollArea()->verticalScrollBar();
	pScrollBar->setValue(nPageNumHeight);
}

int SingleContinuousState::GetVScrollPos()
{
	QScrollBar* pScrollBar = m_ChildViewer->getScrollArea()->verticalScrollBar();

	return pScrollBar->value();
}

int SingleContinuousState::GetHScrollPos()
{
	QScrollBar* pScrollBar = m_ChildViewer->getScrollArea()->horizontalScrollBar();
	return pScrollBar->value();
}

int SingleContinuousState::GetPageHeightCount(int nNumPage)
{
	int nHeight = 0;
	for (int i = 0; i < nNumPage; i++)
		nHeight += m_ChildViewer->getPageSize(i).height() + 8;

	return nHeight;
}

bool SingleContinuousState::GetVPos(int nScrollPos, int &nPageNum, int &nPageVStartPos)
{
	int nPageCount = GetPageCount();

	for (int i = 0; i < nPageCount; i++)
	{
		if (nScrollPos < (GetPageSize(i).height() + 8))
		{
			nPageNum = i;
			nPageVStartPos = nScrollPos;
			break;
		}
		nScrollPos -= (GetPageSize(i).height() + 8);
	}
	nScrollPos += 8;

	return true;
}




// 暂时完成单页非连续状态
//QImage ViewModel::GetImage()
//{
//    int vPos = GetVScrollPos();

//    // 获取第一页的大小
//    int nNum = GetNumCount();
//    QSize size = GetActruallyPageSize(0);


//    int vhigh = size.height();

//    int ny = vPos % vhigh;
//    int nCurPageNum = vPos / vhigh;

//    QImage image2 = GetPageImage(nCurPageNum, 0, nCurPageNum, size.width(), size.height(), 0);

//    return image2;
//}
