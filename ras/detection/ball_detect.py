import numpy as np
import cv2 
import scipy as sci
import skimage as ski
import time
import math

class Ball_Detect:
    def __init__(self, detect_xanh= False, image_width=320, image_height = 240, show_debug= False):
        
        self.image_width = image_width
        self.image_height = image_height
        
        self.lower_blue = np.array([100, 150, 90])
        self.upper_blue = np.array([130, 255, 255])
        
        self.lower_red1 = np.array([0, 100, 20])
        self.upper_red1 = np.array([10, 255, 255])
        self.lower_red2 = np.array([160,100,20])
        self.upper_red2 = np.array([179,255,255])
        
        self.lower_purple = np.array([120, 50, 50])
        self.upper_purple = np.array([165, 255, 255])

        #remove small object < 300
        self.min_object_area = 200
        self.max_object_area = 60000
        self.detect_xanh = detect_xanh
        self.show_debug = show_debug
        
        self.center_ball = [0,0]
        
    def detect_image(self, image):
        bgr = cv2.resize(image, (self.image_width, self.image_height))
        rgb = cv2.cvtColor(bgr, cv2.COLOR_BGR2RGB)
        # rgb = cv2.bilateralFilter(rgb, 15, 75, 75)
        blur = cv2.blur(rgb,(5,5))
        hsv = cv2.cvtColor(blur, cv2.COLOR_RGB2HSV)
        hsv_increased = self.increase_brightness_hsv_image(hsv, -40)
        
        if self.detect_xanh:
            binary = self.extract_blue_color(hsv_increased)
        else:
            binary = self.extract_red_color(hsv_increased)
            
        seg = self.dilate_and_fill_holes(binary)
        seg_uint8 = self.bool_image_to_uint8(seg)
        cnts = self.find_contours(seg_uint8)
        cnts, removed = self.remove_small_object(seg_uint8, cnts)
        centerballs = []
        if len(cnts) > 0:
                c = max(cnts, key=cv2.contourArea)
                # c = np.max(blue_cnts)
                M = cv2.moments(c)
                cX = int(M["m10"] / M["m00"])
                cY = int(M["m01"] / M["m00"])
                centerballs.append([cX, cY])

        if len(centerballs) > 0:
            self.center_ball = min(centerballs, key=lambda x: math.sqrt((x[0] - self.image_width//2)**2 + (x[1] - self.image_height//2)**2))
        else:
            self.center_ball = [-1,-1]
            
        if self.show_debug:
            cv2.imshow("removed", np.uint8(removed))
            cv2.imshow("binary", np.uint8(binary))
            
        # self.watershed2(rgb, removed)
         
        if self.show_debug:
            cv2.imshow("bgr", bgr)
            cv2.imshow("bgr increased", cv2.cvtColor(hsv_increased, cv2.COLOR_HSV2BGR))
    
    def increase_brightness_hsv_image(self, hsv, value):
        h, s, v = cv2.split(hsv)
        v = cv2.add(v, value)
        v[v > 255] = 255
        v[v < 0] = 0
        final_hsv = cv2.merge((h, s, v))
        return final_hsv
    
    def extract_blue_color(self, hsv):
        mask = cv2.inRange(hsv, self.lower_blue, self.upper_blue)
        return mask
    
    def extract_red_color(self, hsv):
        mask1 = cv2.inRange(hsv, self.lower_red1, self.upper_red1)
        mask2 = cv2.inRange(hsv, self.lower_red2, self.upper_red2)
        return mask1 + mask2
        
    def extract_purple_color(self, hsv):
        mask = cv2.inRange(hsv, self.lower_purple, self.upper_purple)
        return mask
    
    def dilate_and_fill_holes(self, binary):
        mask = ski.morphology.binary_dilation(binary)
        mask = ski.morphology.binary_dilation(mask)
        mask_fill_holes = sci.ndimage.binary_fill_holes(mask)
        return mask_fill_holes
    
    def bool_image_to_uint8(self,img_bool):
        img_uint8 = img_bool.astype(np.uint8)
        img_uint8 *= 255
        return img_uint8
    
    def find_contours(self, img_bin):
        cnts,_ = cv2.findContours(img_bin, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
        return cnts
    
    def remove_small_object(self, image, cnts):
        new_cnts = []
        for cnt in cnts:
            area = cv2.contourArea(cnt)
            if area > self.min_object_area and area < self.max_object_area:
                new_cnts.append(cnt)
        
        draw = np.zeros(shape=image.shape)
        cv2.drawContours(draw, new_cnts, -1, color=(255, 255, 255), thickness=cv2.FILLED)
        return new_cnts, draw

    def watershed(self, image):
        image = image.astype(np.uint16)
        distance = sci.ndimage.distance_transform_edt(image)
        coords = ski.feature.peak_local_max(distance, labels=image, min_distance = 20)
        mask = np.zeros(distance.shape, dtype=bool)
        mask[tuple(coords.T)] = True
        markers, _ = sci.ndimage.label(mask)
        labels = ski.segmentation.watershed(-distance, markers, mask=image)
        return labels
    
    def watershed2(self, image, image_bin):
        image_bin = np.uint8(image_bin)
        dist_transform = cv2.distanceTransform(image_bin,cv2.DIST_L2,0)
        ret, sure_fg = cv2.threshold(dist_transform,0.35*dist_transform.max(),255,0)
        sure_fg = np.uint8(sure_fg)
        unknown = cv2.subtract(image_bin,sure_fg)
        ret, markers = cv2.connectedComponents(sure_fg)
        markers = markers+1
        markers[unknown==1] = 0
        watershed = cv2.watershed(image,markers)
        img = image.copy()
        img[watershed == -1] = [255,0,0]
        
        if self.show_debug:
            cv2.imshow("watershed", img)
        return img

    
    
        