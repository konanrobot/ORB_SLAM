/*
 * =====================================================================================
 *
 *       Filename:  ProbabilityMapping.cc
 *
 *    Description:  
 *
 *        Version:  0.1
 *        Created:  01/21/2016 10:39:12 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Josh Tang, Rebecca Frederic 
 *   Organization:  
 *
 * =====================================================================================
 */
#include "ProbabilityMapping.h"
#include "KeyFrame.h"
#include <opencv2/core/core.hpp>
#include <vector>


void firstLoop(KeyFrame kf, depthHo** ho, std::vector<depthHo>* depth_ho){
  vector<KeyFrame*> closestMatches = kf -> GetBestCovisibilityFrames();
  float max_depth;
  float min_depth;
  StereoSearchConstraints(kf, min_depth, max_depth);
  
  cv::Mat gradx, grady, grad;
  cv::Mat image = kf->GetImage();
  GetImageGradient(image,gradx,grady,grad);
  
  vector<depthHo> depth_ho;
  depthHo ho[image.rows][image.cols];

  for(int x = 0; x < image.rows; x++){
    for(int y = 0; y < image.cols; y++){
      ho[x][y] = NULL;
      if(grad.at<float>(x,y) < lambdaG)
        continue;
  
      for(size_t i=0; i<closestMatches.size(); i++){
        KeyFrame* kf2 = closestMatches[j];
        
        struct depthHo dh;
        EpipolarSearch(kf,kf2,x,y,gradx,grady,grad,min_depth,max_depth,dh);
        depth_ho.push_back(dh);
        ho[x][y] = dh;
      }
    }
  }
}

void StereoSearchConstraints(KeyFrame kf, float* min_depth, float* max_depth){
  
  vector<float> orb_depths = kf->GetAllPointDepths();
  
  boost::variance::accumulator_set<double, stats<tag::variance> > acc;
  for_each(orb_depths.begin(), orb_depths.end(), bind<void>(ref(acc), _1));

  float max_depth = mean(acc) + 2*sqrt(variance(acc));
  float min_depth = mean(acc) - 2*sqrt(variance(acc));
}
	        
void EpipolarSearch(KeyFrame kf1, Keyframe kf2, int x, int y, cv::Mat gradx, cv::Mat grady, cv::Mat grad, float min_depth, float max_depth, depthHo* dh){
  cv::Mat original = kf1->GetImage();
  cv::Mat pixel = original.at<cv::Mat>(x,y);

  cv::Mat image = kf2 -> GetImage();
  cv::Mat image_stddev, image_mean;
  cv::meanStdDev(image,mean,image_stddev);
  
  cv::Mat F12 = LocalMapping::ComputeF12(kf1,kf2); 
  float a = x*F12.at<float>(0,0)+y*F12.at<float>(1,0)+F12.at<float>(2,0);
  float b = x*F12.at<float>(0,1)+y*F12.at<float>(1,1)+F12.at<float>(2,1);
  float c = x*F12.at<float>(0,2)+y*F12.at<float>(1,2)+F12.at<float>(2,2);
  
  float old_err = 1000.0;
  float best_photometric_err = 0.0;
  float best_gradient_modulo_err = 0.0;
  int best_pixel;

  for(int uj = minDepth; uj < maxDepth; uj++){
    vj = (a/b)*uj+(c/b);
    
    float th_grad, th_epipolar_line, th_pi, th_rot;
    cv::Mat gradx2, grady2, grad2;
    GetImageGradient(image, gradx2, grady2, grad2);
    GetGradientOrientation(uj,vj,gradx2,grady2,th_grad);
    th_epipolar_line = fastAtan2(uj,vj); 
    GetInPlaneRotation(kf1, kf2, th_rot);
    GetImageGradient(x,y,gradx,grady,th_pi);

    if(grad2.at<float>(uj,vj) < lambdaG)
      continue;
    if(abs(th_grad - th_epipolar_line + M_PI) < lambdaG)
      continue;
    if(abs(th_grad - th_epipolar_line - M_PI) < lambdaG)
      continue;
    if(abs(th_grad - ( th_pi + th_rot )) < lambdaTheta)
      continue;
    
    float photometric_err = pixel - image.at<cv::Mat>(uj,vj);
    float gradient_modulo_err = grad - grad2;
    float err = (photometric_err*photometric_err + (gradient_modulo_err*gradient_modulo_err)/0.23)/(image_stddev);

    if(err < old_err){
      best_pixel = uj;
      old_err = err;
      best_photometric_err = photometric_err;
      best_gradient_modulo_err = gradient_modulo_err;
    }
  }

  int uj_plus = best_pixel + 1;
  int vj_plus = (a/b)*uj_plus + (c/b);
  int uj_minus = best_pixel - 1;
  int vj_minus = (a/b)*uj_minus + (c/b);

  float g = (image.at<float>(uj_plus, vj_plus) - image.at<float>(uj_minus, vj_minus))/2.0;

  float q = (grad2.at<float>(uj_plus, uv_plus) - grad2.at<float>(uj_minus, vj_plus))/2;

  float ustar = best_pixel + (g*best_photometric_err + (1/0.23)*q*best_gradinet_modulo_err)/(g*g + (1/0.23)*q*q);
  float ustar_var = (2*image_stddev*image_stddev)/(g*g

  ComputeInvDepthHypothesis(kf, best_pixel, ustar, ustar_var, a, b, c, dh);
  
  }
}

void inverseDepthHypothesisFusion(const vector<depthHo> H, depthHo* dist) {
    dist->depth = 0;
    dist->sigma = 0;

    vector<depthHo> best_compatible_ho;
    
    for (int a=0; a < H.size(); a++) {
        vector<depthHo> compatible_ho;
        
        for (int b=0; b < H.size(); b++) {
            // test if the hypotheses a and b are compatible
            if (chi_test(H[a], H[b], NULL)) {
                compatible_ho.push_back(H[b]); 
            }
        }
        // test if hypothesis 'a' has the required support
        if (compatible.size()-1 >= lambdaN && compatible.size() > best_compatible_depth.size()) {
            compatible_ho.push_back(H[a]); 
            best_compatible_ho = compatible_ho;
        }
    }

    // calculate the parameters of the inverse depth distribution by fusing hypotheses
    if (best_compatible_ho.size() >= lambdaN) {
        getFusion(best_compatible_ho, &dist, NULL);
    }
} 


// INTRA-KEYFRAME DEPTH CHECKING, SMOOTHING, AND GROWING
void intra_keyframe_depth_checking(depthHo** H, int imrows, int imcols) {

    depthHo H_new[imrows][imcols];
    for (int px = 1; px < (imrows - 1); px++) {
        for (int py = 1; py < (imcols - 1); py++) {
            H_new[px][py] = NULL;
            if (H[px][py] == NULL) {
                // check if this pixel is surrounded by at least two pixels that are compatible to each other.
                std::vector<std::vector<depthHo>> best_compatible_ho;
                
                pixelNeighborNeighborSupport (H, px, py, best_compatible_ho);
                
                int max_support = 0;
                int max_support_index = 0;
                for (int c = 0; c < best_compatible_ho.size(); c++) {
                    if (best_compatible_ho[c].size() > max_support) {
                        max_support = best_compatible_ho[c].size();
                        max_support_index = c;
                    }
                }
                
                // potentially grow the reconstruction density
                if (max_support >= 2) {
                    // assign this previous NULL depthHo the average depth and min sigma of its compatible neighbors
                    depthHo fusion;
                    float min_sigma;

                    getFusion(best_compatible_ho[c], &fusion, &min_sigma);

                    H_new[px][py].depth = fusion.depth;
                    H_new[px][py].sigma = min_sigma;
                }

            } else {
                // calculate the support of the pixel's  8 neighbors
                std::vector<depthHo> best_compatible_ho;
                
                pixelNeighborSupport(H, px, py, best_compatible_ho);
                
                if (best_compatible_ho.size() < 2) {
                    // average depth of the retained pixels
                    // set sigma to minimum of neighbor pixels
                    depthHo fusion;
                    float min_sigma;

                    getFusion(best_compatible_ho, &fusion, &min_sigma);

                    H_new[px][py].depth = fusion.depth;
                    H_new[px][py].sigma = min_sigma;

                } else {
                    H_new[px][py] = H[px][py];
                }
            }
        }
    }
    
    for (xnt x = 0; x < imrows; x++) {
        for (int y = 0; y < imcols; y++) {
            H[x][y] = H_new[x][y];
        }
    }
} 

void interKeyframeDepthChecking(const ORB_SLAM::KeyFrame* currentKF, depthHo** H, int imrows, int imcols) {
        std::vector<ORB_SLAM::KeyFrame*> neighbors;
        // option1: could just be the best covisibility keyframes
        neighbors = Kf->GetBestCovisibilityKeyFrames(covisN);
        // option2: could be found in one of the LocalMapping SearchByXXX() methods
        ORB_SLAM::LocalMapping::SearchInNeighbors(); //mpCurrentKeyFrame->updateConnections()...AddConnection()...UpdateBestCovisibles()...
        ORB_SLAM::LocalMapping::mpCurrentKeyFrame->GetBestCovisibilityKeyFrames(covisN); //mvpOrderedConnectedKeyFrames()
        
        // for each pixel of keyframe_i, project it onto each neighbor keyframe keyframe_j
        // and propagate inverse depth
        for (int px = 0; px < imrows; px++) {
            for (int py = 0; py < imcols; py++) {
                if (H[px][py] == NULL) continue; 
                float depthp = H[px][py].depth;
                int compatible_neighbor_keyframes_count = 0; // count of neighboring keyframes in which there is at least one compatible pixel
	        for(int j=0; j<neighbors.size(); j++){ 
		    ORB_SLAM::KeyFrame* pKFj = neighbors[j];
                    // calibration matrix
	            cv::Mat Kj = pKFj -> GetCalibrationMatrix;
		    cv::Mat Xp = Kj*image;
                    // rotation matrix
                    cv::Mat Rcwj = Tcw_.row(2).colRange(0,3);
                    Rcwj = Rcwj.t();
                    // translation matrix
                    cv::Mat tcwj = pKF2->GetTranslation();
                    cv::Mat Tcwj(3,4,CV_32F);
                    Rcwj.copyTo(Tcwj.colRange(0,3));
                    tcwj.copyTo(Tcwj.col(3));
                    
                    // compute the projection matrix to map 3D point from original image to 2D point in neighbor keyframe
                    // Eq (12)
                    xj = (Kj * Rcwj * (1 / depthp) * xp) + Kj * Tcwj; 
                    float depthj = depthp / (Rcwj[2] * xp + depthp * Tcwj[2]); 

                    // find the (float) coordinates of the new point in keyframe_j
                    cv::Mat xyzj = xj * cv::Mat(px, py, depthp);
                    float xj = xyzj[0];  
                    float yj = xyzj[1]; 
                    
                    int compatible_points_count = 0; // count of compatible neighbor pixels
                    std::vector<cv::Point> compatible_points;
                    // look in 4-neighborhood pixel p_j,n around xj for compatible inverse depth
                    for (int nj = floor(xj); nj <= nj + 1; nj++) {
                        for (int ny = floor(yj); ny < ny + 1; ny++) {
                            if (H[nx][ny] == NULL) continue;
                            float depthjn = H[nx][ny].depth; 
                            float sigmajn = H[nx][ny].sigma; 
                            // Eq (13)
                            float test = (depthp - depthjn) * (depthp - depthjn) / (sigmajn * sigmajn);
                            if (test < 3.84) {
                                compatible_points_count++;
                                compatible_points.push_back(cv::Point(nx, ny));
                            }
                        }
                    }
                    
                    // at least one compatible pixel p_j,n must be found in at least lambdaN neighbor keyframes
                    if (compatible_points_count) {
                        compatible_neighbor_keyframes_count++;
                        float depthp_star = 1000;
                        float sum_depth = 0;
                        for (int p; p < compatible_points.size(); p++) {
                            float depthjn = H[compatible_points[p].x][compatible_points[p].y].depth;
                            float sigmajn = H[compatible_points[p].x][compatible_points[p].y].sigma;
                            // equation (14)
                            sum_depth += pow((depthjn - depthp * Rcwj[2] * xp * Tcwj[2]), 2) / (pow(depthjn, 4) * pow(sigmajn, 2)); 
                        } 
                    } 
                }
                // don't retain the inverse depth distribution of this pixel if not enough support in neighbor keyframes
                if (compatible_neighbor_keyframes_count < lambdaN) {
                    H[px][py] = NULL;
                }
            }
        }
    }
} 




////////////////////////
// Utility functions
////////////////////////

void ComputeInvDepthHypothesis(KeyFrame kf, int pixel, float ustar, float ustar_var, float a, float b, float c, depthHo* dh){
  cv::Mat image = kf -> GetImage();

  cv::Mat frame_rot = kf->GetRotation();
  cv::Mat inv_frame_rot =  frame_rot.t();
  cv::Mat frame_translation = kf -> GetTranslation();
  
  cv::Mat transform_data(3,4,CV_32F);
  frame_rot.copytTo(transform_data.colRange(0,3));
  frame_translation.copyTo(transform_data.col(3));

  const float fx = kf -> fx;
  const float cx = kf -> cx;
  cv::Mat calibration_matrix = kf -> GetCalibrationMatrix();
  
  cv::Mat corrected_image = calibrated_matrix * image;
  int ujcx = pixel - cx;
  int vjcx = (a/b) * ujcx + (c/b);

  float inv_pixel_depth = (inv_frame_rot[2]*corrected_image.at<float>(ujcx,vjcx)-fx*inv_frame_rot[0]*corrected_image)/(transform_data[2][ujcx][vjcx]+fx*transform_data[0]);
  
  int ustarcx_min = ustar - cx - sqrt(ustar_var);
  int vstarcx_min = (a/b)*ustarcx_min + (c/b);

  float inv_depth_min = (inv_frame_rot[2]*corrected_image.at<float>(ustarcx_min ,vstarcx_min)-fx*inv_frame_rot[0]*corrected_image)/(-transform_data[2][ustarcx_min][vstarcx_min]+fx*transform_data[0]); 
  
  int ustarcx_max = ustar - cx + sqrt(ustar_var);
  int vstarcx_max = (a/b)*ustarcx_max + (c/b);
  
  float inv_depth_max = (inv_frame_rot[2]*corrected_image.at<float>(ustarcx_max ,vstarcx_max)-fx*inv_frame_rot[0]*corrected_image)/(-transform_data[2][ustarcx_max][vstarcx_max]+fx*transform_data[0]);

  float sigma_depth = max(abs(inv_depth_max),abs(inv_depth_min));

  dh.depth = inv_pixel_depth;
  dh.sigma = sigma_depth;
}

void GetImageGradient(cv::Mat& image, cv::Mat* gradx, cv::Mat* grady, cv::Mat* grad){
  cv::Mat gradx, grady;
	
  cv::Scharr(image, gradx, CV_16S,1,0);
  cv::Scharr(image, grady, CV_16S,0,1);
	
  cv::Mat absgradx, absgrady;

  cv::convertScaleAbs(gradx, absgradx);
  cv::convertScaleAbs(grady, absgrady);
  gradx = absgradx;
  grady = absgrady;
  cv::addWeighted(absgradx,0.5,absgrady,0.5,grad,0);
}

void GetGradientOrientation(int x, int y, cv::Mat& gradx, cv::Mat& grady, float th){
  float valuex = gradx.at<float>(x,y);
  float valuey = grady.at<float>(x,y);
  float th =  cv::fastAtan2(gradx,grady);
}

//might be a good idea to store these when they get calculated during ORB-SLAM.
void GetInPlaneRotation(KeyFrame& k1, KeyFrame& k2, float th){
  vector<cv::KeyPoint> vKPU1 = k1->GetKeyPointsUn();
  DBoW2::FeatureVector vFeatVec1 = k1->GetFeatureVector();
  vector<MapPoint*> vMapPoints1 = k1->GetMapPointMatches();
  cv::Mat Descriptors1 = k1->GetDescriptors();

  vector<cv::KeyPoint> vKPU2 = k2->GetKeyPointsUn();
  DBoW2::FeatureVector vFeatVec2 = k2->GetFeatureVector();
  vector<MapPoint*> vMapPoints2 = k2 ->GetMapPointMatches();
  cv::Mat Descriptors2 = k2->GetDescriptors();

  vector<int> rotHist[histo_length];
  for(int i=0;i<histo_length;i++)
    rotHist[i].reserve(500);DescriptorDistance
  
  const float factor = 1.0f/histo_length;

  DBoW2::FeatureVector::iterator f1it = vFeatVec1.begin();
  DBoW2::FeatureVector::iterator f2it = vFeatVec2.begin();
  DBoW2::FeatureVector::iterator f1end = vFeatVec1.end();
  DBoW2::FeatureVector::iterator f2end = vFeatVec2.end();

  while(f1it != f1end && fit != f2end) {
    if(f1it->first == f2it->first){
      for(size_t i1=0, iend1=f1it->second.size(); i1<iend1; i1++){
        size_t index1 = f1it->second[i1];

        MapPoint* pMP1 = vpMapPoints1[index1];
        if(!pMP1)
          continue;
        if(pMP1->isBad())
          continue;

        cv::Mat d1 = Descriptors1.row(index1);

        int bestDist1 = INT_MAX;
        int bestIndex2 = -1;
        int bestDist2 = INT_MAX;

        for(size_t i2=0, iend2=f2it->second.size(); i2<iend2; i2++){
          size_t index2 = f2it->second[i2];

          MapPoint* pMP2 = vpMapPoints2[index2];
          if(!pMP2)
            continue;
          if(pMP2->isBad())
            continue;

          cv::Mat d2 = Descriptors.row(index2);

          int dist = ORBmatcher::DescriptorDistance(d1,d2);

          if(dist<bestDist1){
            bestDist2 = bestDist1;
            bestDist1 = dist;
            bestIndex2 = index2;
          }
          else if(dist<bestDist2){
            bestDist2 = dist;
          }
        }
        if(bestDist1<th_low){
          if(static_cast<float>(bestDist1)<nnratio*static_cast<float>(bestDist2)){
            float rot = vKPU1[index1].angle - vKPU2[index2].angle;
            if(rot<0.0)
              rot+=360.0f;
            int bin = round(rot*factor);
            if(bin==histo_length)
              bin=0;
            rotHist[bin].push_back(index1);
          }
        }
      }
    }
  }
  //calculate the median angle
  size_t size = rotHist.size();
  std::sort(rotHist.begin(),rotHist.end());

  if(size % 2 == 0){
    th = (rotHist[size/2 - 1] + rotHist[size/2])/2;
  }
  else{
    th = rotHist[size/2];
  }
  return th;
}


void pixelNeighborSupport (const depthHo** H, int px, int py, std::vector<depthHo>& support) {
    support.clear();
    for (int x = px - 1; x <= px + 1; x++) {
        for (int y = py - 1; y <= py + 1; y++) {
            if (x == px && y == py) continue; 
            if (chi_test(H[x][y], H[px][py], NULL)) {
                support.push_back(H[px][py]);
            }
        }
    }
}

void pixelNeighborNeighborSupport (const depthHo** H, int px, int py, std::vector<std::vector<depthHo>& support) {
    support.clear();
    for (int x = px - 1; x <= px + 1; x++) {
        for (int y = py - 1; y <= py + 1; y++) {
            if (x == px && y == py) continue;
            std::vector<depthHo> tempSupport;
            float min_sigma = H[x][y].sigma;
            for (int nx = px - 1; nx <= px + 1; nx++) {
                for (int ny = py - 1; ny <= py + 1; ny++) {
                    if ((nx == px && ny == py) || (nx == x && ny == y)) continue;
                    if (chi_test(H[x][y], H[nx][ny], NULL) {
                        tempSupport.push_back(H[nx][ny]);
                    }
                }
            }
            support.push_back(tempSupport);
        }
    }
}

void getIntensityGradient_D(cv::Mat ImGrad, float* q) {
    float grad_d = (ImGrad.at<float>(uplusone,vplusone) - ImGrad.at<float>(uminone,vminone))/2;
    *q = grad_d;
} 

void getPixelDepth(cv::Mat& R, cv::Mat& T, ORB_SLAM::KeyFrame* kF cv::Mat& Im, int u, float *p) {
    const float fx = kF->fx;
    const float cx = kF->cx;

    cv::Mat K = kF->GetCalibrationMatrix();

    cv::Mat Xp = K*Im;

    int ucx = u - cx;
    int vcx = (a/b)*ucx + (c/b);
    
    float depthp = (R[2]*Xp.at<float>(ucx,vcx)-fx*R[0]*Xp)/(-T[2][ucx][vcx]+fx*T[0]);
    *p = depthp;
} 

bool chiTest(const depthHo ha, const depthHo hb, float* chi_val) {
    float chi_test = (ha.depth - hb.depth)*(ha.depth - hb.depth) / (ha.sigma*ha.sigma) + (ha.depth - hb.depth)*(ha.depth - hb.depth) / (ha.sigma*ha.sigma);
    if (chi_val)
        *chi_val = chi_test;
    return (chi_test < 5.99);
} 

void getFusion(const vector<depthHo> best_compatible_ho, depthHo* hypothesis, float* min_sigma) {
    hypothesis->depth = 0;
    hypothesis->sigma = 0;
    float temp_min_sigma = 0;
    float pjsj =0; // numerator
    float rsj =0; // denominator
    for (int j = 0; j < best_compatible_ho.size(); j++) {
        pjsj += (best_compatible_ho[j].depth / (best_compatible_ho[j].sigma * best_compatible_ho[j].sigma));
        rsj += (1 / (best_compatible_ho[j].sigma * best_compatible_ho[j].sigma));
        if (best_compatible_ho[j].sigma * best_compatible_ho[j].sigma < temp_min_sigma * temp_min_sigma) {
            temp_min_sigma = best_compatible_ho[j].sigma;
        }
    }
    hypothesis->depth = pjsj / rsj;
    hypothesis->sigma = sqrt(1 / rsj);
    if (min_sigma) {
        *min_sigma = temp_min_sigma;
    }
} 
