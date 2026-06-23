#pragma once
#include <QWidget>
#include <functional>
#include <QPainter>
#include "../EngineCore/Source/EngineCore.h"
#include "../EngineCore/Core/Event/InputEventManager.h"
class QMimeData;

class EventFilter : public QObject
{
	Q_OBJECT
protected:
	bool eventFilter(QObject *obj, QEvent *event) override
	{
		return true;
	}
};

class StudioView;
namespace Resafety { 
	namespace DeepEye { 
		class Node;
		class LonLatAlt;
	} 
}
class RenderWidget : public QWidget
{
	Q_OBJECT
public:
	explicit RenderWidget(QWidget *parent = nullptr);
	~RenderWidget();
	virtual QPaintEngine* paintEngine() const override
	{
		return NULL;
	}

public:
	//void paintEvent(QPaintEvent *e) override;

signals:
	void prepareEnv(const QString& path);
	void openSolution(const QString& path);
	void dropEventPos(const QString& key,const QPoint& point);
	void acceptDrop(int type);
public:
	void onOpenSolution(const QString& path);

	void isLoginToken(const bool isOffline);
	void getTokenList(QStringList list);

protected:
	void initKernel();
	bool acceptDrapMimeData(const QMimeData* mimeData);
	QStringList mimeDataHasFile(const QMimeData* mimeData);
	bool processImportModel(QDragEnterEvent* event);
	bool posToLla(int sceenX, int sceenY, Resafety::DeepEye::LonLatAlt& target);

protected:
	void leaveEvent(QEvent* event) override;
	void enterEvent(QEvent*) override;
	virtual void paintEvent(QPaintEvent* e);
	virtual void mouseMoveEvent(QMouseEvent *event) override;
	virtual void mouseReleaseEvent(QMouseEvent *event) override;
	virtual void mousePressEvent(QMouseEvent *event) override;
	virtual void resizeEvent(QResizeEvent* event) override;
	//void wheelEvent(QWheelEvent *event) override;
	//void resizeEvent(QResizeEvent *ev) override;
	//void mouseDoubleClickEvent(QMouseEvent *event) override;

	void keyPressEvent(QKeyEvent *event) override;
	void keyReleaseEvent(QKeyEvent *event) override;

	//void dragEnterEvent(QDragEnterEvent* event) override;
	//void dragLeaveEvent(QDragLeaveEvent* event) override;
	//void dragMoveEvent(QDragMoveEvent* event) override;
	//void dropEvent(QDropEvent* event) override;
	//bool nativeEventFilter(const QByteArray& eventType, void* message, long* result) override;
private:
	void nodeEnterScene(std::vector<Resafety::DeepEye::Node*>& nodes);
	void nodeLeverScene(std::vector<Resafety::DeepEye::Node*>& nodes);
	void nodeSetPosition(std::vector<Resafety::DeepEye::Node*>& nodes, Resafety::DeepEye::LonLatAlt& lla);
	void QMouseEvent2MouseState(QMouseEvent* event, EngineCore::MouseState& ms);
private:
	EventFilter m_eventFilter;
	StudioView* m_studioView;
	QStringList m_tokenInfoList;
	bool m_isOffLine;
};

