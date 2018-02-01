%%
evi=csvread('Transect1_EVI.csv');

Nx=49;Ny=382;

subsize=30;
nx= floor(Nx/subsize);ny= floor(Ny/subsize);

for i=1:nx
    for j=1:ny
        
        submatrix = evi(((i-1)*subsize+1):(i*subsize),((j-1)*subsize+1):(j*subsize));
        
        for k=1:subsize
            for l=1:subsize
                dlmwrite('Transect1_EVI.txt',submatrix(k,l),'-append');
            end
        end
       
    end 
end

%%
evi=csvread('Transect2_EVI.csv');

Nx=49;Ny=382;

subsize=30;
nx= floor(Nx/subsize);ny= floor(Ny/subsize);

for i=1:nx
    for j=1:ny
        
        submatrix = evi(((i-1)*subsize+1):(i*subsize),((j-1)*subsize+1):(j*subsize));
        
        for k=1:subsize
            for l=1:subsize
                dlmwrite('Transect2_EVI.txt',submatrix(k,l),'-append');
            end
        end
       
    end 
end

%%
evi=csvread('Transect4_EVI.csv');

Nx=379;Ny=47;

subsize=30;
nx= floor(Nx/subsize);ny= floor(Ny/subsize);

for i=1:nx
    for j=1:ny
        
        submatrix = evi(((i-1)*subsize+1):(i*subsize),((j-1)*subsize+1):(j*subsize));
        
        for k=1:subsize
            for l=1:subsize
                dlmwrite('Transect4_EVI.txt',submatrix(k,l),'-append');
            end
        end
       
    end 
end

%% Soil data for the transects
%%
evi=csvread('Transect1_Soil.csv');

Nx=13;Ny=103;

subsize=30;
nx= floor(Nx/subsize);ny= floor(Ny/subsize);

for i=1:nx
    for j=1:ny
        
        submatrix = evi(((i-1)*subsize+1):(i*subsize),((j-1)*subsize+1):(j*subsize));
        
        for k=1:subsize
            for l=1:subsize
                dlmwrite('Transect1_Soil.txt',submatrix(k,l),'-append');
            end
        end
       
    end 
end

%%
%%
evi=csvread('Transect2_Soil.csv');

Nx=14;Ny=103;

subsize=30;
nx= floor(Nx/subsize);ny= floor(Ny/subsize);

for i=1:nx
    for j=1:ny
        
        submatrix = evi(((i-1)*subsize+1):(i*subsize),((j-1)*subsize+1):(j*subsize));
        
        for k=1:subsize
            for l=1:subsize
                dlmwrite('Transect2_Soil.txt',submatrix(k,l),'-append');
            end
        end
       
    end 
end

%%
evi=csvread('Transect4_Soil.csv');

Nx=102;Ny=13;

subsize=30;
nx= floor(Nx/subsize);ny= floor(Ny/subsize);

for i=1:nx
    for j=1:ny
        
        submatrix = evi(((i-1)*subsize+1):(i*subsize),((j-1)*subsize+1):(j*subsize));
        
        for k=1:subsize
            for l=1:subsize
                dlmwrite('Transect4_Soil.txt',submatrix(k,l),'-append');
            end
        end
       
    end 
end