@l=[6,2,9,3,1,6,0];
println "Fora de ordem:";
foreach $x (@l)
	println $x;
println "\nReverso:";
foreach $x (reverse @l)
	println $x;
println "\nOrdenado:";
foreach $x (sort @l)
	println $x;
println "\nDecrescente(nao sei se e pra funcionar):";
foreach $x (reverse sort @l)
	println $x;