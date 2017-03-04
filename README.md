# pyxnet
Simulation of multipoint SCADA network

One-to-many with Store-and-Forward mode

# one mini-slot assumption
# ____/-------------\_____
#  rx-tx               tx-rx
#              46b
#  400us                400us
#      ------2.5ms----
# assume 4 header bytes (46-4=42)
# 50B > added ~8 bytes of data for transmission is consecutive slots (inaccurate because has to exclude last slot)

# a raw rate of 38.2kbps which is 19.1 bit/ms for 2-GFSK amd 38.2 bit/ms for 4-GFSK
# for 4-GFSK system a slot of 5ms is contains 382 bits or 24 bytes.
# Phy header is 8 bit preamble and 32 bits sync -> 40 b or 5 bytes, leaving 19 bytes per 5ms
# If we were to transmit an extension of 1 packet by another one then
# ____/--------\____/---------\______
#       PPPDDDDDDDDDDD
# We gain 1ms of tx-rx switch-over (4 bytes) and 5 ms for data (24 bytes) - extra 28 bytes~
# Total single packet payload size: 19B Double: 19+28=47B Triple: 19+28*2=75, etc.
# Next simulation assumes 4-GFSK radios