## This code was written by Krishnapriya Tamma in 2017

### Code to plot the histogram of EVI for 100 mm rainfall bins (histograms in fig 1)
## Spatial Polygons for each 100 mm rainfall bins is made in QGIS using the raster calculator function
library(raster)
library(rgdal)
## setwd 
# read the EVI raster in 
caex <- raster("CAex_MODIS_EVI_2010_AfricaPolygon5.tif") 
# Example for one 100 mm rainfall bin is demonstrated below
# 1200 - 1300
g3 <- readOGR(dsn = getwd(), layer = "1200_1300_final")
# crop the EVI (which is at the continental scale, only for the rainfall bin of interest)
evi3 <- crop(caex, g3)
evi31 <- mask(evi3, g3)
plot(evi31)
hist(evi31, col = "steelblue4", font = 2, xlim = c(0,10000), main = "", xlab = "", ylab = "")
d <- density(evi31)
plot(d, lwd = 2, xlim = c(0,10000), bty = 'n', ylab = "", xlab = "", bg = 'transparent', main = "")
polygon(d, col = "steelblue4")
## repeat for all bins
