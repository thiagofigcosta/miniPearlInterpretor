@l=[6,2,9,3,1,6,0];
println "Fora de ordem:";
foreach $x (@l)
	println $x;
println "Ordenado:";
foreach $x (sort @l)
	println $x;
println "Reverso:";
foreach $x (reverse @l)
	println $x;

println "Decrescente(nao sei se e pra funcionar):";
foreach $x (reverse sort @l)
	println $x;