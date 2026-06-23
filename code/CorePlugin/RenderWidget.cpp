#include "RenderWidget.h"
#include <QMainWindow>
#include <QMoveEvent>
#include <QCoreApplication>
#include <QFileInfo>
#include <QSettings>
#include <QTextCodec>
#include <QStatusBar>
#include <QTimer>
#include <QMimeData>
#include "StudioView.h"
//#include "DeepEyeCore\Pick\PickResult3D.h"
//#include "DeepEyeCore\Pick\Pickable3D.h"
//#include "DeepEyeCore/Platform/Keyboard.h"
//#include "DeepEyeCore/Engine/RenderView.h"
//#include "DeepEyeExt/TokenAccess/TokenAccess.h"
//#include "DeepEyeExt/TokenAccess/interface/TokenAccessInterface.h"
//#include "DeepEyeExt/DataAuthenticationAccess/BusinessAuthDataAccessAPI.h"
//#include "DeepEyeExt/DataAuthenticationAccess/BusinessAuthDataAccessor.h"
//#include <fstream>



RenderWidget::RenderWidget(QWidget *parent) : QWidget(parent)
{
	m_studioView = (StudioView*)parent;
	//setFocusPolicy(Qt::StrongFocus);
	//setAcceptDrops(true);
	setMouseTracking(true);
	setAttribute(Qt::WA_PaintOnScreen, true);
	setAttribute(Qt::WA_NativeWindow, true);
	initKernel();
}

RenderWidget::~RenderWidget()
{
}

void RenderWidget::onOpenSolution(const QString & path)
{
	show();
}

void RenderWidget::initKernel()
{
	EngineCore::EngineCore::GetInstance()->initEngine3D((HWND)winId(), this->width(), this->height());
	//QCoreApplication::processEvents();
	//if (EnginePlugin::GetInstance()->initEngine3D((HWND)winId()))
	//{
	//	startTimer(0);
	//}
	//setMouseTracking(true);
	//setFocusPolicy(Qt::ClickFocus);
	//removeEventFilter(&m_eventFilter);
}
void RenderWidget::getTokenList(QStringList list)
{
	m_tokenInfoList = list;
}
void RenderWidget::isLoginToken(const bool isOffline)
{
	m_isOffLine = isOffline;
}


bool RenderWidget::posToLla(int sceenX, int sceenY,Resafety::DeepEye::LonLatAlt& target)
{	
	

	return false;
}

void RenderWidget::nodeEnterScene(std::vector<Resafety::DeepEye::Node*>& nodes)
{
}

void RenderWidget::nodeLeverScene(std::vector<Resafety::DeepEye::Node*>& nodes)
{
	//std::for_each(nodes.begin(), nodes.end(), [](auto node) {node->removeFromScene(); });
}

void RenderWidget::nodeSetPosition(std::vector<Resafety::DeepEye::Node*>& nodes, Resafety::DeepEye::LonLatAlt& lla)
{
	//std::for_each(nodes.begin(), nodes.end(), [lla](auto node) {
	//	Resafety::DeepEye::GeoPointComponent* potinCom = node->getFirstComponent<Resafety::DeepEye::GeoPointComponent>();
	//	if (potinCom)
	//	{
	//		potinCom->set_position(lla);
	//	}
	//	});
}

bool RenderWidget::processImportModel(QDragEnterEvent* event)
{
	//SceneEditManager* sceneEditManager = (SceneEditManager*)(Resafety::DeepWorld::GetPluginManager()->getPlugin("SceneEditManager"));
	//if (!sceneEditManager)
	//	return false;

	//const QMimeData* mimeData = event->mimeData();
	//QStringList strList = mimeDataHasFile(mimeData);
	//if (strList.size())
	//{
	//	auto pos = event->pos();
	//	Resafety::DeepEye::LonLatAlt lla;
	//	
	//	if (posToLla(pos.x(), pos.y(), lla))
	//	{			
	//		for (size_t i = 0; i < strList.size(); i++)
	//		{
	//			QString str = strList[i];
	//			QFileInfo info(str);
	//			std::string ff = info.suffix().toLocal8Bit().data();

	//			std::vector<Resafety::DeepEye::Node*> nodeVector;
	//			DeepEyeImportFile* importInter = (DeepEyeImportFile*)DeepEyeCommon::getInterface(DEEPEYEIMPORTFILE_1_0);
	//			if (importInter)
	//			{
	//				if (DeepEyeAbstraceImportFilePtr ptr = importInter->getImportFile(ff.c_str()))
	//				{
	//					ptr->setTarScene(Resafety::DeepEye::GeoScene::GetType());
	//					nodeVector = ptr->serializationNode(str.toStdString());
	//				}
	//				else
	//				{
	//					nodeVector = DeepEyeSerialization::XmlToNode(StdString_(str));
	//					for (auto iter = nodeVector.begin(); iter != nodeVector.end();)
	//					{
	//						if ((*iter)->isTypeOf<Resafety::DeepEye::GeoNode>())
	//						{
	//							iter++;
	//						}
	//						else
	//						{
	//							(*iter)->release();
	//							iter = nodeVector.erase(iter);
	//						}
	//					}
	//				}
	//			}

	//			for (auto n : nodeVector)
	//			{
	//				if (n->isTypeOf <Resafety::DeepEye::GeoNode>())
	//				{
	//					Resafety::DeepEye::GeoNode* geoNode = (Resafety::DeepEye::GeoNode*)(n);
	//					char iID[200];
	//					memset(iID, 0, 200);
	//					sceneEditManager->createModelID(iID);
	//					geoNode->set_uuid(iID);
	//					m_dragNodes.push_back(n);
	//				}					
	//			}
	//		}

	//		if (m_dragNodes.size())
	//		{
	//			std::for_each(m_dragNodes.begin(), m_dragNodes.end(), [](auto node) {					
	//				node->setNotSerializableAndHideInEdit();
	//				});
	//			nodeSetPosition(m_dragNodes, lla);
	//			nodeEnterScene(m_dragNodes);
	//			event->acceptProposedAction();
	//			return true;
	//		}
	//	}
	//}
	return false;
}

bool RenderWidget::acceptDrapMimeData(const QMimeData* mimeData)
{
	return !mimeDataHasFile(mimeData).isEmpty();
}

QStringList RenderWidget::mimeDataHasFile(const QMimeData* mimeData)
{
	QStringList strlist;
	static const QString resFormat = QStringLiteral("application/x-qabstractitemmodeldatalist");
	if (mimeData->hasFormat(resFormat))
	{
		QByteArray byteArray = mimeData->data(resFormat);
		QDataStream stream(&byteArray, QIODevice::ReadOnly);
		int row = 0;
		int column = 0;
		QMap<int, QVariant> roles;
		stream >> row >> column >> roles;
		QString str = roles[Qt::UserRole].toString();
		QFileInfo info(str);
		if (info.exists())
		{
			strlist << str;
		}
	}
	else if (mimeData->hasUrls())
	{
		QList<QUrl> urlList = mimeData->urls();
		if (urlList.size())
		{
			for (size_t i = 0; i < urlList.size(); i++)
			{
				QString str = urlList[i].toLocalFile();
				QFileInfo info(str);
				if (info.exists())
				{
					strlist << str;
				}
			}

		}
	}
	return strlist;
}

void RenderWidget::keyPressEvent(QKeyEvent* event)
{
	auto scanCode = event->nativeScanCode();
	EngineCore::EngineCore::GetInstance()->onKeyPress((EngineCore::Keys)event->key());
}

void RenderWidget::keyReleaseEvent(QKeyEvent* event)
{
	auto scanCode = event->nativeScanCode();
	EngineCore::EngineCore::GetInstance()->onKeyRelease((EngineCore::Keys)event->key());
}


void RenderWidget::mousePressEvent(QMouseEvent* event)
{


	EngineCore::MouseState ms;

	QMouseEvent2MouseState(event, ms);

	EngineCore::EngineCore::GetInstance()->onMousePress(ms);
}

void RenderWidget::mouseMoveEvent(QMouseEvent* event)
{
	EngineCore::MouseState ms;

	QMouseEvent2MouseState(event, ms);

	EngineCore::EngineCore::GetInstance()->onMouseMove(ms);

	repaint();

}

void RenderWidget::mouseReleaseEvent(QMouseEvent* event)
{
	EngineCore::MouseState ms;

	QMouseEvent2MouseState(event, ms);

	EngineCore::EngineCore::GetInstance()->onMouseRelease(ms);
}


void RenderWidget::leaveEvent(QEvent* event)
{

	releaseKeyboard();
}
void RenderWidget::enterEvent(QEvent*)
{
	grabKeyboard();
}
void RenderWidget::paintEvent(QPaintEvent* e)
{
	EngineCore::EngineCore::GetInstance()->UpdateScene(EngineCore::EngineCore::GetInstance()->getGameInval());
	update();
}

void RenderWidget::QMouseEvent2MouseState(QMouseEvent* event, EngineCore::MouseState& ms)
{
	QPoint screenPoint = event->pos();
	ms.mousePos.x = screenPoint.x();
	ms.mousePos.y = screenPoint.y();
	ms.mouseType = (EngineCore::MouseType)event->button();
}

void RenderWidget::resizeEvent(QResizeEvent* event)
{
	EngineCore::EngineCore::GetInstance()->onResize(event->size().width(), event->size().height());
}