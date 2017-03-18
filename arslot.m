# Pyxis simulation production graphing
# AR Slot analysis

clear
more off

fpath='F:\Work\OMnetPP\omnetpp-5.0\samples\pyxnet\test_arslot\'

arFiles50={'PyxisPureScada50.sim.allocatedBps',
           'PyxisPureScada50.sim.requestedBps'
           'PyxisPureScada50.sim.business',
           'PyxisPureScada50.sim.collisionsAtBase',
           'PyxisPureScada50.sim.efficiency'}

arFiles60={'PyxisPureScada60.sim.allocatedBps',
           'PyxisPureScada60.sim.requestedBps'
           'PyxisPureScada60.sim.business',
           'PyxisPureScada60.sim.collisionsAtBase',
           'PyxisPureScada60.sim.efficiency'}

arFiles70={'PyxisPureScada70.sim.allocatedBps',
           'PyxisPureScada70.sim.requestedBps'
           'PyxisPureScada70.sim.business',
           'PyxisPureScada70.sim.collisionsAtBase',
           'PyxisPureScada70.sim.efficiency'}
           
arFiles80={'PyxisPureScada80.sim.allocatedBps',
           'PyxisPureScada80.sim.requestedBps'
           'PyxisPureScada80.sim.business',
           'PyxisPureScada80.sim.collisionsAtBase',
           'PyxisPureScada80.sim.efficiency'}

arFiles90={'PyxisPureScada90.sim.allocatedBps',
           'PyxisPureScada90.sim.requestedBps'
           'PyxisPureScada90.sim.business',
           'PyxisPureScada90.sim.collisionsAtBase',
           'PyxisPureScada90.sim.efficiency'}

arFiles100={'PyxisPureScada100.sim.allocatedBps',
            'PyxisPureScada100.sim.requestedBps'
            'PyxisPureScada100.sim.business',
            'PyxisPureScada100.sim.collisionsAtBase',
            'PyxisPureScada100.sim.efficiency'}

arFiles110={'PyxisPureScada110.sim.allocatedBps',
            'PyxisPureScada110.sim.requestedBps'
            'PyxisPureScada110.sim.business',
            'PyxisPureScada110.sim.collisionsAtBase',
            'PyxisPureScada110.sim.efficiency'}

arFiles120={'PyxisPureScada120.sim.allocatedBps',
            'PyxisPureScada120.sim.requestedBps'
            'PyxisPureScada120.sim.business',
            'PyxisPureScada120.sim.collisionsAtBase',
            'PyxisPureScada120.sim.efficiency'}


arFiles = {arFiles50,arFiles60,arFiles70,arFiles80,arFiles90,arFiles100,arFiles110,arFiles120}            

files=arFiles
path=fpath
################################################################################
# Pyxis plot Req vs. Alloc
################################################################################
xAxis={50,60,70,80,90}
elmInEachFile=10

figure(1)

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
