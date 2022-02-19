#%%
from cmath import pi


k = 1000 # Kilo

#%% 
# Determine the output voltage given input and R1,R2

R1 = 10*k
R2 = 20*k
Vin = 5
Vout = Vin * ( R2 / (R1 + R2))
print("Voltage is ",Vout,"V")
###


#%%
# Determine the cutoff frequency given R1 and C1
R1 = 100*k 
C1 = 100*10**-9 # 100nf
f = 1/(2*pi*R1*C1)
print("cutoff frequency is : ",f,"Hz")