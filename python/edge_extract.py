# -*- coding: utf-8 -*-
"""
# project: edge extract
# author:  xhj
# email:   1124418652@qq.com
# date:    2018 9/6
"""

import time
import numpy as np 
import matplotlib.pyplot as plt 
from PIL import Image 

def change_to_binary(img, thresold, value, mod = "normal"):
	height = img.shape[0]
	width = img.shape[1]
	binary_img = np.zeros((height, width))

	if "normal" == mod.lower():

		for i in range(height):
			for j in range(width):
				if img[i][j] >= thresold: 
					binary_img[i][j] = value
				else:
					binary_img[i][j] = 0
	
	else:
		for i in range(height):
			for j in range(width):
				if img[i][j] <= thresold:
					binary_img[i][j] = value 
				else:
					binary_img[i][j] = 0
	return binary_img

def get_contours(binary_img, mod = "sobel"):
	height = binary_img.shape[0]
	width = binary_img.shape[1]
	tmp_img = np.zeros((height+2, width+2))
	res_img = np.zeros((height, width))

	i = 0
	while i < height:
		j = 0
		while j < width:
			tmp_img[i+1][j+1] = binary_img[i][j]
			j += 1
		i += 1 

	if "sobel" == mod:
		kernal_x = np.array([[-1, 0, 1],
						    [-2, 0, 2],
						    [-1, 0, 1]])
		kernal_y = np.array([[-1, -2, -1],
						    [0, 0, 0],
						    [1, 2, 1]])

		for i in range(1, height+1):
			for j in range(1, width+1):
				for k in [-1, 0, 1]:
					for l in [-1, 0, 1]:
						res_img[i-1][j-1] += tmp_img[i+k][j+l] * \
											kernal_x[1+k][1+l]
				if res_img[i-1][j-1] >= 100 or res_img[i-1][j-1] <= -100:
					res_img[i-1][j-1] = 255
				else:
					res_img[i-1][j-1] = 0
		return res_img

	elif "laplacian" == mod:
		kernal = np.array([[-1, -1, -1],
						   [-1, 8, -1],
						   [-1, -1, -1]])
		for i in range(1, height+1):
			for j in range(1, width+1):
				for k in [-1, 0, 1]:
					for l in [-1, 0, 1]:
						res_img[i-1][j-1] += tmp_img[i+k][j+l] * \
											kernal[1+k][1+l]
				if res_img[i-1][j-1] >= 100 or res_img[i-1][j-1] <= -100:
					res_img[i-1][j-1] = 255
				else:
					res_img[i-1][j-1] = 0
		return res_img

def main():
	path = "211.jpg"
	img = np.array(Image.open(path).convert("L"))
	binary_im = change_to_binary(img, 125, 255)
	res_img = get_contours(binary_im, "laplacian")
	res_img = Image.fromarray(res_img)
	plt.imshow(res_img)
	plt.show()

if __name__ == '__main__':
	main()
