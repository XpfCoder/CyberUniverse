#pragma once

#include <QWidget>
#include <QtWidgets/QMainWindow>
#include "../SARibbonBar/SARibbonMainWindow.h"
#include "../SARibbonBar/SARibbonBar.h"
#include "../SARibbonBar/SARibbonPannelItem.h"
#include "../SARibbonBar/SARibbonComboBox.h"
#include "../SARibbonBar/SARibbonCategory.h"
#include "../SARibbonBar/SARibbonPannel.h"
#include "../SARibbonBar/SARibbonMainWindow.h"
class StudioView  : public SARibbonMainWindow
{
	Q_OBJECT

public:
	explicit StudioView();
	~StudioView();

	void addTabifiedDockWidget(Qt::DockWidgetArea area, QDockWidget* dockwidget);
private:
	QAction* createAction(const QString& text, const QString& iconurl);
	QAction* createAction(const QString& text, const QString& iconurl, const QString& objName);

private:
	QList<QDockWidget*> m_dockWidgets;
};
