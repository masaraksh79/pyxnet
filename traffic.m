# Pyxis simulation production graphing
# Traffic analysis

clear
more off

fpath='F:\Work\OMnetPP\omnetpp-5.0\samples\pyxnet\test_traffic\'

Files25M0={'PyxisTraffic25M0.sim.allocatedBps',
           'PyxisTraffic25M0.sim.requestedBps'
           'PyxisTraffic25M0.sim.business',
           'PyxisTraffic25M0.sim.collisionsAtBase',
           'PyxisTraffic25M0.sim.efficiency'}

Files25M1={'PyxisTraffic25M1.sim.allocatedBps',
           'PyxisTraffic25M1.sim.requestedBps'
           'PyxisTraffic25M1.sim.business',
           'PyxisTraffic25M1.sim.collisionsAtBase',
           'PyxisTraffic25M1.sim.efficiency'}

Files25M2={'PyxisTraffic25M2.sim.allocatedBps',
           'PyxisTraffic25M2.sim.requestedBps'
           'PyxisTraffic25M2.sim.business',
           'PyxisTraffic25M2.sim.collisionsAtBase',
           'PyxisTraffic25M2.sim.efficiency'}

Files25M3={'PyxisTraffic25M3.sim.allocatedBps',
           'PyxisTraffic25M3.sim.requestedBps'
           'PyxisTraffic25M3.sim.business',
           'PyxisTraffic25M3.sim.collisionsAtBase',
           'PyxisTraffic25M3.sim.efficiency'}
           

Files30M0={'PyxisTraffic30M0.sim.allocatedBps',
           'PyxisTraffic30M0.sim.requestedBps'
           'PyxisTraffic30M0.sim.business',
           'PyxisTraffic30M0.sim.collisionsAtBase',
           'PyxisTraffic30M0.sim.efficiency'}

Files30M1={'PyxisTraffic30M1.sim.allocatedBps',
           'PyxisTraffic30M1.sim.requestedBps'
           'PyxisTraffic30M1.sim.business',
           'PyxisTraffic30M1.sim.collisionsAtBase',
           'PyxisTraffic30M1.sim.efficiency'}

Files30M2={'PyxisTraffic30M2.sim.allocatedBps',
           'PyxisTraffic30M2.sim.requestedBps'
           'PyxisTraffic30M2.sim.business',
           'PyxisTraffic30M2.sim.collisionsAtBase',
           'PyxisTraffic30M2.sim.efficiency'}

Files30M3={'PyxisTraffic30M3.sim.allocatedBps',
           'PyxisTraffic30M3.sim.requestedBps'
           'PyxisTraffic30M3.sim.business',
           'PyxisTraffic30M3.sim.collisionsAtBase',
           'PyxisTraffic30M3.sim.efficiency'}
           
Files35M0={'PyxisTraffic35M0.sim.allocatedBps',
           'PyxisTraffic35M0.sim.requestedBps'
           'PyxisTraffic35M0.sim.business',
           'PyxisTraffic35M0.sim.collisionsAtBase',
           'PyxisTraffic35M0.sim.efficiency'}

Files35M1={'PyxisTraffic35M1.sim.allocatedBps',
           'PyxisTraffic35M1.sim.requestedBps'
           'PyxisTraffic35M1.sim.business',
           'PyxisTraffic35M1.sim.collisionsAtBase',
           'PyxisTraffic35M1.sim.efficiency'}

Files35M2={'PyxisTraffic35M2.sim.allocatedBps',
           'PyxisTraffic35M2.sim.requestedBps'
           'PyxisTraffic35M2.sim.business',
           'PyxisTraffic35M2.sim.collisionsAtBase',
           'PyxisTraffic35M2.sim.efficiency'}

Files35M3={'PyxisTraffic35M3.sim.allocatedBps',
           'PyxisTraffic35M3.sim.requestedBps'
           'PyxisTraffic35M3.sim.business',
           'PyxisTraffic35M3.sim.collisionsAtBase',
           'PyxisTraffic35M3.sim.efficiency'}
           
Files40M0={'PyxisTraffic40M0.sim.allocatedBps',
           'PyxisTraffic40M0.sim.requestedBps'
           'PyxisTraffic40M0.sim.business',
           'PyxisTraffic40M0.sim.collisionsAtBase',
           'PyxisTraffic40M0.sim.efficiency'}

Files40M1={'PyxisTraffic40M1.sim.allocatedBps',
           'PyxisTraffic40M1.sim.requestedBps'
           'PyxisTraffic40M1.sim.business',
           'PyxisTraffic40M1.sim.collisionsAtBase',
           'PyxisTraffic40M1.sim.efficiency'}

Files40M2={'PyxisTraffic40M2.sim.allocatedBps',
           'PyxisTraffic40M2.sim.requestedBps'
           'PyxisTraffic40M2.sim.business',
           'PyxisTraffic40M2.sim.collisionsAtBase',
           'PyxisTraffic40M2.sim.efficiency'}

Files40M3={'PyxisTraffic40M3.sim.allocatedBps',
           'PyxisTraffic40M3.sim.requestedBps'
           'PyxisTraffic40M3.sim.business',
           'PyxisTraffic40M3.sim.collisionsAtBase',
           'PyxisTraffic40M3.sim.efficiency'}
           
Files45M0={'PyxisTraffic45M0.sim.allocatedBps',
           'PyxisTraffic45M0.sim.requestedBps'
           'PyxisTraffic45M0.sim.business',
           'PyxisTraffic45M0.sim.collisionsAtBase',
           'PyxisTraffic45M0.sim.efficiency'}

Files45M1={'PyxisTraffic45M1.sim.allocatedBps',
           'PyxisTraffic45M1.sim.requestedBps'
           'PyxisTraffic45M1.sim.business',
           'PyxisTraffic45M1.sim.collisionsAtBase',
           'PyxisTraffic45M1.sim.efficiency'}

Files45M2={'PyxisTraffic45M2.sim.allocatedBps',
           'PyxisTraffic45M2.sim.requestedBps'
           'PyxisTraffic45M2.sim.business',
           'PyxisTraffic45M2.sim.collisionsAtBase',
           'PyxisTraffic45M2.sim.efficiency'}

Files45M3={'PyxisTraffic45M3.sim.allocatedBps',
           'PyxisTraffic45M3.sim.requestedBps'
           'PyxisTraffic45M3.sim.business',
           'PyxisTraffic45M3.sim.collisionsAtBase',
           'PyxisTraffic45M3.sim.efficiency'}
           
Files50M0={'PyxisTraffic50M0.sim.allocatedBps',
           'PyxisTraffic50M0.sim.requestedBps'
           'PyxisTraffic50M0.sim.business',
           'PyxisTraffic50M0.sim.collisionsAtBase',
           'PyxisTraffic50M0.sim.efficiency'}

Files50M1={'PyxisTraffic50M1.sim.allocatedBps',
           'PyxisTraffic50M1.sim.requestedBps'
           'PyxisTraffic50M1.sim.business',
           'PyxisTraffic50M1.sim.collisionsAtBase',
           'PyxisTraffic50M1.sim.efficiency'}

Files50M2={'PyxisTraffic50M2.sim.allocatedBps',
           'PyxisTraffic50M2.sim.requestedBps'
           'PyxisTraffic50M2.sim.business',
           'PyxisTraffic50M2.sim.collisionsAtBase',
           'PyxisTraffic50M2.sim.efficiency'}

Files50M3={'PyxisTraffic50M3.sim.allocatedBps',
           'PyxisTraffic50M3.sim.requestedBps'
           'PyxisTraffic50M3.sim.business',
           'PyxisTraffic50M3.sim.collisionsAtBase',
           'PyxisTraffic50M3.sim.efficiency'}

Files55M0={'PyxisTraffic55M0.sim.allocatedBps',
           'PyxisTraffic55M0.sim.requestedBps'
           'PyxisTraffic55M0.sim.business',
           'PyxisTraffic55M0.sim.collisionsAtBase',
           'PyxisTraffic55M0.sim.efficiency'}

Files55M1={'PyxisTraffic55M1.sim.allocatedBps',
           'PyxisTraffic55M1.sim.requestedBps'
           'PyxisTraffic55M1.sim.business',
           'PyxisTraffic55M1.sim.collisionsAtBase',
           'PyxisTraffic55M1.sim.efficiency'}

Files55M2={'PyxisTraffic55M2.sim.allocatedBps',
           'PyxisTraffic55M2.sim.requestedBps'
           'PyxisTraffic55M2.sim.business',
           'PyxisTraffic55M2.sim.collisionsAtBase',
           'PyxisTraffic55M2.sim.efficiency'}

Files55M3={'PyxisTraffic55M3.sim.allocatedBps',
           'PyxisTraffic55M3.sim.requestedBps'
           'PyxisTraffic55M3.sim.business',
           'PyxisTraffic55M3.sim.collisionsAtBase',
           'PyxisTraffic55M3.sim.efficiency'}

           
FilesUnitsM0 = {Files25M0,Files30M0,Files35M0,Files40M0,Files45M0,Files50M0,Files55M0}            
FilesUnitsM1 = {Files25M1,Files30M1,Files35M1,Files40M1,Files45M1,Files50M1,Files55M1}            
FilesUnitsM2 = {Files25M2,Files30M2,Files35M2,Files40M2,Files45M2,Files50M2,Files55M2}            
FilesUnitsM3 = {Files25M3,Files30M3,Files35M3,Files40M3,Files45M3,Files50M3,Files55M3}            

files=arFiles
path=fpath
################################################################################
# Plot for M0/M1/M2 and M3 traffic loads
################################################################################
xAxis={25,30,35,40,45,50,55}

elmInEachFile=10

figure(1)

# TODO: replace with relevant scenario code

g={}
h={}
a={}
prm=1

for k = 1:elmInEachFile
  for j = 1:numel(xAxis)
    g = load("-ascii", char( strcat( path, files{1,j}{prm}) ))
    h(j) = g(k)
  endfor
  a{k}=h
endfor

g={}
h={}
r={}
prm=2

for k = 1:elmInEachFile
  for j = 1:numel(xAxis)
    g = load("-ascii", char( strcat( path, files{1,j}{prm}) ))
    h(j) = g(k)
  endfor
  r{k}=h
endfor

hold on
for k = 1:elmInEachFile
  plot(cell2mat(xAxis),cell2mat(a{1,k}),"b-*", cell2mat(xAxis),cell2mat(r{1,k}),'r:o')
endfor
hold off

xlabel("nodes")
ylabel("bps", "rotation", 0)
legend("allocated","requested", "location", "northwest")
grid("on") 

################################################################################
# Pyxis business, efficiency and collisions at the base
################################################################################
figure(2)
xAxis={50,60,70,80,90,100,110,120}
# business
g={}
h={}
b={}
prm=3

for k = 1:elmInEachFile
  for j = 1:numel(xAxis)
    g = load("-ascii", char( strcat( path, files{1,j}{prm}) ))
    h(j) = g(k)
  endfor
  b{k}=h
endfor

# collisions at Base
g={}
h={}
c={}
prm=4

for k = 1:elmInEachFile
  for j = 1:numel(xAxis)
    g = load("-ascii", char( strcat( path, files{1,j}{prm}) ))
    h(j) = g(k)
  endfor
  c{k}=h
endfor

# efficiency
g={}
h={}
e={}
prm=5

for k = 1:elmInEachFile
  for j = 1:numel(xAxis)
    g = load("-ascii", char( strcat( path, files{1,j}{prm}) ))
    h(j) = g(k)
  endfor
  e{k}=h
endfor

hold on
for k = 1:elmInEachFile
  plot(cell2mat(xAxis),cell2mat(b{1,k}),'r:o', cell2mat(xAxis),cell2mat(c{1,k}),'g--o',cell2mat(xAxis),cell2mat(e{1,k}),'y-o')
endfor
hold off
xlabel("nodes")
legend("business", "collisions", "efficiency", "location", "northwest")
grid("on") 
