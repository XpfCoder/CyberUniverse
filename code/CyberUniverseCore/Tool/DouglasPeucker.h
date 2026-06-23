//#pragma once
//#include <vector>
//#include "DeepEyeGeo/Math/LonLatAlt.h"
//#include "DeepEyeCore/Math/Vector2.h"
//#include "DeepEyeCore/Math/Vector3.h"
//template<typename T>
//T PointToLineSegDis(const Resafety::DeepEye::Vector3<T>& pt, const Resafety::DeepEye::Vector3<T>& line_start, const Resafety::DeepEye::Vector3<T>& line_end,
//	Resafety::DeepEye::Vector3<T>* intersect_pt = NULL)
//{
//	const Resafety::DeepEye::Vector3<T>& pt_a = line_start;
//	const Resafety::DeepEye::Vector3<T>& pt_b = line_end;
//	const Resafety::DeepEye::Vector3<T>& pt_p = pt;
//	double dis = 0.0;
//	Resafety::DeepEye::Vector3<T> AP = pt_p - pt_a;
//	Resafety::DeepEye::Vector3<T> BP = pt_p - pt_b;
//	Resafety::DeepEye::Vector3<T> AB = pt_b - pt_a;
//	T dot = Resafety::DeepEye::Vector3Dot(AP, AB);
//	T lenAB = Resafety::DeepEye::Vector3Length(AB);
//	T sqrAB = lenAB * lenAB;
//	T ratio = dot / sqrAB;
//	if (ratio <= 0)
//	{
//		dis = Resafety::DeepEye::Vector3Length(AP);
//		if (intersect_pt != NULL)
//		{
//			*intersect_pt = pt_a;
//		}
//
//	}
//	else if (ratio >= 1)
//	{
//		dis = Resafety::DeepEye::Vector3Length(BP);
//		if (intersect_pt != NULL)
//		{
//			*intersect_pt = pt_b;
//		}
//	}
//	else
//	{
//		T lenAP = Resafety::DeepEye::Vector3Length(AP);
//		T lenAB = Resafety::DeepEye::Vector3Length(AB);
//		T cosVal = dot / (lenAB*lenAP);
//		T sinVal = sqrt(1 - cosVal * cosVal);
//		dis = lenAP * sinVal;
//		if (intersect_pt != NULL)
//		{
//			Resafety::DeepEye::Vector3Normalize(AB, AB);
//			*intersect_pt = pt_a + lenAP * cosVal*AB;
//		}
//	}
//	return (T)dis;
//}
//
//template<typename T>
//static void DouglasPeuckerImpl(const std::vector<Resafety::DeepEye::Vector3<T> > & point_list, std::vector<int>& point_index, int start, int end, T tolerance)
//{
//	if (start < end)
//	{
//		T max_dis(0);
//		int mid = 0;
//		for (int i = start + 1; i < end; ++i)
//		{
//			T dis = PointToLineSegDis(point_list[i], point_list[start], point_list[end]);
//			if (dis > max_dis)
//			{
//				max_dis = dis;
//				mid = i;
//			}
//		}
//		if (max_dis >= tolerance)
//		{
//			point_index[mid] = 1;
//			DouglasPeuckerImpl(point_list, point_index, start, mid, tolerance);
//			DouglasPeuckerImpl(point_list, point_index, mid, end, tolerance);
//		}
//	}
//}
//
//template<typename T>
//bool DouglasPeucker(std::vector<Resafety::DeepEye::Vector3<T> > & point_list, T tolerance)
//{
//	std::vector<int> point_index(point_list.size(), 0);
//	int start = 0;
//	int end = int(point_list.size() - 1);
//	point_index[start] = 1;
//	point_index[end] = 1;
//	DouglasPeuckerImpl(point_list, point_index, start, end, tolerance);
//	std::vector<Resafety::DeepEye::Vector3<T> > temp_point_list;
//	for (size_t i = 0; i != point_list.size(); ++i)
//	{
//		if (point_index[i] == 1)
//		{
//			temp_point_list.push_back(point_list[i]);
//		}
//	}
//	point_list.swap(temp_point_list);
//	return true;
//}