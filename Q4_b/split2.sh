#!/bin/bash
#mb=131072000 #500 mb
mb=2621440
divide(){
	#echo "$1" " " "$2"
	if [ `echo "$2 <= $mb"|bc -l ` -eq 1 ]
	then
		sort -no "$1" "$1" 
		return
	fi
	#if [ $(($2%2)) -eq 0 ]
	#then
	#	nw=`echo "$(($2/2))"`
	#else
	nw=`echo $(($(($2+1))/2))`
	#fi
	split -l $nw "$1"  
	mv "xaa" "$(($1*2))"
	mv "xab" "$(($1*2+1))"
	divide "$(($1*2))" $nw
	divide "$(($1*2+1))" $nw
	#echo "$(($1*2))" " " "$(($1*2+1))" " "  "$1"
	sort -nm  $(($1*2)) $(($1*2+1)) --output="$1"
	return
	
}



n=`wc -l "1"`
#cat "${files[@]}"

j=1
divide "$j" $n




exit


