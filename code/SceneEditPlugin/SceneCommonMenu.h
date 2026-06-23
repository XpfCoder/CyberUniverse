#pragma once
#ifndef SceneCommonMenu_h__
#define SceneCommonMenu_h__
#include <QtWidgets/QMenu>

class QAction;
namespace Resafety {
	namespace CyberUniverseStudio {

		enum CommonMenu
		{
			Menu_Invalid = 0,
			Menu_Add = 1,
			Menu_Delete = Menu_Add << 1,
			Menu_Refresh = Menu_Delete << 1,
			Menu_Save = Menu_Refresh << 1
		};

		class Q_DECL_EXPORT SceneCommonMenu : public QMenu
		{
			Q_OBJECT
		public:
			SceneCommonMenu(QWidget* parent = Q_NULLPTR);
			SceneCommonMenu(const QString& title, QWidget* parent = Q_NULLPTR);
			~SceneCommonMenu();
		public:
			QAction* addAction(int flag, QString str);
			void enabledAction();
			void enabledAction(int flags);
			QAction* action(int flag);
			int getFlags() { return m_bites; }
			//นดักorทวนดัก
			void setActionChecked(const int flags);
		public:
			void addCommonAction();
			void addCommonAction(int flags);
		private slots:
			void on_triggered(QAction* ac);
		signals:
			void triggeredAction(int);
		private:
			int m_bites;
		};
	}
}

#endif // SceneCommonMenu_h__
