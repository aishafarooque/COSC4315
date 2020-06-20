rm -f grade
base1="ans"
base="tc"
base2=".out"
sum=0
for testN in {1..3}
do

  inputAn=$base1$testN$base2
  input=$base$testN$base2

  declare -a anArray
  i=0
  while IFS= read -r line
  do
    if [ -z "$line" ]
    then
      continue
    fi 
    key=$(echo "$line")
    anArray[$i]=$key
    i=$(($i+1))
  done < $inputAn

  wrong=0
  iT=0
  while IFS= read -r line
  do
    out=$(echo "$line")
    if [ -z "$line" ]
    then
      continue
    fi 
    if [[ $out != ${anArray[$iT]} ]] 
    then
      wrong=$(($wrong + 1))
    fi
    iT=$(($iT+1))
  done < $input

  if [ $iT -gt  $i ] && [ $wrong == 0 ]
  then
    wrong=$(($wrong + 1))
  fi

  grade=$((10*($iT - $wrong)/$i))
  sum=$(($sum+$grade))
  echo "the grade for testcase "$testN" is "$grade >> grade

done

  echo "the total grade is "$sum>>grade

