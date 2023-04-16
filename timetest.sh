
if [ $# -ne 2 ]
then
	echo "usage: ./timetest.sh <size> <iteration>"
	exit 1
fi

size="$1"
iteration="$2"

arr=()

for ((i = 1; i <= $iteration; i++))
do
	time="$(./test.sh $size 2>&1 | grep real | awk '{print $2}')"

	echo "$i: $time"
	arr+=("$time")
done

for ele in ${arr[@]}
do
	echo "ele: $ele"
done

