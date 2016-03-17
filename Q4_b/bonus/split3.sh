#!/bin/bash
#mb=131072000 #500 mb
mb=26214400
divide(){
	#echo "$1" " " "$2"
	if [ `echo "$2 <= $mb"|bc -l ` -eq 1 ]
	then
		sort -no "$1" "$1" 
		return
	fi
	if [ $(($2%3)) -eq 0 ]
	then
		nw=`echo "$(($2/3))"`
	else
		nw=`echo $(($2/3 + 1))`
	fi
	#nw=`echo $(($(($2+2))/3))`
	split -l $nw "$1"  
	mv "xaa" "$(($1*3-1))"
	mv "xab" "$(($1*3))"
	mv "xac" "$(($1*3+1))"
	divide "$(($1*3-1))" $nw
	divide "$(($1*3))" $nw
	divide "$(($1*3+1))" $nw
	#echo "$(($1*2))" " " "$(($1*2+1))" " "  "$1"
	sort -nm  "$(($1*3-1))" "$(($1*3))" "$(($1*3+1))" --output="$1"
	return
	
}



n=`wc -l "1"`
#cat "${files[@]}"

j=1
divide "$j" $n




exit


