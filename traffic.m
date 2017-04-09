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
           
Files25M4={'PyxisTraffic25M4.sim.allocatedBps',
           'PyxisTraffic25M4.sim.requestedBps'
           'PyxisTraffic25M4.sim.business',
           'PyxisTraffic25M4.sim.collisionsAtBase',
           'PyxisTraffic25M4.sim.efficiency'}

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
           
Files30M4={'PyxisTraffic30M4.sim.allocatedBps',
           'PyxisTraffic30M4.sim.requestedBps'
           'PyxisTraffic30M4.sim.business',
           'PyxisTraffic30M4.sim.collisionsAtBase',
           'PyxisTraffic30M4.sim.efficiency'}

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
           
Files35M4={'PyxisTraffic35M4.sim.allocatedBps',
           'PyxisTraffic35M4.sim.requestedBps'
           'PyxisTraffic35M4.sim.business',
           'PyxisTraffic35M4.sim.collisionsAtBase',
           'PyxisTraffic35M4.sim.efficiency'}
           
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

Files40M4={'PyxisTraffic40M4.sim.allocatedBps',
           'PyxisTraffic40M4.sim.requestedBps'
           'PyxisTraffic40M4.sim.business',
           'PyxisTraffic40M4.sim.collisionsAtBase',
           'PyxisTraffic40M4.sim.efficiency'}
           
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

Files45M4={'PyxisTraffic45M4.sim.allocatedBps',
           'PyxisTraffic45M4.sim.requestedBps'
           'PyxisTraffic45M4.sim.business',
           'PyxisTraffic45M4.sim.collisionsAtBase',
           'PyxisTraffic45M4.sim.efficiency'}
           
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

Files50M4={'PyxisTraffic50M4.sim.allocatedBps',
           'PyxisTraffic50M4.sim.requestedBps'
           'PyxisTraffic50M4.sim.business',
           'PyxisTraffic50M4.sim.collisionsAtBase',
           'PyxisTraffic50M4.sim.efficiency'}
           
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

Files55M4={'PyxisTraffic55M4.sim.allocatedBps',
           'PyxisTraffic55M4.sim.requestedBps'
           'PyxisTraffic55M4.sim.business',
           'PyxisTraffic55M4.sim.collisionsAtBase',
           'PyxisTraffic55M4.sim.efficiency'}
           
FilesUnitsM0 = {Files25M0,Files30M0,Files35M0,Files40M0,Files45M0,Files50M0,Files55M0}            
FilesUnitsM1 = {Files25M1,Files30M1,Files35M1,Files40M1,Files45M1,Files50M1,Files55M1}            
FilesUnitsM2 = {Files25M2,Files30M2,Files35M2,Files40M2,Files45M2,Files50M2,Files55M2}            
FilesUnitsM3 = {Files25M3,Files30M3,Files35M3,Files40M3,Files45M3,Files50M3,Files55M3}            
FilesUnitsM3 = {Files25M4,Files30M4,Files35M4,Files40M4,Files45M4,Files50M4,Files55M4}            

files=FilesUnitsM3
path=fpath

function retval = runOne(p, f, prm, elms, x)
  g={}
  h={}
  ret={}

  for k = 1:elms
    for j = 1:numel(x)
      g = load("-ascii", char( strcat( p, f{1,j}{prm}) ))
      h(j) = g(k)
    endfor
    ret{k}=h
  endfor
  
  retval=ret

endfunction

################################################################################
# Plot for M0/M1/M2 and M3 traffic loads
################################################################################
xAxis={25,30,35,40,45,50,55}

elmInEachFile=10

# params
p_allocated=1
p_requested=2
p_busy=3
p_collAtBase=4
p_efficiency=5

figure(1)

a0=runOne(fpath, FilesUnitsM0, p_allocated, elmInEachFile, xAxis)
r0=runOne(fpath, FilesUnitsM0, p_requested, elmInEachFile, xAxis)
a1=runOne(fpath, FilesUnitsM1, p_allocated, elmInEachFile, xAxis)
r1=runOne(fpath, FilesUnitsM1, p_requested, elmInEachFile, xAxis)
a2=runOne(fpath, FilesUnitsM2, p_allocated, elmInEachFile, xAxis)
r2=runOne(fpath, FilesUnitsM2, p_requested, elmInEachFile, xAxis)
a3=runOne(fpath, FilesUnitsM3, p_allocated, elmInEachFile, xAxis)
r3=runOne(fpath, FilesUnitsM3, p_requested, elmInEachFile, xAxis)

hold on
for k = 1:elmInEachFile
  plot(cell2mat(xAxis),cell2mat(a0{1,k}),"b-*", cell2mat(xAxis),cell2mat(r0{1,k}),'b--o')
  plot(cell2mat(xAxis),cell2mat(a1{1,k}),"g-*", cell2mat(xAxis),cell2mat(r1{1,k}),'g--o')
  plot(cell2mat(xAxis),cell2mat(a2{1,k}),"m-*", cell2mat(xAxis),cell2mat(r2{1,k}),'m--o')
  plot(cell2mat(xAxis),cell2mat(a3{1,k}),"y-*", cell2mat(xAxis),cell2mat(r3{1,k}),'y--o')
endfor
hold off

xlabel("nodes")
ylabel("bps", "rotation", 0)
legend("allocated (M0)","requested (M0)", 
       "allocated (M1)","requested (M1)",
       "allocated (M2)","requested (M2)",
       "allocated (M3)","requested (M3)","location", "northwest")
grid("on") 

figure(2)

b0=runOne(fpath, FilesUnitsM0, p_busy, elmInEachFile, xAxis)
e0=runOne(fpath, FilesUnitsM0, p_efficiency, elmInEachFile, xAxis)
b1=runOne(fpath, FilesUnitsM1, p_busy, elmInEachFile, xAxis)
e1=runOne(fpath, FilesUnitsM1, p_efficiency, elmInEachFile, xAxis)
b2=runOne(fpath, FilesUnitsM2, p_busy, elmInEachFile, xAxis)
e2=runOne(fpath, FilesUnitsM2, p_efficiency, elmInEachFile, xAxis)
b3=runOne(fpath, FilesUnitsM3, p_busy, elmInEachFile, xAxis)
e3=runOne(fpath, FilesUnitsM3, p_efficiency, elmInEachFile, xAxis)

hold on
for k = 1:elmInEachFile
  plot(cell2mat(xAxis),cell2mat(b0{1,k}),"g-*")
  plot(cell2mat(xAxis),cell2mat(b2{1,k}),"r-*")
  plot(cell2mat(xAxis),cell2mat(b3{1,k}),"b-*")
endfor
hold off

xlabel("nodes")
ylabel("bps", "rotation", 0)
legend("business (Scada only)",
       "business (+30%)", 
       "business (+50%)", "location", "northwest")
grid("on") 

figure(3)

hold on
for k = 1:elmInEachFile
  plot(cell2mat(xAxis),cell2mat(e0{1,k}),"g-*")
  plot(cell2mat(xAxis),cell2mat(e2{1,k}),"r-*")
  plot(cell2mat(xAxis),cell2mat(e3{1,k}),"b-*")
endfor
hold off

xlabel("nodes")
ylabel("bps", "rotation", 0)
legend("efficiency (Scada only)",
       "efficiency (+30%)", 
       "efficiency (+50%)", "location", "northwest")
grid("on") 
