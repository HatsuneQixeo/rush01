EXE="./rush01.exe"
size="$1"

source="$(python3.exe generator.py $size)" || exit $?

arg="$(awk 'NR<2' <<< "$source")"

echo "Arg: $arg"

expect="$(awk 'NR>2' <<< "$source")"
output="$(time $EXE "$arg")"

echo "Expect:    
$expect"
echo "Output:
$output"

