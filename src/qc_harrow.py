
from dwave.system.samplers import DWaveSampler
from dwave.system.composites import EmbeddingComposite #lazyfixedembedding
     
sampler = EmbeddingComposite(DWaveSampler(endpoint='https://cloud.dwavesys.com/sapi/', token='DEV-ee4b5b8ef36b029647ac19ded061ddb112f340e0', solver='Advantage_system1.1'))

file = open("/Users/diogopires/Desktop/jets/Diogo/Events/file_n.txt", "r")
file_n = eval(file.readline())

for i in range(file_n):
	
	file = open("/Users/diogopires/Desktop/jets/Diogo/Events/Q-matrix"+str(i)+".txt", "r") 
	
	Q = eval(file.readline())
	
	response = sampler.sample_qubo(Q, num_reads=5000, annealing_time = 20)
	
	#print(response.first.sample, "Energy: ", response.first.energy, "Occurrences: ", response.first.num_occurrences)
	
	file1 = open("/Users/diogopires/Desktop/jets/Diogo/Results/results_harrow"+str(i)+".txt", "w") 
	
	for key in response.first.sample:
		file1.write(key[1:])
		file1.write("\t")
		file1.write(str(response.first.sample[key]))
		file1.write("\n")
	
	print("Quantum time "+str(i)+": ", response.info["timing"])
	print(response.first.energy, "\n", "\n")
#print(response.first.sample, "\n", "\n")

#file1.write(""+response.first.sample)

# for datum in response.data(['sample', 'energy', 'num_occurrences']):   # doctest: +SKIP
# 	print(datum.sample, "Energy: ", datum.energy, "Occurrences: ", datum.num_occurrences)

