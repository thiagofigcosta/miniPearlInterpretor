%h={"one"=>1,"two"=>2,"x"=>"quebrando\nlinhas"};
println %h;
println %h{"one"};
%h{"one"}=666;
println %h;
println %h{"one"};