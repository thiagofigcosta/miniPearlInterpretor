%dic={"um"=>"one","dois"=>"two","tres"=>"three","quatro"=>"four","cinco"=>"five"};
@pt = keys %dic;
@en = values %dic;
printlm @pt.@en;