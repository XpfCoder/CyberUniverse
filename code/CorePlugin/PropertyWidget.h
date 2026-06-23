#pragma once

#include <QDockWidget>
#include <QTreeWidget>

namespace EngineCore { class Node; };

class CyberUniversePropertyTreeWidget : public QTreeWidget
{
	Q_OBJECT
public:
	CyberUniversePropertyTreeWidget(QWidget* parent);
	virtual ~CyberUniversePropertyTreeWidget();

	QMainWindow* getMainWindow();
	void SetMainWindow(QMainWindow* mainWnd) { m_mainWnd = mainWnd; }

	void setNode(EngineCore::Node* node);
	EngineCore::Node* getCurrentNode() const { return m_node; }

	bool isLock() { return m_lock; }

signals:
	void propertyChanged();

public slots:
	void setLock(bool val);
	void refreshProperty();

protected:
	void buildPropertyTree();

private:
	EngineCore::Node* m_node{ nullptr };
	QMainWindow* m_mainWnd{ nullptr };
	bool m_lock{ false };
};



class PropertyEditWidget : public QDockWidget
{
	Q_OBJECT

public:
	explicit PropertyEditWidget(QWidget* parent = nullptr);
	~PropertyEditWidget();

	void setNode(EngineCore::Node* node);
	EngineCore::Node* getNode() const { return m_node; }

	CyberUniversePropertyTreeWidget* getPropertyTreeWidget()
	{
		return m_propertyTree;
	}

signals:
	void prepareEnv(const QString& path);
	void openSolution(const QString& path);
	void propertyChanged();

private:
	CyberUniversePropertyTreeWidget* m_propertyTree{ nullptr };
	EngineCore::Node* m_node{ nullptr };
};
