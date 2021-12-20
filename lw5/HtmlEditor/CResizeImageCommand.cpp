#include "stdafx.h"
#include "CResizeImageCommand.h"

CResizeImageCommand::CResizeImageCommand(CImageSize& currentSize, const CImageSize& newSize)
	: m_currentSize(currentSize)
	, m_newSize(newSize)
{
}

void CResizeImageCommand::DoExecute()
{
	std::swap(m_currentSize, m_newSize);
}

void CResizeImageCommand::DoUnexecute()
{
	std::swap(m_currentSize, m_newSize);
}
