# This code was written by Sabiha Majumder in 2016.
# It takes the data of variance/ACF-1 for different driver values and picks up the driver value (or density) at which the metric is maximum.
# The driver value corresponding to maximum spatial variance/ACF-1 is calculated for all values of coarse-graining length. The point at which this converges, is estimated as critical point 


x<-seq(0,0.99,0.01)  # array of the same length as number of driver vlaues
file<-sprintf("file-with-driver-values-and-mean-density.txt");
a=read.table(file);
p<-a[,1];
mean=a[,2];

c=1:32;   #coarse-graining length goes from 1 to 32

pmax<-numeric(length(c))
meanmax<-numeric(length(c))

for (k in c) {
  filename<-sprintf("variance_Cg%d.txt",k)  # Variance/ACF-1 for all values of driver at a given cg-length
  dat1<-read.table(filename);
  dat1<-dat1[,];
  i<-which(dat1[]==max(dat1));  
  pmax[k]<-p[i]
  meanmax[k]<-mean[i]
  
}



plot(meanmax~c,col="dark red",type ="l",lwd=4,ylim=c(0.0,1),ylab="mean cover for variance peak",xlab="C-G length",cex.lab=1.2,col.lab="black")

#x=data.frame(pmax,meanmax)
#write.table(x,"nullmodelvariancepeak.txt")
