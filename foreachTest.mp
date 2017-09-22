@l=[1,2,3];
println "Fora de ordem:";
foreach $x (@l)
	println $x;
println "Ordenado:";
foreach $x (reverse @l)
	println $x;