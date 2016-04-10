#include "bsplinecurveevaluator.h"
#include <cassert>

float max(float x){
	return x+1;
}

void BSplineCurveEvaluator::evaluateCurve(const std::vector<Point>& ptvCtrlPts, 
										 std::vector<Point>& ptvEvaluatedCurvePts, 
										 const float& fAniLength, 
										 const bool& bWrap) const
{
	int iCtrlPtCount = ptvCtrlPts.size();

	ptvEvaluatedCurvePts.clear();
	//ptvEvaluatedCurvePts.assign(ptvCtrlPts.begin(), ptvCtrlPts.end());

	if(bWrap){
		if(iCtrlPtCount<3){
			for(int j=0; j<100;j++){
				for(int i=0; i<iCtrlPtCount; i++){
					float u = j/100.0;

					float x_new=0.0;
					float y_new=0.0;

					Point first, second, third, fourth;

					if(i==0){
						first = ptvCtrlPts[0];
						second = ptvCtrlPts[1];
						third = ptvCtrlPts[0];
							third.x += fAniLength;
						fourth = ptvCtrlPts[1];
							fourth.x += fAniLength;
					}else{
						first = ptvCtrlPts[1];
							first.x -= fAniLength;
						second = ptvCtrlPts[0];
						third = ptvCtrlPts[1];
						fourth = ptvCtrlPts[0];
							fourth.x += fAniLength;
					 }

					x_new = first.x*(-1.0/6*u*u*u+1.0/2*u*u-1.0/2*u+1.0/6) 
								+ second.x*(1.0/2*u*u*u-u*u+2.0/3) 
								+ third.x*(-1.0/2*u*u*u+1.0/2*u*u+1.0/2*u+1.0/6)
								+ fourth.x*(1.0/6*u*u*u);
					 if(x_new>fAniLength) x_new-=fAniLength;
					 //if(x_new<0) x_new+=fAniLength;
					y_new = first.y*(-1.0/6*u*u*u+1.0/2*u*u-1.0/2*u+1.0/6) 
								+ second.y*(1.0/2*u*u*u-u*u+2.0/3) 
								+ third.y*(-1.0/2*u*u*u+1.0/2*u*u+1.0/2*u+1.0/6)
								+ fourth.y*(1.0/6*u*u*u);

					ptvEvaluatedCurvePts.push_back(Point(x_new, y_new));
				}
			}
			return;
		}

		for(int j=0; j<100;j++){
			for(int i=0; i<iCtrlPtCount; i++){
				float u = j/100.0;

				float x_new=0.0;
				float y_new=0.0;

				Point first = (i<iCtrlPtCount)?ptvCtrlPts[i]:ptvCtrlPts[i-iCtrlPtCount];
					if(i>=iCtrlPtCount) first.x += fAniLength;
				Point second = (i+1<iCtrlPtCount)?ptvCtrlPts[i+1]:ptvCtrlPts[i+1-iCtrlPtCount];
					if(i+1>=iCtrlPtCount) second.x += fAniLength;
				Point third = (i+2<iCtrlPtCount)?ptvCtrlPts[i+2]:ptvCtrlPts[i+2-iCtrlPtCount];
					if(i+2>=iCtrlPtCount) third.x += fAniLength;
				Point fourth = (i+3<iCtrlPtCount)?ptvCtrlPts[i+3]:ptvCtrlPts[i+3-iCtrlPtCount];
					if(i+3>=iCtrlPtCount) fourth.x += fAniLength;

				x_new = first.x*(-1.0/6*u*u*u+1.0/2*u*u-1.0/2*u+1.0/6) 
							+ second.x*(1.0/2*u*u*u-u*u+2.0/3) 
							+ third.x*(-1.0/2*u*u*u+1.0/2*u*u+1.0/2*u+1.0/6)
							+ fourth.x*(1.0/6*u*u*u);
				if(x_new>fAniLength) x_new-=fAniLength;
				y_new = first.y*(-1.0/6*u*u*u+1.0/2*u*u-1.0/2*u+1.0/6) 
							+ second.y*(1.0/2*u*u*u-u*u+2.0/3) 
							+ third.y*(-1.0/2*u*u*u+1.0/2*u*u+1.0/2*u+1.0/6)
							+ fourth.y*(1.0/6*u*u*u);

				ptvEvaluatedCurvePts.push_back(Point(x_new, y_new));
			}
		}

	}else{
		if(iCtrlPtCount<3){
			ptvEvaluatedCurvePts.assign(ptvCtrlPts.begin(), ptvCtrlPts.end());
			float y1 = ptvCtrlPts[0].y;
			float y2 = ptvCtrlPts[ptvCtrlPts.size() - 1].y;
			ptvEvaluatedCurvePts.push_back(Point(0, y1));
			ptvEvaluatedCurvePts.push_back(Point(fAniLength, y2));
			return;
		}

		std::vector<Point> newCtrlPts;
		newCtrlPts.assign(ptvCtrlPts.begin(), ptvCtrlPts.end());

		//add more curve by adding points
		Point tmpPoint = newCtrlPts[0];
		newCtrlPts.insert(newCtrlPts.begin(), tmpPoint);
		newCtrlPts.insert(newCtrlPts.begin(), tmpPoint);
		tmpPoint = newCtrlPts[newCtrlPts.size() - 1];
		newCtrlPts.push_back(tmpPoint);
		newCtrlPts.push_back(tmpPoint);

		for(int j=0; j<100;j++){
			for(int i=0; i<newCtrlPts.size()-3; i++){
				float u = j/100.0;

				float x_new=0.0;
				float y_new=0.0;

				x_new = newCtrlPts[i].x*(-1.0/6*u*u*u+1.0/2*u*u-1.0/2*u+1.0/6) 
							+ newCtrlPts[i+1].x*(1.0/2*u*u*u-u*u+2.0/3) 
							+ newCtrlPts[i+2].x*(-1.0/2*u*u*u+1.0/2*u*u+1.0/2*u+1.0/6)
							+ newCtrlPts[i+3].x*(1.0/6*u*u*u);
				y_new = newCtrlPts[i].y*(-1.0/6*u*u*u+1.0/2*u*u-1.0/2*u+1.0/6) 
							+ newCtrlPts[i+1].y*(1.0/2*u*u*u-u*u+2.0/3) 
							+ newCtrlPts[i+2].y*(-1.0/2*u*u*u+1.0/2*u*u+1.0/2*u+1.0/6)
							+ newCtrlPts[i+3].y*(1.0/6*u*u*u);

				ptvEvaluatedCurvePts.push_back(Point(x_new, y_new));
			}
		}

		float y1 = newCtrlPts[0].y;
		float y2 = newCtrlPts[newCtrlPts.size() - 1].y;
		ptvEvaluatedCurvePts.push_back(Point(0, y1));
		ptvEvaluatedCurvePts.push_back(Point(fAniLength, y2));

	}
	

	// float x = 0.0;
	// float y1 = max(0.5);


	// if (bWrap) {
	// 	// if wrapping is on, interpolate the y value at xmin and
	// 	// xmax so that the slopes of the lines adjacent to the
	// 	// wraparound are equal.

	// 	// if ((ptvCtrlPts[0].x + fAniLength) - ptvCtrlPts[iCtrlPtCount - 1].x > 0.0f) {
	// 	// 	y1 = (ptvCtrlPts[0].y * (fAniLength - ptvCtrlPts[iCtrlPtCount - 1].x) + 
	// 	// 		  ptvCtrlPts[iCtrlPtCount - 1].y * ptvCtrlPts[0].x) /
	// 	// 		 (ptvCtrlPts[0].x + fAniLength - ptvCtrlPts[iCtrlPtCount - 1].x);
	// 	// }
	// 	//else 
	// 		y1 = ptvCtrlPts[0].y;
	// }
	// else {
	// 	// if wrapping is off, make the first and last segments of
	// 	// the curve horizontal.

	// 	y1 = newCtrlPts[0].y;
 //    }

	// ptvEvaluatedCurvePts.push_back(Point(x, y1));

	// /// set the endpoint based on the wrap flag.
	// float y2;
 //    x = fAniLength;
 //    if (bWrap)
	// 	y2 = y1;
 //    else
	// 	y2 = newCtrlPts[newCtrlPts.size() - 1].y;

	// ptvEvaluatedCurvePts.push_back(Point(x, y2));

}
