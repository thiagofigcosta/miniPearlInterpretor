%alunos={};
do{
	$nome=input "Entre com o nome:";
	%alunos{$nome}=input "Entre com a nota de ".$nome.":" if(not empty $nome);
}while(not empty $nome);
println %alunos;