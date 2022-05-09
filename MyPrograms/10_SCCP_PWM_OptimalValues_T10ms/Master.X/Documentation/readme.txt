The following code in python gives the best settings for the PWM. It's not the best code (it could be prettier) but it works:

desired_period = 0.02

sccp_prescaler = [1,4,16,64]
ref_clk = [8e6,100e6,200e6] #POSC,FCY, FOSC

ref_prescaler = [1]
i = 0
while i< 65534:
	ref_prescaler.append(i+2)
	i=i+2

counts = []
combinations = []

for source in ref_clk:
	for prescaler1 in ref_prescaler:
		for prescaler2 in sccp_prescaler:
			count = ((source/prescaler1)/prescaler2)*desired_period
			decimal = abs(count-int(count))
			if count<=65535 and decimal<0.001:
				counts.append(count)
				combinations.append("CLK={} P1={} P2={}".format(source, prescaler1, prescaler2))

best_count = max(counts)
best_index = counts.index(best_count)
best_combination = combinations[best_index]

print(best_count)
print(best_combination)
