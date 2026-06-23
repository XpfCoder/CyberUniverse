//#include "../DeepWorldApi/MathTool.h"
//#include "../DeepWorldApi/MathTool.mh"
//#include "../DeepWorldApi/MathTool.ic"
//#include "../DeepWorldApi/MathTool.mc"
//#include "../DeepWorldApi/FrameworkInterface.h"
//#include "DouglasPeucker.h"
//#include "DeepEyeCore/Graphics/Camera3D.h"
//#include "DeepEyeCore/Graphics/Camera3DComponent.h"
//#include "DeepEyeCore/Scene/Node3D.h"
//#include "DeepEyeGeo/Math/GeographicCoordinate.h"
//#include "DeepEyeCore/Pick/PickResult3D.h"
//#include "DeepEyeCore/Pick/PickSystem.h"
//#include "DeepEyeCore/Engine/Engine.h"
//#include "DeepEyeGeo/Globe/GlobeTerrainComponent.h"
//#include "DeepEyeGeo/Globe/GlobeTerrainComponent.h"
//#include "DeepEyeGeo/Globe/GlobeTerrainManager.h"
//
//
//const double DEK_DOUBLE_PI = 3.1415926535897932384626433;
//double MathTool::g_lessen = 1;
//
//Resafety::DeepEye::Vector3f MathTool::LLHToScreenPt(const Resafety::DeepEye::LonLatAlt& llh)
//{
//	auto framework = Resafety::DeepWorld::GetFramework();
//	Resafety::DeepEye::PerspectiveCameraComponent* cameraComponent = framework->getMainCameraComponent();
//	Resafety::DeepEye::PerspectiveCamera* camera3d = cameraComponent->getCamera();
//
//	Resafety::DeepEye::HPTVector3 point;
//	LonLatAltToWGS(point, llh);
//	Resafety::DeepEye::Vector3f view = camera3d->worldToView(point);
//	Resafety::DeepEye::Vector3f projection = camera3d->viewToProjection(view);
//	const Resafety::DeepEye::Viewport& viewport = camera3d->getViewport();
//
//	Resafety::DeepEye::Vector3f pt(0, 0, 0);
//	pt.x = projection.x * (viewport.width / 2) + (viewport.width / 2) + viewport.x;
//	pt.y = projection.y * (-viewport.height / 2) + (viewport.height / 2) + viewport.y;
//	pt.z = projection.z;
//
//	pt.x = pt.x * g_lessen;
//	pt.y = pt.y * g_lessen;
//
//	return pt;
//}
//
//bool MathTool::ScreenPtToLLH(Resafety::DeepEye::LonLatAlt& points, const int x, const int y)
//{
//	Resafety::DeepEye::LinePickResult3D pickResult;
//	auto framework = Resafety::DeepWorld::GetFramework();
//	Resafety::DeepEye::PerspectiveCameraComponent* cameraComponent = framework->getMainCameraComponent();
//	Resafety::DeepEye::PerspectiveCamera* camera3d = cameraComponent->getCamera();
//	Resafety::DeepEye::PickSystem* pickSystem = Resafety::DeepEye::Engine::GetInstance()->getPickSystem();
//	pickSystem->screenPointPick3D(pickResult, camera3d, Resafety::DeepEye::Vector2f((float)x, (float)y));
//	Resafety::DeepEye::HPTLineSegment3 lineSeg = pickResult.getPickLine();
//	if (!pickResult.getPickedItemCount())
//	{
//		return false;
//	}
//	const Resafety::DeepEye::LinePickedItem3D &item = pickResult.getPickedItem(0);
//	Resafety::DeepEye::Vector3d pickPos(0, 0, 0);
//	lineSeg.getPoint(pickPos, item.distance);
//	Resafety::DeepEye::WGSToLonLatAlt(points, pickPos);
//	return true;
//}
//
//bool MathTool::ScreenPtToLLH(Resafety::DeepEye::LonLatAlt& points, const float x, const float y)
//{
//	Resafety::DeepEye::LinePickResult3D pickResult;
//	auto framework = Resafety::DeepWorld::GetFramework();
//	Resafety::DeepEye::PerspectiveCameraComponent* cameraComponent = framework->getMainCameraComponent();
//	Resafety::DeepEye::PerspectiveCamera* camera3d = cameraComponent->getCamera();
//	Resafety::DeepEye::PickSystem* pickSystem = Resafety::DeepEye::Engine::GetInstance()->getPickSystem();
//	pickSystem->screenPointPick3D(pickResult, camera3d, Resafety::DeepEye::Vector2f(x, y));
//	Resafety::DeepEye::HPTLineSegment3 lineSeg = pickResult.getPickLine();
//	if (!pickResult.getPickedItemCount())
//	{
//		return false;
//	}
//	const Resafety::DeepEye::LinePickedItem3D &item = pickResult.getPickedItem(0);
//	Resafety::DeepEye::Vector3d pickPos(0, 0, 0);
//	lineSeg.getPoint(pickPos, item.distance);
//	Resafety::DeepEye::WGSToLonLatAlt(points, pickPos);
//	return true;
//}
//
//Resafety::DeepEye::LonLatAlt MathTool::ScreenPtToLlaPt(const int x, const int y)
//{
//	Resafety::DeepEye::LonLatAlt lla(0, 0, 0);
//	Resafety::DeepEye::LinePickResult3D pickResult;
//	auto framework = Resafety::DeepWorld::GetFramework();
//	Resafety::DeepEye::PerspectiveCameraComponent* cameraComponent = framework->getMainCameraComponent();
//	Resafety::DeepEye::PerspectiveCamera* camera3d = cameraComponent->getCamera();
//	Resafety::DeepEye::PickSystem* pickSystem = Resafety::DeepEye::Engine::GetInstance()->getPickSystem();
//	pickSystem->screenPointPick3D(pickResult, camera3d, Resafety::DeepEye::Vector2f((float)x * g_lessen, (float)y * g_lessen));
//	Resafety::DeepEye::HPTLineSegment3 lineSeg = pickResult.getPickLine();
//	if (!pickResult.getPickedItemCount())
//	{
//		return lla;
//	}
//	const Resafety::DeepEye::LinePickedItem3D& item = pickResult.getPickedItem(0);
//	Resafety::DeepEye::Vector3d pickPos(0, 0, 0);
//	lineSeg.getPoint(pickPos, item.distance);
//	Resafety::DeepEye::WGSToLonLatAlt(lla, pickPos);
//	return lla;
//	return Resafety::DeepEye::LonLatAlt(0, 0, 0);
//}
//
//double MathTool::PolygonArea(const std::vector<Resafety::DeepEye::LonLatAlt>& poly)
//{
//	size_t point_num = poly.size();
//	if (point_num < 3)return 0.0;
//	Resafety::DeepEye::GeographicCoordinate gc;
//	std::vector<Resafety::DeepEye::Vector3f> lcl;
//	lcl.resize(point_num);
//	gc.setOrigin(poly[0]);
//	for (int i = 0; i < point_num; i++)
//		gc.lonLatAltToLocal(lcl[i], poly[i]);
//
//	double s = lcl[0].z * (lcl[point_num - 1].x - lcl[1].x);//points[0].z * (points[point_num - 1].x - points[1].x);
//
//	for (int i = 1; i < point_num; ++i)
//		s += lcl[i].z * (lcl[i - 1].x - lcl[(i + 1) % point_num].x);
//
//	return fabs(s / 2.0);
//}
//
//double MathTool::PolygonArea(const std::vector<Resafety::DeepEye::Vector2d>& poly)
//{
//	double res = 0.0f;
//	int count = (int)poly.size();
//	if (count < 3)
//	{
//		return 0;
//	}
//	for (int i = 1; i < count - 1; ++i)
//	{
//		res += Vector2Cross(poly[i] - poly[0], poly[(i + 1) % count] - poly[0]);
//	}
//	return abs(res * 0.5);
//}
//
//bool MathTool::GetNorthAngle(Resafety::DeepEye::LonLatAlt vStart, Resafety::DeepEye::LonLatAlt vEnd, float& fAngle)
//{
//	using namespace Resafety::DeepEye;
//	if (vStart.m_lon == vEnd.m_lon)
//	{
//		fAngle = 0.0f;
//		return true;
//	}
//	Vector3f			m_vAt;				// 北向
//	Vector3f			m_vUp;				// 天向
//	LonLatAlt llh[3];
//	llh[1] = vStart;
//	Matrix4x4f mat;
//	LonLatToOrientationLH(mat, LonLat(llh[1].m_lon, llh[1].m_lat));
//	Vector3d vOrigin;
//	LonLatAltToWGS(vOrigin, llh[1]);
//	m_vUp = *(Vector3f*)&mat.m[1];
//	m_vAt = *(Vector3f*)&mat.m[2];
//	Vector3d vNorth(vOrigin.x + (m_vAt * 100).x, vOrigin.y + (m_vAt * 100).y, vOrigin.z);
//	LonLatAlt lla;
//	WGSToLonLatAlt(lla, vNorth);
//	llh[0].m_lon = lla.m_lon;
//	llh[0].m_lat = lla.m_lat;
//	llh[0].m_alt = 0;
//	llh[1].m_alt = 0;
//	llh[2] = llh[1];
//
//	LonLatAlt llh2;
//	llh2 = vEnd;
//	llh2.m_alt = 0;
//	Vector3d vPos1, vPos2;
//	LonLatAltToWGS(vPos1, llh2);
//	LonLatAltToWGS(vPos2, llh[1]);
//	Vector3f vNormalize;
//	Vector3Normalize(vNormalize, ConvertToVector3<float>(vPos1 - vPos2));
//	Vector3d vPos3(vPos2.x + ((float)Vector3Length(vPos1 - vPos2) * m_vAt).x, vPos2.y + ((float)Vector3Length(vPos1 - vPos2) * m_vAt).y, vPos2.z);
//	WGSToLonLatAlt(lla, vPos3);
//	float fAngle2 = (float)(acos(Vector3Dot(m_vAt, vNormalize)) / DEK_DOUBLE_PI * 180.0f);
//	Vector3d vCross;
//	Vector3Cross(vCross, vPos1 - vPos2, m_vUp);
//	Vector3f vCrossNormalize;
//	Vector3Normalize(vCrossNormalize, ConvertToVector3<float>(vCross));
//	float fPAngle = (float)(acos(Vector3Dot(m_vAt, vCrossNormalize)) / DEK_DOUBLE_PI * 180.0f);
//	if (fPAngle > 90.0f)
//		fAngle2 = -fAngle2;
//	fAngle = fAngle2;
//	return true;
//}
//
//bool MathTool::GetNorthAngle(Resafety::DeepEye::Vector3d& startPos, Resafety::DeepEye::Vector3d& endPos, float& angle)
//{
//	Resafety::DeepEye::Vector3d	northVec(0, 0, 1);
//	Resafety::DeepEye::Vector3d normalize(0, 0, 0);
//	Vector3Normalize(normalize, ConvertToVector3<float>(endPos - startPos));
//	angle = (float)(acos(Vector3Dot(northVec, normalize)) / DEK_DOUBLE_PI * 180.0f);
//	if (endPos.x < 0)
//	{
//		angle = -angle;
//	}
//	return true;
//}
//
//bool MathTool::GetLandDistance(const std::vector<Resafety::DeepEye::LonLatAlt>& pLLHs, double& fDistance)
//{
//	if (pLLHs.size() < 2)
//	{
//		fDistance = 0;
//		return false;
//	}
//	fDistance = GetLandDistance(&pLLHs[0], (uint32_t)pLLHs.size());
//	return true;
//}
//
//double MathTool::GetStraightLineDistance(const Resafety::DeepEye::LonLatAlt& points1, const Resafety::DeepEye::LonLatAlt& points2)
//{
//	Resafety::DeepEye::GeographicCoordinate gc;
//	gc.setOrigin(points1);
//
//	Resafety::DeepEye::Vector3d local = Resafety::DeepEye::Vector3d::s_0_0_0;
//	gc.lonLatAltToLocal(local, points2);
//
//	double distance = 0;
//	distance = sqrt((local.x * local.x) + (local.y * local.y) + (local.z * local.z));
//	return distance;
//}
//
//double GetTriangeArea(const Resafety::DeepEye::Vector3f p0, const Resafety::DeepEye::Vector3f p1, const Resafety::DeepEye::Vector3f p2)
//{
//	double area = 0;
//	area = p0.x * p1.z + p1.x * p2.z + p2.x * p0.z - p1.x * p0.z - p2.x * p1.z - p0.x * p2.z;
//	return area / 2;
//}
//
//float MathTool::GetAlt(const Resafety::DeepEye::LonLat& lonLat)
//{
//	Resafety::DeepEye::GlobeTerrainComponent* globeTerrainComponent = Resafety::DeepEye::GlobeTerrainManager::GetInstance()->getEarth();
//	if (globeTerrainComponent)
//	{
//		return globeTerrainComponent->getAltitude(lonLat);
//	}
//	
//	return 0;
//}
//
//bool MathTool::IsPointInPolygon(const Resafety::DeepEye::Vector2d& point, const std::vector<Resafety::DeepEye::Vector2d>& polygon)
//{
//	int crosscount = 0;
//	size_t pointcount = polygon.size();
//	for (size_t i = 0; i < pointcount; ++i)
//	{
//		Resafety::DeepEye::Vector2d p1 = polygon[i];
//		Resafety::DeepEye::Vector2d p2 = polygon[(i + 1) % pointcount];
//		if (p1.y == p2.y)
//		{
//			continue;
//		}
//		if (point.y < Min(p1.y, p2.y))
//		{
//			continue;
//		}
//		if (point.y > Max(p1.y, p2.y))
//		{
//			continue;
//		}
//		double x = (p2.x - p1.x) / (p2.y - p1.y) * (point.y - p1.y) + p1.x;
//		if (x > point.x)
//		{
//			crosscount++;
//		}
//	}
//	return (crosscount % 2) != 0;
//}
//
//double MathTool::GetProjectedArea(const std::vector<Resafety::DeepEye::LonLatAlt>& lla)
//{
//	if (lla.size() < 3)
//	{
//		return 0;
//	}
//	Resafety::DeepEye::GeographicCoordinate gc;
//	gc.setOrigin(lla[0]);
//
//	std::vector< Resafety::DeepEye::Vector3d> localPos(lla.size());
//	std::vector<Resafety::DeepEye::Vector2d> edge(lla.size());
//	for (int i = 0; i < lla.size(); ++i)
//	{
//		gc.lonLatAltToLocal(localPos[i], lla[i]);
//		edge[i].x = localPos[i].x;
//		edge[i].y = localPos[i].z;
//	}
//	if (PolygonArea(edge) < 1.0)
//	{
//		return PolygonArea(edge);
//	}
//
//	double cellSize = sqrt(PolygonArea(edge) / 2500);
//
//	Resafety::DeepEye::AxisAlignedBox2d aligenBox;
//	Resafety::DeepEye::AxisAlignedBox2BuildFromPoints(aligenBox, &edge[0], edge.size());
//
//	int cols = Max(1, (int)(aligenBox.getSize().x / cellSize));
//	int rows = Max(1, (int)(aligenBox.getSize().y / cellSize));
//
//	double stepCols = aligenBox.getSize().x / cols;
//	double stepRows = aligenBox.getSize().y / rows;
//
//	Resafety::DeepEye::Vector2d halfStep(stepCols *0.5, stepRows*0.5);
//	Resafety::DeepEye::Vector2d minPos = aligenBox.m_min;
//	double proArea = 0.0;
//
//	for (int i = 0; i < rows; ++i)
//	{
//		for (int j = 0; j < cols; ++j)
//		{
//			minPos.x += stepCols * j;
//			minPos.y += stepRows * i;
//			minPos += halfStep;
//			if (IsPointInPolygon(minPos, edge))
//			{
//				Resafety::DeepEye::Vector3d quad[] =
//				{
//					Resafety::DeepEye::Vector3d(minPos.x - halfStep.x, minPos.y + halfStep.y, GetAlt(Resafety::DeepEye::LonLat(minPos.x - halfStep.x, minPos.y + halfStep.y))),
//					Resafety::DeepEye::Vector3d(minPos.x + halfStep.x, minPos.y + halfStep.y, GetAlt(Resafety::DeepEye::LonLat(minPos.x + halfStep.x, minPos.y + halfStep.y))),
//					Resafety::DeepEye::Vector3d(minPos.x - halfStep.x, minPos.y - halfStep.y, GetAlt(Resafety::DeepEye::LonLat(minPos.x - halfStep.x, minPos.y - halfStep.y))),
//					Resafety::DeepEye::Vector3d(minPos.x + halfStep.x, minPos.y - halfStep.y, GetAlt(Resafety::DeepEye::LonLat(minPos.x + halfStep.x, minPos.y - halfStep.y))),
//				};
//				proArea += (MathTool::triangleArea(quad[0], quad[1], quad[2]) + MathTool::triangleArea(quad[3], quad[1], quad[2]));
//			}
//		}
//	}
//	return proArea;
//}
//
//int MathTool::DouglasPeuckerLLH(Resafety::DeepEye::LonLatAlt* pLLHs, uint32_t pointCount, float tolerance)
//{
//	using namespace Resafety::DeepEye;
//	if (pointCount < 3)
//	{
//		return 0;
//	}
//	std::vector<LonLatAlt> points;
//	points.reserve(pointCount);
//	for (uint32_t i = 0; i < pointCount; i++)
//	{
//		points.push_back(pLLHs[i]);
//	}
//	//std::vector<LonLatAlt> points(pLLHs);
//
//	while (pointCount > 1)
//	{
//		if (pLLHs[0] == pLLHs[pointCount - 1])
//		{
//			pointCount--;
//
//			continue;
//		}
//		break;
//	}
//
//	if (pointCount < 3)
//	{
//		return 0;
//	}
//	Resafety::DeepEye::GeographicCoordinate gc;
//	gc.setOrigin(points[0]);
//	std::vector<Vector3f> lclPoints(pointCount);
//	gc.lonLatAltToLocal(&lclPoints[0], &points[0], pointCount);
//	bool success = DouglasPeucker(lclPoints, tolerance);
//	if (!success || lclPoints.size() < 3)
//		return 0;
//
//	for (size_t i = 0; i != lclPoints.size(); ++i)
//	{
//		LonLatAlt llh;
//		gc.localToLonLatAlt(llh, lclPoints[i]);
//		pLLHs[i] = llh;
//	}
//
//	return (int)lclPoints.size();
//}
//
//double MathTool::GetWeightCenter(const Resafety::DeepEye::LonLatAlt* pLLHs, uint32_t pointCount, Resafety::DeepEye::LonLatAlt& center)
//{
//	using namespace Resafety::DeepEye;
//	//uint32_t pointCount = pLLHs.size();
//	if (pointCount < 3)
//	{
//		return 0;
//	}
//	center = LonLatAlt(0, 0, 0);
//	double area = 0;
//
//	//std::vector<LonLatAlt> points(pLLHs);
//	/*auto it = std::unique(points.begin(), points.end());
//	points.erase(it, points.end());
//	pointCount = (uint32_t)points.size();
//	if (*points.begin() == *points.rbegin())
//	{
//		PAF_ASSERT(pointCount > 0);
//		pointCount -= 1;
//	}
//	if (pointCount < 3)
//	{
//		return 0;
//	}*/
//	Resafety::DeepEye::GeographicCoordinate gc;
//	gc.setOrigin(pLLHs[0]);
//	std::vector<Vector3f> lclPoints(pointCount);
//	gc.lonLatAltToLocal(&lclPoints[0], &pLLHs[0], pointCount);
//	Vector3d weight_point = Vector3d(0, 0, 0);
//	for (uint32_t i = 0; i < pointCount - 2; i++)
//	{
//		Vector3f p0 = lclPoints[0];
//		Vector3f p1 = lclPoints[i + 1];
//		Vector3f p2 = lclPoints[i + 2];
//
//		double triange_area = GetTriangeArea(p0, p1, p2);
//		area += triange_area;
//		weight_point.x += (p0.x + p1.x + p2.x)*triange_area;
//		weight_point.z += (p0.z + p1.z + p2.z)*triange_area;
//
//	}
//	weight_point.x = weight_point.x / 3 / area;
//	weight_point.z = weight_point.z / 3 / area;
//	gc.localToLonLatAlt(center, weight_point);
//
//	return area;
//
//
//
//	/*std::vector<Vector2f> llc;
//	for (int i = 0; i < lclPoints.size(); ++i)
//	{
//		Vector2f temp_2f(lclPoints[i].x, lclPoints[i].z);
//		llc.push_back(temp_2f);
//	}
//	int indexCount = DeepEye_Polygon::GetTriange(&llc[0], pointCount, nullptr, 0);
//	if (indexCount == -1)
//		return false;
//	std::vector<int> indices(indexCount);
//	DeepEye_Polygon::GetTriange(&llc[0], (int)llc.size(), &indices[0], indexCount);
//	float sum_area = 0;
//	int triange_count = indexCount / 3;
//	for (int i = 0; i < triange_count; i++)
//	{
//		Vector2f p0 = llc[indices[3 * i]];
//		Vector2f p1 = llc[indices[3 * i+1]];
//		Vector2f p2 = llc[indices[3 * i+2]];
//	}*/
//
//
//
//	return true;
//}
//
//int MathTool::CWorCCW(const Resafety::DeepEye::Vector3f* pPos, int nCounts)
//{
//	if (nullptr == pPos || nCounts <= 2)
//	{
//		return 0;
//	}
//
//	float fMinZ = FLT_MAX;
//
//	for (int i = 0; i < nCounts; ++i)
//	{
//		if (pPos[i].z < fMinZ)
//		{
//			fMinZ = pPos[i].z;
//		}
//	}
//
//	float fArea = 0.0f;
//
//	for (int i = 0; i < nCounts; ++i)
//	{
//		fArea += (pPos[i].z + pPos[(i + 1) % nCounts].z - fMinZ * 2) * (pPos[(i + 1) % nCounts].x - pPos[i].x);
//	}
//
//	if (fArea == 0.0f)
//	{
//		return 0;
//	}
//
//	return fArea > 0 ? 1 : -1;
//}
//
//Resafety::DeepEye::LonLatAlt* MathTool::GetScaleLLH(Resafety::DeepEye::LonLatAlt* pLLHs, uint32_t pointCount, float addNum)
//{
//	if (pointCount > 0)
//	{
//		using namespace Resafety::DeepEye;
//		bool isRing = false;
//		Resafety::DeepEye::LonLatAlt * resLLA = new Resafety::DeepEye::LonLatAlt[pointCount];
//		std::vector<Vector3f> lclPoints(pointCount);
//		if (pLLHs[0] == pLLHs[pointCount - 1])
//		{
//			isRing = true;
//			pointCount = pointCount - 1;
//		}
//		if (pointCount >= 3)
//		{
//			/*Resafety::DeepEye::LonLatAlt * resLLA = new Resafety::DeepEye::LonLatAlt[pointCount];*/
//
//			Resafety::DeepEye::GeographicCoordinate gc;
//			gc.setOrigin(pLLHs[0]);
//			/*std::vector<Vector3f> lclPoints(pointCount);*/
//			gc.lonLatAltToLocal(&lclPoints[0], &pLLHs[0], pointCount);
//			int isClockWise = CWorCCW(lclPoints.data(), pointCount);
//
//			//注掉的部分的算法暂时有问题，暂未修改所以注掉
//			/*for (uint32_t i = 0; i < pointCount; i++)
//			{
//				Vector3f dirNormal = Vector3f(0, 0, 0);
//				Vector3f dirNormal1 = Vector3f(0, 0, 0);
//				Vector3f dirNormal2 = Vector3f(0, 0, 0);
//				if (i == 0)
//				{
//					dirNormal1 = lclPoints[pointCount - 1] - lclPoints[i];
//					dirNormal2 = lclPoints[i + 1] - lclPoints[i];
//					
//				}
//				else if(i == pointCount-1)
//				{
//					dirNormal1 = lclPoints[i - 1] - lclPoints[i];
//					dirNormal2 = lclPoints[0] - lclPoints[i];
//				}
//				else
//				{
//					dirNormal1 = lclPoints[i - 1] - lclPoints[i];
//					dirNormal2 = lclPoints[i + 1] - lclPoints[i];
//				}
//				dirNormal1 = Vector3Normalize(dirNormal1);
//				dirNormal2 = Vector3Normalize(dirNormal2);
//				Vector3f upDir = Vector3Cross(dirNormal2, dirNormal1);
//				if (upDir.y < 0)
//				{
//					upDir = -upDir;
//				}
//				Vector3f rightDir = Vector3Cross(dirNormal2, upDir);
//				dirNormal = dirNormal1 + dirNormal2;
//				double dot = Vector3Dot(dirNormal, rightDir);
//				if (dot <= 0)
//				{
//					dirNormal = -dirNormal;
//				}
//				dirNormal = Vector3Normalize(dirNormal);
//				dirNormal *= addNum;
//				Vector3d newPoint = Vector3d(dirNormal.x + lclPoints[i].x, dirNormal.y + lclPoints[i].y, dirNormal.z + lclPoints[i].z);
//				gc.localToLonLatAlt(resLLA[i], newPoint);
//			}*/
//
//			for (size_t i = 0; i != pointCount; ++i)
//			{
//				size_t preIndex = i - 1;
//				if (i == 0)
//				{
//					preIndex = pointCount - 1;
//				}
//				const Vector3f& prePt = lclPoints[preIndex];
//				const Vector3f& pt = lclPoints[i];
//				const Vector3f& nextPt = lclPoints[(i + 1) % pointCount];
//				Vector3f dir1 = prePt - pt;
//				Vector3f dir2 = nextPt - pt;
//				Vector3Normalize(dir1, dir1);
//				Vector3Normalize(dir2, dir2);
//				Vector3f dir = dir1 + dir2;//角平分线
//				Vector3Normalize(dir, dir);
//				float sign = 1.0f;
//				if (isClockWise==1)
//				{
//					sign = (Vector3Cross(dir1, dir2).y > 0 ? 1.0f : -1.0f);
//				}
//				else
//				{
//					sign = (Vector3Cross(dir1, dir2).y > 0 ? -1.0f : 1.0f);
//				}		
//				Vector3d newPoint = Vector3d( lclPoints[i].x + dir.x * addNum*sign, lclPoints[i].y + dir.y * addNum*sign, lclPoints[i].z + dir.z * addNum*sign);
//				gc.localToLonLatAlt(resLLA[i], newPoint);
//			}
//
//			if (isRing)
//			{
//				(resLLA[pointCount]) = (resLLA[0]);
//			}
//			return resLLA;
//		}		
//
//		delete [] resLLA;
//	}
//	return NULL;
//}
//
//
//double MathTool::GetLandDistance(const Resafety::DeepEye::LonLatAlt* pLLHs, uint32_t pointCount)
//{
//	using namespace Resafety::DeepEye;
//	if (pointCount < 2)
//	{
//		return 0;
//	}
//
//	double fLength = 0;
//	for (uint32_t i = 0; i < pointCount - 1; i++)
//	{
//		Vector3d wgsPos1;
//		Vector3d wgsPos2;
//		LonLatAltToWGS(wgsPos1, pLLHs[i]);
//		LonLatAltToWGS(wgsPos2, pLLHs[i + 1]);
//		fLength += Vector3Length(wgsPos1 - wgsPos2);
//	}
//
//	return fLength;
//}
//
//bool MathTool::IsPointInLineSegment(const Resafety::DeepEye::Vector3d& newPoint, const Resafety::DeepEye::Vector2d& endLine,
//	const Resafety::DeepEye::Vector3d& localPoint, const Resafety::DeepEye::Vector2d& currentLine)
//{
//	Resafety::DeepEye::Vector3d subtrValue(localPoint - newPoint);
//	double res1 = (subtrValue.x * currentLine.y - subtrValue.z * currentLine.x) / (endLine.x * currentLine.y - endLine.y * currentLine.x);
//	double res2 = (float)(subtrValue.x * endLine.y - subtrValue.z * endLine.x) / (endLine.x * currentLine.y - endLine.y * currentLine.x);
//	if ((res1 > 0 && res1 < 1) && (res2 > 0 && res2 < 1))
//	{
//		return true;
//	}
//	return false;
//}
//
//bool MathTool::NewPointIsVaildForPolygon(const std::vector<Resafety::DeepEye::LonLatAlt>& polygonLLAList, const Resafety::DeepEye::LonLatAlt& newLla)
//{
//	//如果面的点数小于3,则认为newPoint属于有效的点
//	if (polygonLLAList.size()<3)
//	{
//		return true;
//	}
//	Resafety::DeepEye::GeographicCoordinate gc;
//	gc.setOrigin(polygonLLAList[0]);
//	size_t count = polygonLLAList.size();
//	std::vector<Resafety::DeepEye::Vector3d>localPoints(count);
//	for (size_t i = 0; i < count; ++i)
//	{
//		gc.lonLatAltToLocal(localPoints[i], polygonLLAList[i]);
//	}
//	Resafety::DeepEye::Vector3d newPoint{ 0,0,0 };
//	gc.lonLatAltToLocal(newPoint, newLla);
//	//第一个、最后一个点与新选的点分别形成线段
//	Resafety::DeepEye::Vector2d firstLine(localPoints[0].x - newPoint.x, localPoints[0].z - newPoint.z);
//	Resafety::DeepEye::Vector2d endLine(localPoints[count - 1].x - newPoint.x, localPoints[count - 1].z - newPoint.z);
//
//	if (Resafety::DeepEye::Vector2Length(firstLine) <= 1e-4f || Resafety::DeepEye::Vector2Length(endLine) <= 1e-4f)
//	{
//		return false;
//	}
//	//判断新选的点形成的线段与已知线段间有没有交点
//	for (size_t i = 0; i < count - 1; ++i)
//	{
//		//当前已知线段的标准向量
//		Resafety::DeepEye::Vector2d currentLine(localPoints[i + 1].x - localPoints[i].x, localPoints[i + 1].z - localPoints[i].z);
//
//		if ((firstLine.x * currentLine.y == firstLine.y * currentLine.x))
//		{
//			if (endLine.x * currentLine.y == endLine.y * currentLine.x)
//			{
//				continue;
//			}
//			if (IsPointInLineSegment(newPoint, endLine, localPoints[i], currentLine))
//			{
//				return false;
//			}
//		}
//		else if (endLine.x * currentLine.y == endLine.y * currentLine.x)
//		{
//			if (IsPointInLineSegment(newPoint, firstLine, localPoints[i], currentLine))
//			{
//				return false;
//			}
//		}
//		else
//		{
//			if (IsPointInLineSegment(newPoint, firstLine, localPoints[i], currentLine) || IsPointInLineSegment(newPoint, endLine, localPoints[i], currentLine))
//			{
//				return false;
//			}
//		}
//	}
//	return true;
//}