## Function to calculate modes from data
find_modes<- function(x) {
  modes <- NULL
  for ( i in 2:(length(x)-1) ){
    if ( (x[i] > x[i-1]) & (x[i] > x[i+1]) ) {
      modes <- c(modes,i)
    }
  }
  if ( length(modes) == 0 ) {
    modes = 'This is a monotonic distribution'
  }
  return(modes)
}

## Use this function to derive modes for your transect data
# (after clipping the transect to the EVI data)
# lets say that the transect raster is saved as pr_1
mymodes_indices <- find_modes(density(pr_1)$y) 
density(pr_1)$y[mymodes_indices]
density(pr_1)$x[mymodes_indices]