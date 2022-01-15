

K = 1000
M = 1000000
MU = 0.000001

Ra = 100*K
Rb = 40*K
C = 1000*MU
Duty_cycle = (Rb)/(Ra+2*Rb)

f= (1.46)/( (Ra + 2*Rb )*C )
T  = 1/f

# it looks like its inversed
#T_On = Duty_cycle * T
#T_Off = (1-Duty_cycle) *T

T_Off = Duty_cycle * T
T_On = (1-Duty_cycle) *T

print("Duty cycle : <",Duty_cycle,">")
print("Periode : <",T,">")
print("Frequency : <",f,">")
print("T_on : <",T_On,">")
print("T_Off: <",T_Off,">")





