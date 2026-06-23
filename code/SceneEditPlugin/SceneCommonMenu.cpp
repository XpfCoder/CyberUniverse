#include <QtWidgets/QAction>
#include "SceneCommonMenu.h"

namespace Resafety {
	namespace CyberUniverseStudio {

		SceneCommonMenu::SceneCommonMenu(QWidget* parent)
			:QMenu(parent), m_bites(0)
		{
			QObject::connect(this, SIGNAL(triggered(QAction*)), SLOT(on_triggered(QAction*)));
		}


		SceneCommonMenu::SceneCommonMenu(const QString& title, QWidget* parent /*= Q_NULLPTR*/)
			: QMenu(title, parent), m_bites(0)
		{
			QObject::connect(this, SIGNAL(triggered(QAction*)), SLOT(on_triggered(QAction*)));
		}

		SceneCommonMenu::~SceneCommonMenu()
		{
		}

		QAction* SceneCommonMenu::addAction(int flag, QString str)
		{
			QAction* acion = QMenu::addAction(str);
			acion->setData(flag);
			return acion;
		}

		void SceneCommonMenu::enabledAction()
		{
			QList<QAction*> actions = this->actions();
			for (int i = 0; i < actions.size(); ++i)
			{
				actions[i]->setEnabled(true);
			}
		}

		void SceneCommonMenu::enabledAction(int flags)
		{
			QList<QAction*> actions = this->actions();
			for (int i = 0; i < actions.size(); ++i)
			{
				int flag = actions[i]->data().toInt();
				actions[i]->setEnabled(flag & flags);
			}
			m_bites = flags;
		}

		QAction* SceneCommonMenu::action(int flag)
		{
			QList<QAction*> actions = this->actions();
			for (int i = 0; i < actions.size(); ++i)
			{
				int f = actions[i]->data().toInt();
				if (f == flag)
				{
					return actions[i];
				}
			}
			return nullptr;
		}

		void SceneCommonMenu::setActionChecked(const int flags)
		{
			QList<QAction*> actions = this->actions();
			for (int i = 0; i < actions.size(); ++i)
			{
				int flag = actions[i]->data().toInt();
				actions[i]->setChecked(flag & flags);
			}
		}

		void SceneCommonMenu::addCommonAction()
		{
			addAction(Menu_Add, QObject::tr("Add"));
			addAction(Menu_Delete, QObject::tr("Delete"));
			addAction(Menu_Refresh, QObject::tr("Refresh"));
			addAction(Menu_Save, QObject::tr("Save"));
		}

		void SceneCommonMenu::addCommonAction(int flags)
		{
			if (Menu_Add & flags)
			{
				addAction(Menu_Add, QObject::tr("Add"));
			}
			if (Menu_Delete & flags)
			{
				addAction(Menu_Delete, QObject::tr("Delete"));
			}
			if (Menu_Refresh & flags)
			{
				addAction(Menu_Refresh, QObject::tr("Refresh"));
			}
			if (Menu_Save & flags)
			{
				addAction(Menu_Save, QObject::tr("Save"));
			}
		}

		void SceneCommonMenu::on_triggered(QAction* ac)
		{
			int f = ac->data().toInt();
			emit triggeredAction(f);
		}
	}
}
