%alunos = {};
do {
	$nome=input "Entre com o nome: ";
	%alunos{$nome} = input "Entre com a nota de " . $nome . ": " if (not empty $nome);
} while (not empty $nome);
@nomes = keys %alunos;
println @nomes;
println %alunos;println "Foram " . (size @nomes) . " aluno(s) matriculado(s):";
foreach $a (sort @nomes) {
	print " " . $a . ": ";
	$c = %alunos{$a};
	if ($c >= 60) {
		print "aprovado(a) - ";
		println "A" if $c >= 90;
		println "B" if ($c >= 80 and $c < 90);
		println "C" if ($c >= 70 and $c < 80);
		println "D" if ($c < 70);
	} else {
		println "reprovado(a) - E";
	}
}