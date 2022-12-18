
from dwave.system.samplers import DWaveSampler
from dwave.system.composites import EmbeddingComposite #lazyfixedembedding
     
sampler = EmbeddingComposite(DWaveSampler(endpoint='https://cloud.dwavesys.com/sapi/', token='DEV-6ead7fc50a1b6881ab4eea5a3ea87748768fc97f', solver='Advantage_system1.1'))


file = open("/Users/diogopires/Desktop/jets/Diogo/Events/file_n.txt", "r")
file_n = eval(file.readline())

for i in range(30,file_n):
	
	file = open("/Users/diogopires/Desktop/jets/Diogo/Events/J-Matrix"+str(i)+".txt", "r") 
	
	J = eval(file.readline())
	
	response = sampler.sample_ising({}, J, num_reads=5000, annealing_time = 20)
	
	#print(response.first.sample, "Energy: ", response.first.energy, "Occurrences: ", response.first.num_occurrences)
	
	file1 = open("/Users/diogopires/Desktop/jets/Diogo/Results/results_clustering"+str(i)+".txt", "w") 
	
	for key in response.first.sample:
		file1.write(key[1:])
		file1.write("\t")
		file1.write(str(response.first.sample[key]))
		file1.write("\n")
	
	print("Quantum time "+str(i)+": ", response.info["timing"])
	print(response.first.energy, "\n", "\n")

#file1.write(""+response.first.sample)

# for datum in response.data(['sample', 'energy', 'num_occurrences']):   # doctest: +SKIP
# 	print(datum.sample, "Energy: ", datum.energy, "Occurrences: ", datum.num_occurrences)

