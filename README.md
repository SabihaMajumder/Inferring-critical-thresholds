# Inferring-critical-points

#Codes and Data for "Inferring critical thresholds of ecosystem transitions using spatial data", by Sabiha Majumder, Krishnapriya Tamma, Sriram Ramaswamy and Vishwesha Guttal 

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

## REAL DATA ANALYSES
The real data analyses is done across different software and resources including Google Engine Engine, QGIS, and R. 
The following are the steps that can be followed to obtain critical points/thresholds from real data.

## Obtaining the data
The data for EVI for each box is accessed from GEE and downloaded to the hard-disk for further processing. The other datasets are obtained from various sources and directly accessed in QGIS/R. See the Section 3.2 in Methods, 'Application of our method to real data' for more information on where the data were retrieved from. 

## Processing of data in QGIS:
### Creating the transects
Transects can be created using the Layer / Create Layer / New Shapefile Layer. Using the toggle option a new polygon corresponding to the desired location and dimension of the transect can be made. Ensure that the transect is a closed polygon. 

### Clipping the EVI data to the transects
The EVI raster corresponds to data at the box-scale. To obtain EVI data for the transect, read the EVI raster and the shapefile into QGIS, then perform: Raster / Extraction / Clipper (clip to the mask, which in this case is the transect shapefile)
This can then be read into R and matlab for further analyses / plotting. 

### Creating the polygons for the 100 mm rainfall bins
Read the raster for the mean annual rainfall. Use Raster Calculator to obtain the pixels that fall within the desired data range. To do this, use '(MAR >= 1000) AND (MAR <= 1100)' (MAR = rastre for mean annual rainfall). Pixels that are TRUE for this condition are given a value 1, while those that do not meet the condition are given a value 0. Convert into a polygon (Raster / Conversion / Polygonise)
Select the region of interest and save as shapefile (Save as).

## Code to generate histograms 
(All code by Krishnapriya Tamma)
An R code (Histograms.R) to generate histograms from EVI data for each 100 mm rainfall bin. The EVI data can be obtained from QGIS. 
Before the next step, make transects and obtain EVI/Elevation/Slope/Aspect/Soil data for the transects as described above (Step 1 and 2 of 'Processing data in QGIS').

## Code to generate the state diagrams (phase diagrams) 
(All code by Krishnapriya Tamma)
An R code (Code_to_generate_EVIfrequencies_phaseDiagram.R) to obtain the frequencies of the different EVI bins for each of the 100mm rainfall bins. This helps generate the csv file corresponding to 'PhaseDiagramFrequencies_25pc_Australia.csv' which is used in the R code below to actually generate the phase diagram. 
We also include a code (Code_FindingModes.R) to identify modes. Might require some manual inspection to ensure correct modes are being returned.  
An R code (PhaseDiagram.R) to use the frequency of EVI in each rainfall bin to generate the state diagrams as depicted in the paper. This file includes code to plot the modes. 

Two csv files that are needed to generate the phase diagram for Box A (Australia) are included. These are 
     - Australia_polygon3_S-shapedCurve.csv
     - PhaseDiagramFrequencies_25pc_Australia.csv

## Code to calculate the spatial variance and autocorrelation-lag 1 from the real data/transects
Includes
     - Code to convert csv to txt file (Code by Sabiha Majumder)
     - A matlab code (Code by csvTodat_matrices.m) to order the data such that moving window analyses can be carried out.  
     - Code to calculate spatial indicators (Code by coarse_grained_indicators.cpp) 






