#include "beziercurveevaluator.h"
#include <cassert>

void BezierCurveEvaluator::evaluateCurve(const std::vector<Point>& ptvCtrlPts, 
										 std::vector<Point>& ptvEvaluatedCurvePts, 
										 const float& fAniLength, 
										 const bool& bWrap) const
{
	int iCtrlPtCount = ptvCtrlPts.size();

	//ptvEvaluatedCurvePts.assign(ptvCtrlPts.begin(), ptvCtrlPts.end());
	ptvEvaluatedCurvePts.clear();

	if(bWrap){
		if(iCtrlPtCount>3){
			for(int j=0; j<100;j++){
				for(int i=0; i<iCtrlPtCount-3; i+=3){
					float u = j/100.0;

					float x_new=0.0;
					float y_new=0.0;

					x_new = ptvCtrlPts[i].x*(-u*u*u+3*u*u-3*u+1) + ptvCtrlPts[i+1].x*(3*u*u*u-6*u*u+3*u) 
								+ ptvCtrlPts[i+2].x*(-3*u*u*u+3*u*u) + ptvCtrlPts[i+3].x*u*u*u;
					y_new = ptvCtrlPts[i].y*(-u*u*u+3*u*u-3*u+1) + ptvCtrlPts[i+1].y*(3*u*u*u-6*u*u+3*u) 
								+ ptvCtrlPts[i+2].y*(-3*u*u*u+3*u*u) + ptvCtrlPts[i+3].y*u*u*u;

					ptvEvaluatedCurvePts.push_back(Point(x_new, y_new));
				}
			}

			if(iCtrlPtCount%3!=0){
				for(int i=(iCtrlPtCount-1)/3*3+1; i<iCtrlPtCount; i++){
					ptvEvaluatedCurvePts.push_back(ptvCtrlPts[i]);
				}
				float x1 = 0.0;
				float x2 = fAniLength;
				float y1 = (ptvCtrlPts[0].y * (fAniLength - ptvCtrlPts[iCtrlPtCount - 1].x) + 
				  ptvCtrlPts[iCtrlPtCount - 1].y * ptvCtrlPts[0].x) /
				 (ptvCtrlPts[0].x + fAniLength - ptvCtrlPts[iCtrlPtCount - 1].x);
				ptvEvaluatedCurvePts.push_back(Point(x1, y1));
				ptvEvaluatedCurvePts.push_back(Point(x2, y1));
			}else{
				for(int j=0; j<100;j++){
						float u = j/100.0;

						float x_new=0.0;
						float y_new=0.0;

						x_new = ptvCtrlPts[iCtrlPtCount-3].x*(-u*u*u+3*u*u-3*u+1) + ptvCtrlPts[iCtrlPtCount-2].x*(3*u*u*u-6*u*u+3*u) 
									+ ptvCtrlPts[iCtrlPtCount-1].x*(-3*u*u*u+3*u*u) + (ptvCtrlPts[0].x+fAniLength)*u*u*u;
						if(x_new>fAniLength){
							x_new-=fAniLength;
						}
						y_new = ptvCtrlPts[iCtrlPtCount-3].y*(-u*u*u+3*u*u-3*u+1) + ptvCtrlPts[iCtrlPtCount-2].y*(3*u*u*u-6*u*u+3*u) 
									+ ptvCtrlPts[iCtrlPtCount-1].y*(-3*u*u*u+3*u*u) + ptvCtrlPts[0].y*u*u*u;

						ptvEvaluatedCurvePts.push_back(Point(x_new, y_new));

				}
			}

		 }else{
		 	ptvEvaluatedCurvePts.assign(ptvCtrlPts.begin(), ptvCtrlPts.end());
			float x1 = 0.0;
			float x2 = fAniLength;
			float y1 = ptvCtrlPts[0].y;
			float y2 = ptvCtrlPts[iCtrlPtCount - 1].y;
			ptvEvaluatedCurvePts.push_back(Point(x1, y1));
			ptvEvaluatedCurvePts.push_back(Point(x2, y2));
		 }

	}else{
		if(iCtrlPtCount>3){
			for(int j=0; j<100;j++){
				for(int i=0; i<iCtrlPtCount-3; i+=3){
					float u = j/100.0;

					float x_new=0.0;
					float y_new=0.0;

					x_new = ptvCtrlPts[i].x*(-u*u*u+3*u*u-3*u+1) + ptvCtrlPts[i+1].x*(3*u*u*u-6*u*u+3*u) 
								+ ptvCtrlPts[i+2].x*(-3*u*u*u+3*u*u) + ptvCtrlPts[i+3].x*u*u*u;
					y_new = ptvCtrlPts[i].y*(-u*u*u+3*u*u-3*u+1) + ptvCtrlPts[i+1].y*(3*u*u*u-6*u*u+3*u) 
								+ ptvCtrlPts[i+2].y*(-3*u*u*u+3*u*u) + ptvCtrlPts[i+3].y*u*u*u;

					ptvEvaluatedCurvePts.push_back(Point(x_new, y_new));
				}
			}

			for(int i=(iCtrlPtCount-1)/3*3+1; i<iCtrlPtCount; i++){
				ptvEvaluatedCurvePts.push_back(ptvCtrlPts[i]);
			}

			float x1 = 0.0;
			float y1 = ptvCtrlPts[0].y;
			ptvEvaluatedCurvePts.push_back(Point(x1, y1));

			float x2 = fAniLength;
			float y2 = ptvCtrlPts[iCtrlPtCount - 1].y;
			ptvEvaluatedCurvePts.push_back(Point(x2, y2));

		}else{
			ptvEvaluatedCurvePts.assign(ptvCtrlPts.begin(), ptvCtrlPts.end());
			float x1 = 0.0;
			float x2 = fAniLength;
			float y1 = ptvCtrlPts[0].y;
			float y2 = ptvCtrlPts[iCtrlPtCount - 1].y;
			ptvEvaluatedCurvePts.push_back(Point(x1, y1));
			ptvEvaluatedCurvePts.push_back(Point(x2, y2));
		}
	}

}
