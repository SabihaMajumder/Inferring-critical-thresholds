## This code generates the frequency data used to generate fig 3
## this frequency data forms the colour bands in the phase diagram

library(raster)
library(rgdal)
library(fields)

##################################### CAex #########################
##### phase diagram analysis
## first you have to reclassify the EVI data to 5 pc intervals
# read in the EVI map for the Box B
caex <- raster("CAex_MODIS_EVI_2010_AfricaPolygon5.tif")
hist(caex)
## We need a file that contains information about the values and what they should be transformed to
# the dataset is also provided as part of this file
evire <- read.csv("EVI_reclass_5.csv")
## setwd - Africa Bimodal
?reclassify
reevi <- reclassify(caex, evire)
plot(reevi)
writeRaster(reevi, "CAex_EVI_reclass_5pc.tif")

## for each reclassified EVI, get the proportion of the percent EVI in each
## rainfall regime
## 1000-1100----
# g1 is the shapefile for the first rainfallregimes
# crop the raster to only regions that correspond to this rainfall regime
g1 <- readOGR(dsn = getwd(), layer = '1000-1100_final')
reg1 <- crop(reevi, g1)
reg11 <- mask(reg1, g1)
plot(reg11)
# now for this rainfall bin we get the frequency pixels belonging to eacj EVI bin
unique(getValues(reg11))
r <- sort(unique(getValues(reg11)))
d <- c()
for(i in 1:length(r)) {
  j <- r[i]
  p <- length(which(getValues(reg11) == j))/length(which(getValues(reg11)>0))
  d <- c(d, p)
  f <- cbind(r, d)
  colnames(f) <- c("fa", "d")
}

## Repeat this for all the rainfall regimes