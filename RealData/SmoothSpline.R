## This code was written by Krishnapriya Tamma in 2017

### Code to read in the ACF-1 and variance data and perform a smooth spline fitting (fig 3)
## Using aspect and slope as example
## setwd
t1a <- read.table("T1_aspect_variance_Cg4.txt") ## result from the calculation of var and acf-1 (matlab)
t2a <- read.table("T2_aspect_variance_Cg4.txt")
t4a <- read.table("T4_aspect_variance_Cg4.txt")

t1s <- read.table("T1_slope_variance_Cg4.txt")
t2s <- read.table("T2_slope_variance_Cg4.txt")
t4s <- read.table("T4_slope_variance_Cg4.txt")

cbind(t1a$V1, c(1:44)) ## as there are 44 bins/moving windows
p1 <- smooth.spline(t1a$V1 ~ c(1:44), spar = 0.6) 
## this value of spar is used for all analyses. See methods for details on why this was chosen
plot(t1a$V1 ~ c(1:44), pch = 16, ylab = "variance in aspect")
lines(p1, lwd = 2)
abline(v = c(13, 9, 22, 26), col = 'gray60', lty = 2, lwd = 3)
p1e <- smooth.spline(v1$V1 ~ c(1:44), spar = 0.6)
plot(v1$V1 ~ c(1:44), pch = 16, ylab = "variance in EVI")
lines(p1e, lwd = 2)
abline(v = c(13, 9, 31, 27), col = 'gray60', lty = 2, lwd = 3)
