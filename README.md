# Inferring-critical-points

#Codes and Data for "Inferring critical thresholds of ecosystem transitions using spatial data", (https://doi.org/10.1101/187799)

## Model
Four C++ codes (homogeneous_driver_model.cpp, gradient_driver_model.cpp, grazing_model(Kefi2007,Schneider2017).cpp, null_model.cpp) for the spatially-explicit models used in the paper to produce the spatial patterns and transitions, written by Sabiha Majumder. To run this code, use any latest linux OS. We have run this on Ubuntu 12.04. It is expected to work on other OS as well, if you have the compilers, but we haven't tested. 

To run this code, type the following command on the command prompt.

```
g++ -o sptime homogeneous_driver_model.cpp
```
This will compile the C++ code and provide an executable named sptime. Now execute this on the command prompt:

```
./sptime &
```
 
##Spatial Indicator codes to analyse simulation data (by Sabiha Majumder)

1. A C++ code (coarse_grained_indicators.cpp) to calculate two spatial indicators (Spatial variance and spatial correlation). Put this code in the same folder that contains the spatial matrices obtained by the codes above. Follow the same procedure as above to create the executable, but with different names for C++ code and the executable.

2. Code to calculate driver value where spatial indicators are maximum (by Sabiha Majumder)

3. An R code (calculate_CP.R) to calculate driver value where spatial indicators are maximum for each coarse graining length. 

## Real Data
Processing of data in QGIS:

### Creating the transects
Transects can be created using the Layer / Create Layer / New Shapefile Layer. Using the toggle option a new polygon corresponding to the desired location and dimension of the transect can be made.

### Clipping the EVI data to the transects
Raster / Extraction / Clipper
This can then be read into R and matlab for further analyses / plotting

### Creating the polygons for the 100 mm rainfall bins
Read the raster for the mean annual rainfall. Use Raster Calculator to obtain the pixels that fall within the desired data range. Convert this into a polygon, select the pixels of interest and save separately. 

###Code to generate histograms (by Krishnapriya Tamma)
1. An R code (Histograms.R) to generate histograms from EVI data for each 100 mm rainfall bin. The EVI data can be obtained from QGIS. 
Before the next step, make transects and obtain EVI/Elevation/Slope/Aspect/Soil data for the transects as described above (Step 1 and 2 of 'Processing data in QGIS')

2. Code to convert csv to txt file (by Sabiha Majumder)

3. A matlab code (csvTodat_matrices.m) to order the data such that moving window analyses can be carried out.  

4. Code to calculate spatial indicators (coarse_grained_indicators.cpp) 

5. Code to generate the state diagrams (by Krishnapriya Tamma)
An R code (PhaseDiagram.R) to use the frequency of EVI in each rainfall bin to generate the state diagrams as depicted in the paper. This file includes code to plot the modes. 




