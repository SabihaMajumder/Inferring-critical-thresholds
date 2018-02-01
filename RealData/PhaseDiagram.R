## This code was written by Krishnapriya Tamma in 2017

### Code to plot for Phase diagram (fig 4)
library(fields)

### AUSTRALIA; BOX A
# setwd to  location of data
shpa <- read.csv("Australia_polygon3_S-shapedCurve.csv", header = T)
# this file contains the value of the modes from each histogram (obtained using Histogram.R)

## this file below contains the frequency of pixels for each EVI bin for each rainfall bin. 
# This was generated using the clipped EVI dataset for each rainfall bin (generated in Histograms.R)
# What one ends up with is a matrix of EVI x Rainfall and the values are frequencies. 
ph <- read.csv("PhaseDiagramFrequencies_25pc_Australia.csv", header = T, row.names = 1)
ph1 <- as.matrix(ph)
pht <- t(ph1)
colb <- c("#ffffe5", "#fff7bc", "#fee391", "#fec44f", "#fe9929", "#ec7014", "#cc4c02", "#993404", "#662506")

# identifying the points which are differing by less than 25% (see Fig legend for details)
pt1 <- which(shpa[1:23,4] <= 0.25) # 1800-1900
pt2 <- pt1[c(1,3,4,5)]
pt3 <- which(shpa[1:23,4] > 0.25)
pt4 <- which(shpa[1:23,4] == NA)
pht1 <- pht[1:13,1:23] # 47.5 # 60
#use image from library fields to plot the background heat map that is based on freq distribution
image(pht1, col = designer.colors(n=30, col = colb), bty = "n", legend.only = FALSE, xaxt = "n", yaxt = "n")
axis(1, at = seq(0,1,length.out=13)[c(1, 7,13)], labels = c("600-700", "1200-1300","1800-1900"), font = 2, cex.axis = 2)
axis(2, at = seq(0,1,length.out=23)[c(10, 23)], labels = c("2000-2250", "5250-5500"), font = 2, cex.axis = 2)
points((shpa[1:23,3]-1)/12, shpa[,5]/55, type = 'n', xlab = "", ylab = "" , bty = "n") 
# the '/12' allows you to adjust the x-axis, determine this by observing your data. 
points(x=(shpa[pt2,3]-1)/12, y=shpa[pt2,5]/55, cex = 2, pch = 16, col = 'gray60')
points(x=(shpa[pt3,3]-1)/12, y=shpa[pt3,5]/55, cex = 2, pch = 16, col = 'black')
#rect((5.5-1)/15, 2.5/75, (9-1)/15, 75/75)
