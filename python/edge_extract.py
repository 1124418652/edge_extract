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

def get_contours(binary_img, thresold = 100, mod = "sobel"):
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
		res_tmp = res_img.copy()
		for i in range(1, height+1):
			for j in range(1, width+1):
				for k in [-1, 0, 1]:
					for l in [-1, 0, 1]:
						res_img[i-1][j-1] += tmp_img[i+k][j+l] * \
											kernal_x[1+k][1+l]
						res_tmp[i-1][j-1] += tmp_img[i+k][j+l] * \
											kernal_y[1+k][1+l]
				if res_img[i-1][j-1] >= thresold or res_img[i-1][j-1] <= -thresold:
					res_img[i-1][j-1] = 255
				else:
					res_img[i-1][j-1] = 0
				if res_tmp[i-1][j-1] >= thresold or res_tmp[i-1][j-1] <= -thresold:
					res_tmp[i-1][j-1] = 255
				else:
					res_tmp[i-1][j-1] = 0
		return res_img + res_tmp

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

def OTSU(img_array):
	height = img_array.shape[0]
	width = img_array.shape[1]
	count_pixel = np.zeros(256)

	for i in range(height):
		for j in range(width):
			count_pixel[int(img_array[i][j])] += 1 

	# fig = plt.figure()
	# ax = fig.add_subplot(111)
	# ax.bar(np.linspace(0, 255, 256), count_pixel)
	# ax.set_xlabel("pixels")
	# ax.set_ylabel("num")
	# plt.show()

	max_variance = 0.0
	best_thresold = 0
	for thresold in range(256):
		n0 = count_pixel[:thresold].sum()
		n1 = count_pixel[thresold:].sum()
		w0 = n0 / (height * width)
		w1 = n1 / (height * width)
		u0 = 0.0
		u1 = 0.0
		
		for i in range(thresold):
			u0 += i * count_pixel[i]
		for j in range(thresold, 256):
			u1 += j * count_pixel[j]
		
		u = u0 * w0 + u1 * w1 
		tmp_var = w0 * np.power((u - u0), 2) + w1 * np.power((u - u1), 2)

		if tmp_var > max_variance:
			best_thresold = thresold
			max_variance = tmp_var

	return best_thresold

def main():
	path = "211.jpg"
	img = np.array(Image.open(path).convert("L"))
	print(OTSU(img))

	start = time.time()
	binary_im = change_to_binary(img, OTSU(img), 255, "inverse")
	end1 = time.time()
	print(end1 - start)

	plt.imshow(Image.fromarray(binary_im))

	res_img = get_contours(binary_im, 100, "sobel")
	end2 = time.time()
	print(end2 - end1)
	res_img = Image.fromarray(res_img)
	plt.imshow(res_img)
	plt.show()

if __name__ == '__main__':
	main()
